//Spencer Jackson
//casynth.c
#include<casynth.h>
#include<constants.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>


//main functions
LV2_Handle init_casynth(const LV2_Descriptor *descriptor,double sample_rate, const char *bundle_path,const LV2_Feature * const* host_features)
{
    CASYNTH* synth = malloc(sizeof(CASYNTH));
    uint8_t i;

    synth->sample_rate = sample_rate;

    init_waves(&(synth->waves));

    synth->midi_in_p = NULL;
    synth->nactive = 0;
    synth->nsustained = 0;
    synth->pitchbend = 1;
    synth->ibpm = .5;//60/120
    for(i=0; i<127; i++)
    {
        init_note(&(synth->note[i]),
                  &(synth->waves),
                  sample_rate,
                  i,
                  &(synth->ncells),
                  &(synth->cell_lifetime),
                  &(synth->amod_g),
                  &(synth->fmod_g));
        synth->active[i] = 0;
        synth->sustained[i] = 0;
    }

    synth->harmonic_mode = HARMONIC_MODE_SINC;
    for(i=0; i<MAX_N_HARMONICS; i++)
    {
        synth->harm_gain_sinc[i] = 1/(float)(MAX_N_HARMONICS +1);//(nharmonics+1);
        synth->harm_gain_saw[i] = .29/(float)(i+2);//.29 makes it so gain=1 if all harmonics play
        synth->harm_gain_sqr[i] = (i%2!=0)*.48/(float)(i+2);//odd harmonics
        synth->harm_gain_tri[i] = (i%2!=0)*.83/(float)((i+2)*(i+2));
    }
    //fundamental
    synth->harm_gain_sinc[i] = 1/(float)(MAX_N_HARMONICS +1);//(nharmonics+1);
    synth->harm_gain_saw[i] = .29;//.29 makes it so gain=1 if all harmonics play
    synth->harm_gain_sqr[i] = .48;
    synth->harm_gain_tri[i] = .83;

    synth->harm_gains = synth->harm_gain_sinc;

    //get urid map value for midi events
    for (int i = 0; host_features[i]; i++)
    {
        if (strcmp(host_features[i]->URI, LV2_URID__map) == 0)
        {
            LV2_URID_Map *urid_map = (LV2_URID_Map *) host_features[i]->data;
            if (urid_map)
            {
                synth->midi_event_type = urid_map->map(urid_map->handle, LV2_MIDI__MidiEvent);
                synth->other_type = urid_map->map(urid_map->handle, LV2_ATOM__Blank);
                synth->long_type = urid_map->map(urid_map->handle, LV2_ATOM__Long);
                synth->float_type = urid_map->map(urid_map->handle, LV2_ATOM__Float);
                synth->time_info_type = urid_map->map(urid_map->handle, LV2_TIME__Position);
                synth->beatsperbar_type = urid_map->map(urid_map->handle, LV2_TIME__barBeat);
                synth->bpm_type = urid_map->map(urid_map->handle, LV2_TIME__beatsPerMinute);
                synth->speed_type = urid_map->map(urid_map->handle, LV2_TIME__speed);
                synth->frame_type = urid_map->map(urid_map->handle, LV2_TIME__frame);
                synth->framespersec_type = urid_map->map(urid_map->handle, LV2_TIME__framesPerSecond);
                break;
            }
        }
    }

    return synth;
}

