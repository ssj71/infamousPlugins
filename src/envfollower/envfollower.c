//Spencer Jackson
//envfollower.c
#include<envfollower.h>
#include<constants.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<lv2.h>
#include<lv2/lv2plug.in/ns/ext/urid/urid.h>
#include<lv2/lv2plug.in/ns/ext/midi/midi.h>
#include<lv2/lv2plug.in/ns/ext/atom/util.h>
#include "lv2/lv2plug.in/ns/ext/time/time.h"
#include "lv2/lv2plug.in/ns/ext/atom/forge.h"
#include "rms_calc.h"


typedef struct _ENVFOLLOWER
{
    float sample_time;

    float current;
    float prev;
    uint8_t mout;
    uint8_t mprev;

    double sum;
    float out;

    float atime;
    float up[3];
    float dtime;
    float dn[3];

    RMS_CALC rms_calc;

    //midi
    LV2_URID_Map* urid_map;
    LV2_URID midi_event_type;
    LV2_Atom_Forge forge;
    LV2_Atom_Forge_Frame frame;

    //ports
    float* input_p;
    float* output_p;
    float* cv_out_p;
    LV2_Atom_Sequence* midi_out_p;
    float* ctl_in_p;
    float* ctl_out_p;

    float* channel_p;
    float* control_p;
    float* cv_p;
    float* min_p;
    float* max_p;
    float* rev_p;

    float* cmin_p;
    float* cmax_p;
    float* crev_p;

    float* peakrms_p;
    float* threshold_p;
    float* saturation_p;
    float* atime_p;
    float* dtime_p;
} ENVFOLLOWER;

//main functions
LV2_Handle init_envfollower(const LV2_Descriptor *descriptor,double sample_rate, const char *bundle_path,const LV2_Feature * const* host_features)
{
    ENVFOLLOWER* plug = malloc(sizeof(ENVFOLLOWER));

    plug->sample_time = 1/sample_rate;

    plug->current = 0;
    plug->prev = 0;
    plug->mout = 0;
    plug->mprev = 0;
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

    rms_init(&plug->rms_calc,64);

    return plug;
}

LV2_Handle init_midi_envfollower(const LV2_Descriptor *descriptor,double sample_rate, const char *bundle_path,const LV2_Feature * const* host_features)
{
    ENVFOLLOWER* plug = init_envfollower(descriptor,sample_rate, bundle_path,host_features);
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
    else if(port == CTL_IN)	plug->ctl_in_p = (float*)data;
    else if(port == CTL_OUT)    plug->ctl_out_p = (float*)data;
    else if(port == CHANNEL)    plug->channel_p = (float*)data;
    else if(port == CONTROL_NO) plug->control_p = (float*)data;
    else if(port == MINV)       plug->min_p = (float*)data;
    else if(port == MAXV)       plug->max_p = (float*)data;
    else if(port == REVERSE)    plug->rev_p = (float*)data;
    else if(port == PEAKRMS)    plug->peakrms_p = (float*)data;
    else if(port == THRESHOLD)  plug->threshold_p = (float*)data;
    else if(port == SATURATION) plug->saturation_p = (float*)data;
    else if(port == ATIME)      plug->atime_p = (float*)data;
    else if(port == DTIME)      plug->dtime_p = (float*)data;
}

void connect_envCV_ports(LV2_Handle handle, uint32_t port, void *data)
{
    ENVFOLLOWER* plug = (ENVFOLLOWER*)handle;
    if(port == INPUT)           plug->input_p = (float*)data;
    else if(port == OUTPUT)     plug->output_p = (float*)data;
    else if(port == CV_OUT)     plug->cv_out_p = (float*)data;
    else if(port == CTL_IN)	plug->ctl_in_p = (float*)data;
    else if(port == CTL_OUT)    plug->ctl_out_p = (float*)data;
    else if(port == PEAKRMS)    plug->peakrms_p = (float*)data;
    else if(port == THRESHOLD)  plug->threshold_p = (float*)data;
    else if(port == SATURATION) plug->saturation_p = (float*)data;
    else if(port == ATIME)      plug->atime_p = (float*)data;
    else if(port == DTIME)      plug->dtime_p = (float*)data;
    else if(port == CMINV)      plug->cmin_p = (float*)data;
    else if(port == CMAXV)      plug->cmax_p = (float*)data;
    else if(port == CREVERSE)   plug->crev_p = (float*)data;
}

