//Spencer Jackson
//envfollower.c
#include<envfollower.h>
#include<constants.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>


//main functions
LV2_Handle init_envfollower(const LV2_Descriptor *descriptor,double sample_rate, const char *bundle_path,const LV2_Feature * const* host_features)
{
    ENVFOLLOWER* plug = malloc(sizeof(ENVFOLLOWER));
    LV2_URID_Map *urid_map;

    plug->sample_time = 1/sample_rate;

    plug->current = 0;
    plug->prev = 0;
    plug->mout = 0;
    plug->mprev = 0;
    plug->nsum = 1;
    plug->sum = 0;
    plug->out = 0;

    plug->atime = .1;
    float tmp = 2.2*plug->sample_time;
    float den = 2*plug->atime + tmp;
    plug->up[0] = (2 - plug->sample_time)*plug->atime/den;
    plug->up[1] = tmp/den;
    plug->up[2] = plug->sample_time*plug->atime/den;

    plug->dtime = .1;
    den = 2*plug->dtime + tmp;
    plug->dn[0] = (2 - plug->sample_time)*plug->dtime/den;
    plug->dn[1] = tmp/den;
    plug->dn[2] = plug->sample_time*plug->dtime/den;

    //get urid map value for midi events
    for (int i = 0; host_features[i]; i++)
    {
        if (strcmp(host_features[i]->URI, LV2_URID__map) == 0)
        {
            plug->urid_map = (LV2_URID_Map *) host_features[i]->data;
            if (plug->urid_map)
            {
                plug->midi_event_type = plug->urid_map->map(plug->urid_map->handle, LV2_MIDI__MidiEvent);
                break;
            }
        }
    }

    lv2_atom_forge_init(&plug->forge,plug->urid_map);

    return plug;
}

void connect_envfollower_ports(LV2_Handle handle, uint32_t port, void *data)
{
    ENVFOLLOWER* plug = (ENVFOLLOWER*)handle;
    if(port == INPUT)           plug->input_p = (float*)data;
    else if(port == OUTPUT)     plug->output_p = (float*)data;
    else if(port == MIDI_OUT)   plug->midi_out_p = (LV2_Atom_Sequence*)data;
    else if(port == CHANNEL)    plug->channel_p = (float*)data;
    else if(port == CONTROL_NO) plug->control_p = (float*)data;
    else if(port == MINV)       plug->min_p = (float*)data;
    else if(port == MAXV)       plug->max_p = (float*)data;
    else if(port == PEAKRMS)    plug->peakrms_p = (float*)data;
    else if(port == THRESHOLD)  plug->threshold_p = (float*)data;
    else if(port == SATURATION) plug->saturation_p = (float*)data;
    else if(port == ATIME)      plug->atime_p = (float*)data;
    else if(port == DTIME)      plug->dtime_p = (float*)data;
    else puts("UNKNOWN PORT YO!!");
}


void run_envfollower( LV2_Handle handle, uint32_t nframes)
{
    ENVFOLLOWER* plug = (ENVFOLLOWER*)handle;
    LV2_Atom midiatom;
    uint32_t i;
    float *buf = plug->input_p;
    unsigned char msg[3];
    float peak;
    float rms;
    float sat = *plug->saturation_p;
    float max = *plug->max_p;
    if(sat <= *plug->threshold_p)
    {
        max = *plug->min_p;
    }
    if(max < *plug->min_p)
    {
        max = *plug->min_p;
    }
    float mapping = (max - *plug->min_p)/(sat - *plug->threshold_p);


    //get midi port ready
    const uint32_t capacity = plug->midi_out_p->atom.size;
    lv2_atom_forge_set_buffer(&plug->forge,(uint8_t*)plug->midi_out_p, capacity);
    lv2_atom_forge_sequence_head(&plug->forge, &plug->frame, 0);
    midiatom.type = plug->midi_event_type;
    midiatom.size = 3;//midi CC

    //recalculate filter coefficients as necessary
    if(plug->atime != *plug->atime_p)
    {
        plug->atime = *plug->atime_p;
        float tmp = 2.2*plug->sample_time;
        float den = 2*plug->atime + tmp;
        plug->up[0] = (2 - plug->sample_time)*plug->atime/den;
        plug->up[1] = tmp/den;
        plug->up[2] = plug->sample_time*plug->atime/den;
    }
    if(plug->dtime != *plug->dtime_p)
    {
        plug->dtime = *plug->dtime_p;
        float tmp = 2.2*plug->sample_time;
        float den = 2*plug->dtime + tmp;
        plug->dn[0] = (2 - plug->sample_time)*plug->dtime/den;
        plug->dn[1] = tmp/den;
        plug->dn[2] = plug->sample_time*plug->dtime/den;
    }

    //process data
    for(i=0;i<nframes;i++)
    {
        //get values
        peak = buf[i]>0?buf[i]:-buf[i];
        plug->sum += buf[i]*buf[i];
        rms = sqrt(plug->sum/plug->nsum++);

        plug->prev = plug->current;
        plug->current = (1 - *plug->peakrms_p)*peak + *plug->peakrms_p*rms;

        if(plug->current >= plug->out)
        {
            plug->out = plug->up[0]*plug->out + plug->up[1]*plug->current + plug->up[2]*plug->prev;
        }
        else
        {
            plug->out = plug->dn[0]*plug->out + plug->dn[1]*plug->current + plug->dn[2]*plug->prev;
        }

        //now map to the midi values
        if(plug->out <= *plug->threshold_p)
        {
            plug->mout = *plug->min_p;
        }
        else if(plug->out >= *plug->saturation_p)
        {
            plug->mout = *plug->max_p;
        }
        else
        {
            plug->mout = mapping*(plug->out - *plug->threshold_p) + *plug->min_p;
        }

        if(plug->mout!=plug->mprev)
        {
            //make event
            msg[0] = MIDI_CONTROL_CHANGE + (unsigned char)(*plug->channel_p - 1);
            msg[1] = MIDI_DATA_MASK & (unsigned char)*plug->control_p;
            msg[2] = MIDI_DATA_MASK & plug->mout;

            midiatom.type = plug->midi_event_type;
            midiatom.size = 3;//midi CC
            lv2_atom_forge_frame_time(&plug->forge,i);
            lv2_atom_forge_raw(&plug->forge,&midiatom,sizeof(LV2_Atom));
            lv2_atom_forge_raw(&plug->forge,msg,3);
            lv2_atom_forge_pad(&plug->forge,3+sizeof(LV2_Atom));


        }
        plug->mprev = plug->mout;

        plug->output_p[i] = buf[i];
    }
   /* msg[0] = MIDI_CONTROL_CHANGE + (unsigned char)0;
    msg[1] = MIDI_DATA_MASK & (unsigned char)1;
    msg[2] = MIDI_DATA_MASK & 64;

    lv2_atom_forge_frame_time(&plug->forge,i);
    lv2_atom_forge_raw(&plug->forge,&midiatom,sizeof(LV2_Atom));
    lv2_atom_forge_raw(&plug->forge,msg,3);
    lv2_atom_forge_pad(&plug->forge,3+sizeof(LV2_Atom));*/

}


void cleanup_envfollower(LV2_Handle handle)
{
    ENVFOLLOWER* plug = (ENVFOLLOWER*) handle;
    free(plug);
}

