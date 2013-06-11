//Spencer Jackson
//casynth.c
#include<casynth.h>
#include<constants.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>



//private functions
inline void run_active_notes(CASYNTH *synth, uint32_t nframes, float buffer[])
{
    unsigned char j,k;
    NOTE* note;
    double astep = *synth->amod_freq_p/synth->sample_rate;
    double fstep = *synth->fmod_freq_p/synth->sample_rate;//need to decide where to calculate this. Probably not here.
    for(j=0;j<synth->nactive;j++)
    {
        note = &(synth->note[synth->active[j]]);
        play_note( note,
                   nframes,
                   buffer,
                   synth->pitchbend,
                   *synth->master_gain_p,
                   (unsigned char)*synth->rule_p,
                   astep,
                   fstep);

        //cleanup dead notes
        if(note->note_dead)
        {
            synth->nactive--;
            for(k=j;k<synth->nactive;k++)
            {
                synth->active[k] = synth->active[k+1];
            }
        }
    }
}


//main functions
LV2_Handle init_casynth(const LV2_Descriptor *descriptor,double sample_rate, const char *bundle_path,const LV2_Feature * const* host_features)
{
    CASYNTH* synth = malloc(sizeof(CASYNTH));
    unsigned char i;

    synth->sample_rate = sample_rate;

    synth->midi_in_p = NULL;
    synth->nactive = 0;
    synth->nsustained = 0;
    for(i=0;i<127;i++)
    {
        init_note(&(synth->note[i]),
                  sample_rate,
                  i,
                  synth->nharmonics_p,
                  synth->cell_life_p,
                  synth->amod_gain_p,
                  synth->fmod_gain_p);
        synth->active[i] = 0;
        synth->sustained[i] = 0;
    }

    synth->harmonic_mode = HARMONIC_MODE_SINC;
    for(i=0;i<MAX_N_HARMONICS;i++)
    {
        synth->harm_gain_sinc[i] = 1/(MAX_N_HARMONICS +1);//(nharmonics+1);
        synth->harm_gain_saw[i] = .29/(i+2);//.29 makes it so gain=1 if all harmonics play
        synth->harm_gain_sqr[i] = (i%2!=0)*.48/(i+2);//odd harmonics
        synth->harm_gain_tri[i] = (i%2!=0)*.83/((i+2)*(i+2));
    }
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
                break;
            }
        }
    }

    return synth;
}

void connect_casynth_ports(LV2_Handle handle, uint32_t port, void *data)
{
    CASYNTH* synth = (CASYNTH*)handle;
    if(port == MIDI_IN)         synth->midi_in_p = (const LV2_Atom_Sequence*)data;
    else if(port == OUTPUT)     synth->output_p = (const float*)data;
    else if(port == CHANNEL)    synth->channel_p = (const float*)data;
    else if(port == MASTER_GAIN)synth->master_gain_p = (const float*)data;
    else if(port == RULE)       synth->cell_life_p = (const float*)data;
    else if(port == CELL_LIFE)  synth->rule_p = (const float*)data;
    else if(port == INIT_CELLS) synth->init_cells_p = (const float*)data;
    else if(port == NHARMONICS) synth->nharmonics_p = (const float*)data;
    else if(port == HARM_MODE)  synth->harmonic_mode_p = (const float*)data;
    else if(port == WAVE)       synth->wave_p = (const float*)data;
    else if(port == ENV_A)      synth->env_a_p = (const float*)data;
    else if(port == ENV_D)      synth->env_d_p = (const float*)data;
    else if(port == ENV_B)      synth->env_b_p = (const float*)data;
    else if(port == ENV_SWL)    synth->env_swl_p = (const float*)data;
    else if(port == ENV_SUS)    synth->env_sus_p = (const float*)data;
    else if(port == ENV_R)      synth->env_r_p = (const float*)data;
    else if(port == AMOD_WAV)   synth->amod_wave_p = (const float*)data;
    else if(port == AMOD_FREQ)  synth->amod_freq_p = (const float*)data;
    else if(port == AMOD_GAIN)  synth->amod_gain_p = (const float*)data;
    else if(port == FMOD_WAV)   synth->fmod_wave_p = (const float*)data;
    else if(port == FMOD_FREQ)  synth->fmod_freq_p = (const float*)data;
    else if(port == FMOD_GAIN)  synth->fmod_gain_p = (const float*)data;
    else puts("UNKNOWN PORT YO!!");
}

