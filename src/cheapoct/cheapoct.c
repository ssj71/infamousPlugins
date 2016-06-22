//Spencer Jackson
//cheapoct.c
#include<lv2.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"cheapoct.h"


#define TOLERANCE .0010

typedef struct _OCTAVER
{
    uint16_t w; //current write point in buffer
    uint16_t r; //read point in buffer
    uint8_t  c; //counter for every other increment (ZOH)
    uint16_t mask; //mask for circulating pointers
    uint8_t xfade; //length of crossfade
    uint8_t xc; //counter for crossfade
    uint8_t xm; //mask for crossfade count
    uint8_t ready; //flag for if we have moved sufficiently along the wave to start looking for another jump
    uint16_t mingap; //distance to lowest found score

    float *buf;
    float minerr; //lowest found score

    float *input_p;
    float *output_p;
    float *tolerance_p;
    float *weight_p;
    float *dbg_p;
} OCTAVER;


void run_cheapoct(LV2_Handle handle, uint32_t nframes)
{
    OCTAVER* plug = (OCTAVER*)handle;
    float* in, *out, *buf, err;
    uint32_t i;
    uint16_t r,w,mask;
    uint8_t c;

    *plug->dbg_p = 0;

    in = plug->input_p;
    out = plug->output_p;
    buf = plug->buf;
    mask = plug->mask;
    r = plug->r;
    w = plug->w;
    c = plug->c;

    for(i=0; i<nframes && plug->xc; i++)
    {
        buf[w] = in[i];
        out[i] = in[i] + (plug->xc--/((float)plug->xfade+1.0))*(buf[r] - in[i]);

        r += c++&0x01; //oh look. A zero-order hold
        r &= mask;
        w++;
        w &= mask;
    }
    for( ; i<nframes; i++)
    {
        buf[w] = in[i];
        out[i] = buf[r];// + in[i];

        r += c++&0x01; //oh look. A zero-order hold
        r &= mask;
        w++;
        w &= mask;

        if((w+plug->xfade)&mask == r)
        {
            plug->xc = plug->xfade;
            for( ; i<nframes && plug->xc; i++)
            {
                buf[w] = in[i];
                out[i] = in[i] + (plug->xc--/((float)plug->xfade+1.0))*(buf[r] - in[i]);

                r += c++&0x01; //oh look. A zero-order hold
                r &= mask;
                w++;
                w &= mask;
            }
            //w should == r here
        }
    }




    plug->r = r;
    plug->w = w;
    plug->c = c;

    return;
}

LV2_Handle init_cheapoct(const LV2_Descriptor *descriptor,double sample_freq, const char *bundle_path,const LV2_Feature * const* host_features)
{
    OCTAVER* plug = malloc(sizeof(OCTAVER));

    uint16_t tmp;
    tmp = 0x0400;//10 bits 1024
    if(sample_freq<100000)//88.1 or 96.1kHz
        tmp = tmp>>1;//09 bits
    if(sample_freq<50000)//44.1 or 48kHz
        tmp = tmp>>1;//08 256
    plug->buf = (float*)malloc(tmp*sizeof(float));
    plug->r = 0;
    plug->w = 0;
    plug->c = 0;
    plug->mask = tmp-1;
    plug->xfade = (tmp>>2)-1;//4 bits 16
    plug->xc = 0;

    plug->ready = 1;
    plug->minerr = 1;
    plug->mingap = 0;

    plug->buf[0] = 0;
    plug->buf[tmp-1] = 0;
    return plug;
}

void connect_cheapoct_ports(LV2_Handle handle, uint32_t port, void *data)
{
    OCTAVER* plug = (OCTAVER*)handle;
    switch(port)
    {
    case IN:
        plug->input_p = (float*)data;
        break;
    case OUT:
        plug->output_p = (float*)data;
        break;
    case TOL:
        plug->tolerance_p = (float*)data;
        break;
    case WEIGHT:
        plug->weight_p = (float*)data;
        break;
    case DBG:
        plug->dbg_p = (float*)data;
        break;
    default:
        puts("UNKNOWN PORT YO!!");
    }
}

void cleanup_cheapoct(LV2_Handle handle)
{
    OCTAVER* plug = (OCTAVER*)handle;
    free(plug->buf);
    free(plug);
}

static const LV2_Descriptor cheapoct_descriptor=
{
    CHEAPOCT_URI,
    init_cheapoct,
    connect_cheapoct_ports,
    0,//activate
    run_cheapoct,
    0,//deactivate
    cleanup_cheapoct,
    0//extension
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index)
    {
    case 0:
        return &cheapoct_descriptor;
    default:
        return 0;
    }
}