void connect_casynth_ports(LV2_Handle handle, uint32_t port, void *data)
{
    CASYNTH* synth = (CASYNTH*)handle;
    switch(port)
    {
    case MIDI_IN:
        synth->midi_in_p = (LV2_Atom_Sequence*)data;
        break;
    case OUTPUT:
        synth->output_p = (float*)data;
        break;
    case CHANNEL:
        synth->channel_p = (float*)data;
        break;
    case MASTER_GAIN:
        synth->master_gain_p = (float*)data;
        break;
    case RULE:
        synth->rule_p = (float*)data;
        break;
    case CELL_LIFE:
        synth->cell_life_p = (float*)data;
        break;
    case INIT_CELLS:
        synth->init_cells_p = (float*)data;
        break;
    case NHARMONICS:
        synth->nharmonics_p = (float*)data;
        break;
    case HARM_MODE:
        synth->harmonic_mode_p = (float*)data;
        break;
    case HARM_WIDTH:
        synth->harmonic_width_p = (float*)data;
        break;
    case WAVE:
        synth->wave_p = (float*)data;
        break;
    case ENV_A:
        synth->env_a_p = (float*)data;
        break;
    case ENV_D:
        synth->env_d_p = (float*)data;
        break;
    case ENV_B:
        synth->env_b_p = (float*)data;
        break;
    case ENV_SWL:
        synth->env_swl_p = (float*)data;
        break;
    case ENV_SUS:
        synth->env_sus_p = (float*)data;
        break;
    case ENV_R:
        synth->env_r_p = (float*)data;
        break;
    case AMOD_WAV:
        synth->amod_wave_p = (float*)data;
        break;
    case AMOD_FREQ:
        synth->amod_freq_p = (float*)data;
        break;
    case AMOD_GAIN:
        synth->amod_gain_p = (float*)data;
        break;
    case FMOD_WAV:
        synth->fmod_wave_p = (float*)data;
        break;
    case FMOD_FREQ:
        synth->fmod_freq_p = (float*)data;
        break;
    case FMOD_GAIN:
        synth->fmod_gain_p = (float*)data;
        break;
    default:
        puts("UNKNOWN PORT YO!!");
    }
}