void run_casynth( LV2_Handle handle, uint32_t nframes)
{
    CASYNTH* synth = (CASYNTH*)handle;
    unsigned char i,j,k;
    float* buf = synth->output_p;
    LV2_Atom_Event event;
    uint32_t frame_no = 0;
    unsigned char* message;
    unsigned char type;
    unsigned char num, val;
    short bend;
    bool firstnote = true;
    NOTE* note;
    double astep = *synth->amod_freq_p/synth->sample_rate;
    double fstep = *synth->fmod_freq_p/synth->sample_rate;//need to decide where to calculate this. Probably not here.


    memset(buf,0, sizeof(float)*nframes);//start by filling buffer with 0s, we'll add to this

    LV2_ATOM_SEQUENCE_FOREACH(synth->midi_in_p, event)
    {
        if (event && event->body.type == synth->midi_event_type)//make sure its a midi event
        {
            message = (unsigned char*) LV2_ATOM_BODY(&(event->body));
            if( !(*synth->channel_p) || ((message[0]&MIDI_CHANNEL_MASK) == (*synth->channel_p)+1) )
            {
                type = message[0]&MIDI_TYPE_MASK;

                if(type == MIDI_NOTE_ON)
                {
                    num = message[1]&MIDI_DATA_MASK;
                    val = message[2]&MIDI_DATA_MASK;
                    if(synth->note[num].note_dead == true)
                    {
                        synth->active[synth->nactive++] = num;//push new note onto active stack
                    }
                    if(firstnote)//only calculate these if there is a note in this period
                    {
                        firstnote = false;
                        //condition envelope
                        synth->envelope[ENV_ATTACK] = 1/(*synth->env_a_p*synth->sample_rate);
                        synth->envelope[ENV_DECAY] = (*synth->env_b_p-1)/(*synth->env_d_p*synth->sample_rate);
                        synth->envelope[ENV_BREAK] = *synth->env_b_p;
                        synth->envelope[ENV_SWELL] = (*synth->env_sus_p - *synth->env_b_p)/(*synth->env_swl_p*synth->sample_rate);
                        synth->envelope[ENV_SUSTAIN] = *synth->env_sus_p;
                        synth->envelope[ENV_RELEASE] = -*synth->env_sus_p/(*synth->env_r_p*synth->sample_rate);

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
                    start_note(&(synth->note[num]),
                               val,
                               event->time.frames,
                               synth->harm_gains,
                               *synth->init_cells_p,
                               synth->envelope,
                               *synth->wave_p,
                               *synth->amod_wave_p,
                               *synth->fmod_wave_p);
                }
                else if(type == MIDI_NOTE_OFF)
                {
                    num = message[1]&MIDI_DATA_MASK;
                    for(i=0;i<synth->nactive;i++)
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
                                end_note(&(synth->note[num]),event->time.frames);
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
                            for(i=0;i<synth->nsustained;i++)
                            {
                                end_note(&(synth->note[synth->sustained[i]]),event->time.frames);
                            }
                            synth->nsustained = 0;
                        }
                        else
                        {
                            synth->sus = true;
                        }
                    }

                }
                else if(type == MIDI_PITCHBEND)
                {
                    bend = (message[1]&MIDI_DATA_MASK) + ((message[2]&MIDI_DATA_MASK)<<7) - MIDI_PITCH_CENTER;
                    //run and update current position because this blocks (affects all notes)
                    //run_active_notes(synth, event->time.frames - frame_no -1, &(buf[frame_no]));
                    for(j=0;j<synth->nactive;j++)
                    {
                        note = &(synth->note[synth->active[j]]);
                        play_note( note,
                                   event->time.frames - frame_no -1,//play to frame before event
                                   &(buf[frame_no]),
                                   synth->pitchbend,
                                   *synth->master_gain_p,
                                   (unsigned char)*synth->rule_p,
                                   astep,
                                   fstep);

                        //cleanup dead notes
                        if(note->note_dead)
                        {
                            synth->nactive--;
                            for(k=j;k<synth->nactive;k++)
                            {
                                synth->active[k] = synth->active[k+1];
                            }
                        }
                    }
                    synth->pitchbend = pow(2,bend/49152);//49152 is 12*8192/2
                    frame_no = event->time.frames;
                }//message types
            }//correct channel
        }//actually midi
    }//for each event

    //finish off whatever frames are left
    if(frame_no != nframes-1)
    {
        //run_active_notes(synth, nframes - frame_no, &(buf[frame_no]));
        for(j=0;j<synth->nactive;j++)
        {
            note = &(synth->note[synth->active[j]]);
            play_note( note,
                       nframes - frame_no,
                       &(buf[frame_no]),
                       synth->pitchbend,
                       *synth->master_gain_p,
                       (unsigned char)*synth->rule_p,
                       astep,
                       fstep);

            //cleanup dead notes
            if(note->note_dead)
            {
                synth->nactive--;
                for(k=j;k<synth->nactive;k++)
                {
                    synth->active[k] = synth->active[k+1];
                }
            }
        }//active notes
    }//leftovers
}


void cleanup_casynth(LV2_Handle handle)
{
    CASYNTH* synth = (CASYNTH*) handle;
    free(synth);
}