void run_envfollower( LV2_Handle handle, uint32_t nframes)
{
    ENVFOLLOWER* plug = (ENVFOLLOWER*)handle;
    LV2_Atom midiatom;
    uint32_t i;
    float *buf = plug->input_p;
    uint8_t msg[3];
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

    *plug->ctl_in_p = 0;
    *plug->ctl_out_p = 0;

    //recalculate filter coefficients as necessary
    if(plug->atime != *plug->atime_p)
    {
        plug->atime = *plug->atime_p;
        float tmp = 2.2*plug->sample_time;
        float den = 2.0*plug->atime + tmp;
        plug->up[0] = (2.0 - plug->sample_time)*plug->atime/den;
        plug->up[1] = tmp/den;
        plug->up[2] = plug->sample_time*plug->atime/den;
    }
    if(plug->dtime != *plug->dtime_p)
    {
        plug->dtime = *plug->dtime_p;
        float tmp = 2.2*plug->sample_time;
        float den = 2.0*plug->dtime + tmp;
        plug->dn[0] = (2.0 - plug->sample_time)*plug->dtime/den;
        plug->dn[1] = tmp/den;
        plug->dn[2] = plug->sample_time*plug->dtime/den;
    }

    //process data
    for(i=0; i<nframes; i++)
    {
        //get values
        peak = buf[i]>0?buf[i]:-buf[i];
        rms = rms_shift(&plug->rms_calc,buf[i]);

        plug->prev = plug->current;
        plug->current = (1.0 - *plug->peakrms_p)*peak + *plug->peakrms_p*rms;

        if(plug->current >= plug->out)
        {
            plug->out = plug->up[0]*plug->out + plug->up[1]*plug->current + plug->up[2]*plug->prev;
        }
        else
        {
            plug->out = plug->dn[0]*plug->out + plug->dn[1]*plug->current + plug->dn[2]*plug->prev;
        }
        *plug->ctl_in_p += plug->current;

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

        if(*plug->rev_p)
        {
            plug->mout = *plug->max_p - plug->mout + *plug->min_p;
        }

        if(plug->mout!=plug->mprev)
        {
            //make event
            msg[0] = MIDI_CONTROL_CHANGE + (uint8_t)(*plug->channel_p - 1);
            msg[1] = MIDI_DATA_MASK & (uint8_t)*plug->control_p;
            msg[2] = MIDI_DATA_MASK & plug->mout;

            midiatom.type = plug->midi_event_type;
            midiatom.size = 3;//midi CC
            lv2_atom_forge_frame_time(&plug->forge,i);
            lv2_atom_forge_raw(&plug->forge,&midiatom,sizeof(LV2_Atom));
            lv2_atom_forge_raw(&plug->forge,msg,3);
            lv2_atom_forge_pad(&plug->forge,3+sizeof(LV2_Atom));
        }
        plug->mprev = plug->mout;
        *plug->ctl_out_p += plug->mout/127.0;

        //finally copy the intput to the output
        plug->output_p[i] = buf[i];
    }

    //do average for output controls
    *plug->ctl_in_p /= nframes;
    *plug->ctl_out_p /= nframes;
}

