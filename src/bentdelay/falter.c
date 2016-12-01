    //Spencer Jackson
//falter.c
#include<lv2.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"falter.h"


typedef struct _FALTER
{
    uint16_t w;
    float *buf;
    uint16_t mask;
    float sample_rate;

    float *input_p;
    float *output_p;
    float *decimate_p;
    float *delay_p;
} FALTER;


void run_falter(LV2_Handle handle, uint32_t nframes)
{
    FALTER* plug = (FALTER*)handle;
    float* in, *out, *buf;
    uint16_t i,w, pdelay, ndelay, mask, downmask;

    in = plug->input_p;
    out = plug->output_p;
    buf = plug->buf;
    w = plug->w;
    mask = plug->mask;
    downmask = (mask<<(uint8_t)*plug->decimate_p)&mask;


    pdelay = ndelay = 0;
    if(*plug->delay_p < 0)
        ndelay = -*plug->delay_p*plug->sample_rate/1000;
    else
        pdelay = *plug->delay_p*plug->sample_rate/1000;

    for (i=0;i<nframes;i++)
    {
        buf[w] = in[i];
        out[i] = buf[(w-pdelay)&mask] - buf[(w-ndelay)&downmask];
        //buf[w] += fb*out[i]
        w++;
        w &= mask;
    } 

    plug->w = w;

    return;
}

LV2_Handle init_falter(const LV2_Descriptor *descriptor,double sample_rate, const char *bundle_path,const LV2_Feature * const* host_features)
{
    uint16_t tmp;

    FALTER* plug = malloc(sizeof(FALTER));

    tmp = 0x8000;//for 196k
    if(sample_rate<100000)//88.2 or 96kHz
        tmp = tmp>>1;
    if(sample_rate<50000)//44.1 or 48kHz
        tmp = tmp>>1;
    plug->buf = (float*)malloc(tmp*sizeof(float));
    plug->w = 0;
    plug->mask = tmp-1;

    plug->sample_rate = sample_rate;

    return plug;
}

void connect_falter_ports(LV2_Handle handle, uint32_t port, void *data)
{
    FALTER* plug = (FALTER*)handle;
    switch(port)
    {
    case IN:
        plug->input_p = (float*)data;
        break;
    case OUT:
        plug->output_p = (float*)data;
        break;
    case DECIMATE:
        plug->decimate_p = (float*)data;
        break;
    case DELAY:
        plug->delay_p = (float*)data;
        break;
    default:
        puts("UNKNOWN PORT YO!!");
    }
}

void cleanup_falter(LV2_Handle handle)
{
    FALTER* plug = (FALTER*)handle;
    free(plug->buf);
    free(plug);
}

static const LV2_Descriptor falter_descriptor=
{
    FALTER_URI,
    init_falter,
    connect_falter_ports,
    0,//activate
    run_falter,
    0,//deactivate
    cleanup_falter,
    0//extension
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index)
    {
    case 0:
        return &falter_descriptor;
    default:
        return 0;
    }
}
