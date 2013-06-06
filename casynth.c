//Spencer Jackson
//casynth.c
#include<casynth.h>
#include<constants.h>
#include<string.h>

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
        init_note(&(note[i]),sample_rate,i,synth->nharmonics_p,synth->amod_gain_p,synth->fmod_gain_p);
        synth->active[i] = 0;
        synth->sustained[i] = 0;
    }

    synth->harmonic_mode = HARMONIC_MODE_SINC;
    synth->harm_gain_sinc[i] = 1/(MAX_N_HARMONICS +1);//(nharmonics+1);
    synth->harm_gain_saw[i] = .29/(i+2);//.29 makes it so gain=1 if all harmonics play
    synth->harm_gain_sqr[i] = (i%2!=0)*.48/(i+2);//odd harmonics
    synth->harm_gain_tri[i] = (i%2!=0)*.83/((i+2)*(i+2));
    synth->harm_gains = synth->harm_gain_sinc;

    //get urid map value for midi events
    for (int i = 0; host_features[i]; ++i)
    {
        if (strcmp(host_features[i]->URI, LV2_URID_MAP_URI) == 0)
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

static void connect_casynth_ports(LV2_Handle handle, uint32_t port, void *data)
{
    CASYNTH* synth = (CASYNTH*)handle;
    if(port == MIDI_IN)         synth->midi_in_p = (LV2_Atom_Sequence*)data;
    else if(port == OUTPUT)     synth->output_p = (float*)data;
    else if(port == CHANNEL)    synth->channel_p = (float*)data;
    else if(port == MASTER_GAIN)synth->master_gain_p = (float*)data;
    else if(port == RULE)       synth->cell_life_p = (float*)data;
    else if(port == CELL_LIFE)  synth->rule_p = (float*)data;
    else if(port == INIT_CELLS) synth->init_cells_p = (float*)data;
    else if(port == NHARMONICS) synth->nharmonics_p = (float*)data;
    else if(port == HARM_MODE)  synth->harmonic_mode_p = (float*)data;
    else if(port == WAVE)       synth->wave_p = (float*)data;
    else if(port == ENV_A)      synth->env_a_p = (float*)data;
    else if(port == ENV_D)      synth->env_d_p = (float*)data;
    else if(port == ENV_B)      synth->env_b_p = (float*)data;
    else if(port == ENV_SWL)    synth->env_swl_p = (float*)data;
    else if(port == ENV_SUS)    synth->env_sus_p = (float*)data;
    else if(port == ENV_R)      synth->env_r_p = (float*)data;
    else if(port == AMOD_WAV)   synth->amod_wave_p = (float*)data;
    else if(port == AMOD_FREQ)  synth->amod_freq_p = (float*)data;
    else if(port == AMOD_GAIN)  synth->amod_gain_p = (float*)data;
    else if(port == FMOD_WAV)   synth->fmod_wave_p = (float*)data;
    else if(port == FMOD_FREQ)  synth->fmod_freq_p = (float*)data;
    else if(port == FMOD_GAIN)  synth->fmod_gain_p = (float*)data;
    else puts("UNKNOWN PORT YO!!");
}

static void run_casynth( LV2_Handle handle, uint32_t nframes)
{
    CASYNTH* synth = (CASYNTH*)handle;
    unsigned char i;
    float* buf = synth->output_p;
    LV2_Atom_Event event;
    uint32_t frame_no = 0;
    unsigned char* message;
    unsigned char type;

    for(i=0;i<nframes;i++)//start by filling buffer with 0s, we'll add to this
        buf[i] = 0;

    if (synth->midi_in_p)
    {
        LV2_ATOM_SEQUENCE_FOREACH(synth->midi_in_p, event)
        {
            if (event && event->body.type == synth->midi_event_type)//make sure its a midi event
            {
                message = (unsigned char*) LV2_ATOM_BODY(&event->body);
                if(!(*synth->channel_p) || message[0]&MIDI_CHANNEL_MASK == synth->channel_p+1)
                {
                    type = message[0]&MIDI_TYPE_MASK;

                    if(type == MIDI_NOTE_ON)
                    {

                        //update current position
                        frame_no = event->time.frames;
                    }
                    else if(type == MIDI_NOTE_OFF)
                    {

                        //update current position
                        frame_no = event->time.frames;
                    }
                    else if(type == MIDI_CONTROL_CHANGE)
                    {

                        //update current position
                        frame_no = event->time.frames;
                    }
                    else if(type == MIDI_PITCHBEND)
                    {
                        //update current position
                        frame_no = event->time.frames;
                    }

                }
            }
        }
    }
    else//no events probably can just fall through
    {

    }
}
