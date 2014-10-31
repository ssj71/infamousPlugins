//Spencer Jackson
//lushlife.c
#include<lv2.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"lushlife.h"
#include"retuner.h"

#define LUSHLIFE_URI "http://infamousplugins.sourceforge.net/plugs.html#lushlife"

#define NWOOSH 6

typedef struct _LUSHLIFE
{
    TUNERHANDLE tuner;
    double sample_freq;
    float prev;
    unsigned int count;

    uint32_t latency;
    
    float *input_p;
    float *outputl_p;
    float *outputr_p;
    float *dry_gain_p;
    float *dry_pan_p;
    float *tune_p[NWOOSH];
    float *delay_p[NWOOSH];
    float *gain_p[NWOOSH];
    float *pan_p[NWOOSH];
    float *latency_p;
}LUSHLIFE;


void run_lushlife(LV2_Handle handle, uint32_t nframes)
{
    LUSHLIFE* plug = (LUSHLIFE*)handle;

    RetunerSetOffset(plug->tuner,0,1/100);
    RetunerSetDryGain(plug->tuner,0);
    RetunerSetLatency(plug->tuner,0,(uint32_t)*plug->delay_p);

    RetunerProcess(plug->tuner,plug->input_p,plug->outputl_p,plug->outputr_p,nframes);
    *plug->latency_p = plug->latency;

return;
}

LV2_Handle init_lushlife(const LV2_Descriptor *descriptor,double sample_freq, const char *bundle_path,const LV2_Feature * const* host_features)
{
    LUSHLIFE* plug = malloc(sizeof(LUSHLIFE));
    plug->count = plug->prev = 0;
    plug->tuner = RetunerAlloc(sample_freq, 1);

    plug->latency = RetunerGetLatency(plug->tuner,0);

    return plug;
}

void connect_lushlife_ports(LV2_Handle handle, uint32_t port, void *data)
{
    LUSHLIFE* plug = (LUSHLIFE*)handle;
    switch(port)
    {
    case IN:            plug->input_p = (float*)data;break;
    case OUTL:          plug->outputl_p = (float*)data;break;
    case OUTR:          plug->outputr_p = (float*)data;break;
    case DRY_GAIN:      plug->dry_gain_p = (float*)data;break;
    case DRY_PAN:       plug->dry_pan_p = (float*)data;break;
    case TUNE0:         plug->tune_p[0] = (float*)data;break;
    case DELAY0:        plug->delay_p[0] = (float*)data;break;
    case GAIN0:         plug->gain_p[0] = (float*)data;break;
    case PAN0:          plug->pan_p[0] = (float*)data;break;
    case LATENCY:       plug->latency_p = (float*)data;break;
    default:            puts("UNKNOWN PORT YO!!");
    }
}

void cleanup_lushlife(LV2_Handle handle)
{
    LUSHLIFE* plug = (LUSHLIFE*)handle;
    RetunerFree(plug->tuner);
    free(plug);
}

static const LV2_Descriptor lushlife_descriptor={
    LUSHLIFE_URI,
    init_lushlife,
    connect_lushlife_ports,
    0,//activate
    run_lushlife,
    0,//deactivate
    cleanup_lushlife,
    0//extension
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index) {
    case 0:
        return &lushlife_descriptor;
    default:
        return 0;
    }
}