void run_envfollowerCV( LV2_Handle handle, uint32_t nframes)
{
    ENVFOLLOWER* plug = (ENVFOLLOWER*)handle;
    uint32_t i;
    float *buf = plug->input_p;
    float peak;
    float rms;
    float sat = *plug->saturation_p;
    float cmax = *plug->cmax_p;
    if(sat <= *plug->threshold_p)
    {
        cmax = *plug->cmin_p;
    }
    if(cmax < *plug->cmin_p)
    {
        cmax = *plug->cmin_p;
    }
    float cmapping = (cmax - *plug->cmin_p)/(sat - *plug->threshold_p);

    *plug->ctl_in_p = 0;
    *plug->ctl_out_p = 0;

    //recalculate filter coefficients as necessary
    if(plug->atime != *plug->atime_p)
    {
        plug->atime = *plug->atime_p;
        float tmp = 2.2*plug->sample_time;
        float den = 2.0*plug->atime + tmp;
        plug->up[0] = (2.0 - plug->sample_time)*plug->atime/den;
        plug->up[1] = tmp/den;
        plug->up[2] = plug->sample_time*plug->atime/den;
    }
    if(plug->dtime != *plug->dtime_p)
    {
        plug->dtime = *plug->dtime_p;
        float tmp = 2.2*plug->sample_time;
        float den = 2.0*plug->dtime + tmp;
        plug->dn[0] = (2.0 - plug->sample_time)*plug->dtime/den;
        plug->dn[1] = tmp/den;
        plug->dn[2] = plug->sample_time*plug->dtime/den;
    }

    //process data
    for(i=0; i<nframes; i++)
    {
        //get values
        peak = buf[i]>0?buf[i]:-buf[i];
        rms = rms_shift(&plug->rms_calc,buf[i]);

        plug->prev = plug->current;
        plug->current = (1.0 - *plug->peakrms_p)*peak + *plug->peakrms_p*rms;

        if(plug->current >= plug->out)
        {
            plug->out = plug->up[0]*plug->out + plug->up[1]*plug->current + plug->up[2]*plug->prev;
        }
        else
        {
            plug->out = plug->dn[0]*plug->out + plug->dn[1]*plug->current + plug->dn[2]*plug->prev;
        }
        *plug->ctl_in_p += plug->current;

        //now handle the Control Voltage port
        if(plug->out <= *plug->threshold_p)
        {
            plug->cv_out_p[i] = *plug->cmin_p;
        }
        else if(plug->out >= *plug->saturation_p)
        {
            plug->cv_out_p[i] = *plug->cmax_p;
        }
        else
        {
            plug->cv_out_p[i] = cmapping*(plug->out - *plug->threshold_p) + *plug->cmin_p;
        }
        if(*plug->crev_p)
        {
            plug->cv_out_p[i] = *plug->cmax_p - plug->cv_out_p[i] + *plug->cmin_p;
        }

        *plug->ctl_out_p += plug->cv_out_p[i];

        //finally copy the intput to the output
        plug->output_p[i] = buf[i];
    }

    //do average for output controls
    *plug->ctl_in_p /= nframes;
    *plug->ctl_out_p /= nframes;
}


void cleanup_envfollower(LV2_Handle handle)
{
    ENVFOLLOWER* plug = (ENVFOLLOWER*) handle;
    rms_deinit(&plug->rms_calc);
    free(plug);
}


//lv2 stuff
static const LV2_Descriptor envfollower_descriptor=
{
    ENVFOLLOWER_URI,
    init_midi_envfollower,
    connect_envfollower_ports,
    NULL,//activate
    run_envfollower,
    NULL,//deactivate
    cleanup_envfollower,
    NULL//extension
};

static const LV2_Descriptor envfollowerCV_descriptor=
{
    ENVFOLLOWERCV_URI,
    init_envfollower,
    connect_envCV_ports,
    NULL,//activate
    run_envfollowerCV,
    NULL,//deactivate
    cleanup_envfollower,
    NULL//extension
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index)
    {
    case 0:
        return &envfollower_descriptor;
    case 1:
        return &envfollowerCV_descriptor;
    default:
        return NULL;
    }
}
