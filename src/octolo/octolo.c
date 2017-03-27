    //Spencer Jackson
//octolo.c
#include<lv2.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"octolo.h"

//OCTOLO - octaver and tremolo had a baby and this is it


typedef struct _OCTOLO
{
    uint16_t w; //current write point in buffer
    float *buf;
    float r,ru,rd; //read point in buffer (up and dn oct)
    uint16_t prog; //number of samples passed in the period
    float sample_freq;
    float period;
    int8_t sign;

    float *input_p;
    float *output_p;
    float *period_p;
    float *wet_p;
    float *dry_p;
    float *dn_p;
    float *up_p;
    float *shape_p;
    float *seq_p;
    float *dbg_p;
} OCTOLO;

//
// sync         overlap (transient, repeat)
// 11           1 11
// 11           1 11
// 11           1 11
//
// 
// alt1     
// 0011         0 11
// 1100         1 11
// 0011         0 11
//
// alt2     
// 0011         0 11
// 0011         0 11
// 1100         1 11
//
// step
// 00000011     0 0011
// 11001100     1 1111
// 00110000     0 1100
//
// cycle up
// 000011       0 011
// 001100       0 110
// 110000       1 101
// 
// cyce dn
// 110000       1 101
// 001100       0 110
// 000011       0 011

void run_octolo(LV2_Handle handle, uint32_t nframes)
{
    OCTOLO* plug = (OCTOLO*)handle;
    float* in, *out, *buf;
    uint16_t i,r,w, chunk;


    *plug->dbg_p = 0;

    in = plug->input_p;
    out = plug->output_p;
    buf = plug->buf;
    r = plug->r;
    w = plug->w;


    //max period is 1.4 sec = .67
    for(i<0;i<=nframes;i++)
    {
        
    }

    plug->r = r;
    plug->w = w;

    return;
}

LV2_Handle init_octolo(const LV2_Descriptor *descriptor,double sample_freq, const char *bundle_path,const LV2_Feature * const* host_features)
{
    uint16_t i;

    OCTOLO* plug = malloc(sizeof(OCTOLO));

    //this makes the max period a function of samplerate, but you're dumb if you are using anything but 44100 or 48k
    plug->buf = (float*)calloc(0x10000,sizeof(float));
    plug->r = 0;
    plug->w = 0;
    plug->prog = 0;
    plug->sign = 5;
    plug->period = 5;

    plug->sample_freq = sample_freq;

    plug->buf[0] = 0;
    for(i=1;i;i++)
        plug->buf[i] = 0;
    return plug;
}

void connect_octolo_ports(LV2_Handle handle, uint32_t port, void *data)
{
    OCTOLO* plug = (OCTOLO*)handle;
    switch(port)
    {
    case IN:
        plug->input_p = (float*)data;
        break;
    case OUT:
        plug->output_p = (float*)data;
        break;
    case PERIOD:
        plug->period_p = (float*)data;
        break;
    case DRY:
        plug->dry_p = (float*)data;
        break;
    case WET:
        plug->wet_p = (float*)data;
        break;
    case OCTDOWN:
        plug->dn_p = (float*)data;
        break;
    case OCTUP:
        plug->up_p = (float*)data;
        break;
    case SHAPE:
        plug->shape_p = (float*)data;
        break;
    case SEQUENCE:
        plug->seq_p = (float*)data;
        break;
    case DBG:
        plug->dbg_p = (float*)data;
        break;
    default:
        puts("UNKNOWN PORT YO!!");
    }
}

void cleanup_octolo(LV2_Handle handle)
{
    OCTOLO* plug = (OCTOLO*)handle;
    free(plug->buf);
    free(plug);
}

static const LV2_Descriptor octolo_descriptor=
{
    OCTOLO_URI,
    init_octolo,
    connect_octolo_ports,
    0,//activate
    run_octolo,
    0,//deactivate
    cleanup_octolo,
    0//extension
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index)
    {
    case 0:
        return &octolo_descriptor;
    default:
        return 0;
    }
}