void run_casynth( LV2_Handle handle, uint32_t nframes)
{
    CASYNTH* synth = (CASYNTH*)handle;
    uint8_t i,j,k;
    float* buf = synth->output_p;
    uint32_t frame_no = 0;
    uint32_t t = 0;
    uint8_t* message;
    uint8_t type;
    uint8_t num, val;
    int16_t bend;
    bool firstnote = true;
    NOTE* note;
    double astep = synth->waves.func_domain*(*synth->amod_freq_p)/synth->sample_rate;
    double fstep = synth->waves.func_domain*(*synth->fmod_freq_p)/synth->sample_rate;//need to decide where to calculate this. Probably not here.

    synth->ncells = *synth->nharmonics_p;
    synth->cell_lifetime = synth->sample_rate*(*synth->cell_life_p)*synth->ibpm;
    synth->amod_g = *synth->amod_gain_p;
    synth->fmod_g = *synth->fmod_gain_p;

    for(t=0; t<nframes; t++) //start by filling buffer with 0s, we'll add to this
    {
        buf[t] = 0;
    }
    t=0;

    LV2_ATOM_SEQUENCE_FOREACH(synth->midi_in_p, event)
    {
        if (event)
        {
            if(event->body.type == synth->midi_event_type)//make sure its a midi event
            {
                message = (uint8_t*) LV2_ATOM_BODY(&(event->body));
                if( !(*synth->channel_p) || ((message[0]&MIDI_CHANNEL_MASK) == (*synth->channel_p)+1) )
                {
                    type = message[0]&MIDI_TYPE_MASK;
                    t = event->time.frames;

                    if(type == MIDI_NOTE_ON)
                    {
                        num = message[1]&MIDI_DATA_MASK;
                        val = message[2]&MIDI_DATA_MASK;
                        if(firstnote)//only calculate these if there is a note in this period
                        {
                            firstnote = false;
                            //condition envelope
                            synth->envelope[ENV_ATTACK] = 1/(float)(*synth->env_a_p*synth->sample_rate);
                            synth->envelope[ENV_DECAY] = (*synth->env_b_p*.9999-1)/(float)(*synth->env_d_p*synth->sample_rate);
                            synth->envelope[ENV_BREAK] = *synth->env_b_p*.9999;//scale a little so it will not immediately move to swell if b==1
                            synth->envelope[ENV_SWELL] = (*synth->env_sus_p - *synth->env_b_p)/(float)(*synth->env_swl_p*synth->sample_rate);
                            synth->envelope[ENV_SUSTAIN] = *synth->env_sus_p;
                            if(*synth->env_sus_p)
                                synth->envelope[ENV_RELEASE] = -(*synth->env_sus_p)/(float)(*synth->env_r_p*synth->sample_rate);
                            else if(synth->envelope[ENV_DECAY] < synth->envelope[ENV_SWELL])
                                synth->envelope[ENV_RELEASE] = synth->envelope[ENV_DECAY];//release same rate as decay
                            else
                                synth->envelope[ENV_RELEASE] = synth->envelope[ENV_SWELL];//release same rate as swell

                            //set harmonic gains
                            if(*synth->harmonic_mode_p != synth->harmonic_mode)
                            {
                                type = synth->harmonic_mode = *synth->harmonic_mode_p;
                                if(type == HARMONIC_MODE_SINC)
                                {
                                    synth->harm_gains = synth->harm_gain_sinc;
                                }
                                else if(type == HARMONIC_MODE_SAW)
                                {
                                    synth->harm_gains = synth->harm_gain_saw;
                                }
                                else if(type == HARMONIC_MODE_SQR)
                                {
                                    synth->harm_gains = synth->harm_gain_sqr;
                                }
                                else if(type == HARMONIC_MODE_TRI)
                                {
                                    synth->harm_gains = synth->harm_gain_tri;
                                }
                            }
                        }
                        if(val)
                        {
                            if(synth->note[num].note_dead == true)
                            {
                                synth->active[synth->nactive++] = num;//push new note onto active stack
                            }
                            else //note still playing, finish the old one
                            {
                                play_note( &synth->note[num],
                                           &(synth->waves),
                                           t - frame_no,//play to frame before event
                                           &(buf[frame_no]),
                                           synth->pitchbend,
                                           *synth->master_gain_p,
                                           (uint8_t)*synth->rule_p,
                                           *synth->wave_p,
                                           *synth->fmod_wave_p,
                                           fstep,
                                           *synth->amod_wave_p,
                                           astep);//note can't be dead about to start again
                            }
                            start_note(&(synth->note[num]),
                                       &(synth->waves),
                                       val,
                                       t,
                                       synth->harm_gains,
                                       *synth->init_cells_p,
                                       *synth->harmonic_width_p/1200,
                                       synth->envelope);
                        }
                        else//velocity zero == note off
                        {
                            for(i=0; i<synth->nactive; i++)
                            {
                                if(synth->active[i] == num)
                                {
                                    if(synth->sus)
                                    {
                                        if(!synth->note[num].sus)
                                        {
                                            synth->note[num].sus = true;
                                            synth->sustained[synth->nsustained++] = num;
                                        }
                                    }
                                    else
                                    {
                                        end_note(&(synth->note[num]),t);
                                    }
                                }
                            }
                        }
                    }
                    else if(type == MIDI_NOTE_OFF)
                    {
                        num = message[1]&MIDI_DATA_MASK;
                        for(i=0; i<synth->nactive; i++)
                        {
                            if(synth->active[i] == num)
                            {
                                if(synth->sus)
                                {
                                    if(!synth->note[num].sus)
                                    {
                                        synth->note[num].sus = true;
                                        synth->sustained[synth->nsustained++] = num;
                                    }
                                }
                                else
                                {
                                    end_note(&(synth->note[num]),t);
                                }
                            }
                        }

                    }
                    else if(type == MIDI_CONTROL_CHANGE)
                    {
                        num = message[1]&MIDI_DATA_MASK;
                        if(num == MIDI_SUSTAIN_PEDAL)
                        {
                            val = message[2]&MIDI_DATA_MASK;
                            if(val < 64)
                            {
                                synth->sus = false;
                                //end all sus. notes
                                for(i=0; i<synth->nsustained; i++)
                                {
                                    if(synth->note[synth->sustained[i]].sus)
                                    {
                                        end_note(&(synth->note[synth->sustained[i]]),t);
                                    }
                                }
                                synth->nsustained = 0;
                            }
                            else
                            {
                                synth->sus = true;
                            }
                        }
                        else if(num == MIDI_ALL_NOTES_OFF || num == MIDI_ALL_SOUND_OFF)
                        {
                            if(event->time.frames == 0)
                            {
                                event->time.frames++;
                            }
                            for(i=0; i<synth->nactive; i++)
                            {
                                num = synth->active[i];
                                end_note(&(synth->note[num]),t);

                            }
                            synth->nactive = 0;
                            synth->nsustained = 0;
                        }

                    }
                    else if(type == MIDI_PITCHBEND)
                    {
                        bend = (message[1]&MIDI_DATA_MASK) + ((message[2]&MIDI_DATA_MASK)<<7) - MIDI_PITCH_CENTER;
                        //run and update current position because this blocks (affects all notes)
                        //run_active_notes
                        for(j=0; j<synth->nactive; j++)
                        {
                            note = &(synth->note[synth->active[j]]);
                            play_note( note,
                                       &(synth->waves),
                                       t - frame_no,//play to frame before event
                                       &(buf[frame_no]),
                                       synth->pitchbend,
                                       *synth->master_gain_p,
                                       (uint8_t)*synth->rule_p,
                                       *synth->wave_p,
                                       *synth->fmod_wave_p,
                                       fstep,
                                       *synth->amod_wave_p,
                                       astep);

                            //cleanup dead notes
                            if(note->note_dead)
                            {
                                synth->nactive--;
                                for(k=j; k<synth->nactive; k++)
                                {
                                    synth->active[k] = synth->active[k+1];
                                }
                            }
                        }
                        synth->pitchbend = myPow2(bend/49152.0);//49152 is 12*8192/2
                        frame_no = event->time.frames;
                    }//message types
                }//correct channel
            }//actually midi
            else if(event->body.type == synth->other_type)
            {
                // Received new transport position/speed
                const LV2_Atom_Object *obj = (LV2_Atom_Object*)&event->body;
                if(obj->body.otype == synth->time_info_type)
                {
                    LV2_Atom *beat = NULL, *bpm = NULL, *speed = NULL;
                    LV2_Atom *fps = NULL, *frame = NULL;
                    lv2_atom_object_get(obj,
                                        synth->beatsperbar_type, &beat,
                                        synth->bpm_type, &bpm,
                                        synth->speed_type, &speed,
                                        synth->frame_type, &frame,
                                        synth->framespersec_type, &fps,
                                        NULL);

                    if (fps && fps->type == synth->float_type)
                    {
                        synth->sample_rate = ((LV2_Atom_Float*)fps)->body;
                    }
                    if (bpm && bpm->type == synth->float_type)
                    {
                        // Tempo changed, update BPM
                        synth->ibpm = 60/(((LV2_Atom_Float*)bpm)->body);
                        synth->cell_lifetime = synth->sample_rate*(*synth->cell_life_p)*synth->ibpm;
                    }
                    /*if (speed && speed->type == synth->float_type) {
                        // Speed changed, e.g. 0 (stop) to 1 (play)
                        self->speed = ((LV2_Atom_Float*)speed)->body;
                    }//could use this to end all notes, but midi message is good enough
                    if (beat && beat->type == synth->float_type) {
                       const double samples_per_beat = 60.0 / self->bpm * self->samplerate;
                        self->bar_beats = ((LV2_Atom_Float*)beat)->body;
                        self->beat_beats = self->bar_beats - floor(self->bar_beats);
                        self->pos_bbt = self->beat_beats * samples_per_beat;
                    }*/
                    /*if (frame && frame->type == synth->long_type) {
                        self->pos_frame = ((LV2_Atom_Long*)frame)->body;
                    }*/
                }//if time position
            }//if blank type
        }//actually is event
    }//for each event

    //finish off whatever frames are left
    if(frame_no != nframes-1)
    {
        //run_active_notes
        for(j=0; j<synth->nactive; j++)
        {
            note = &(synth->note[synth->active[j]]);
            play_note( note,
                       &(synth->waves),
                       nframes - frame_no,
                       &(buf[frame_no]),
                       synth->pitchbend,
                       *synth->master_gain_p,
                       (uint8_t)*synth->rule_p,
                       *synth->wave_p,
                       *synth->fmod_wave_p,
                       fstep,
                       *synth->amod_wave_p,
                       astep);

            //cleanup dead notes
            if(note->note_dead)
            {
                synth->nactive--;
                for(k=j; k<synth->nactive; k++)
                {
                    synth->active[k] = synth->active[k+1];
                }
                j--;//indexes changed
            }
        }//active notes
    }//leftovers

}


void cleanup_casynth(LV2_Handle handle)
{
    CASYNTH* synth = (CASYNTH*) handle;
    free(synth);
}

static const LV2_Descriptor casynth_descriptor=
{
    CASYNTH_URI,
    init_casynth,
    connect_casynth_ports,
    NULL,//activate
    run_casynth,
    NULL,//deactivate
    cleanup_casynth,
    NULL//extension
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index)
    {
    case 0:
        return &casynth_descriptor;
    default:
        return NULL;
    }
}
