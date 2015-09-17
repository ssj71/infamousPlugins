//Spencer Jackson
//ewham.c
#include<lv2.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"ewham.h"
#include"retuner.h"

#define EWHAM_URI "http://ssj71.github.io/infamousPlugins/plugs.html#ewham"

typedef struct _EWHAM
{
    TUNERHANDLE tuner;
    double sample_freq;
    float prev;
    unsigned int count;

    float *input_p;
    float *output_p;
    float *expression_p;
    float *start_p;
    float *finish_p;
    float *mode_p;
    float *lock_p;
    float *latency_p;
} EWHAM;

enum _MODES
{
    CLASSIC = 0,
    HARMONIZER,
    CHORUS
};

enum _LOCK
{
    NONE = 0,
    LAND_ON_SEMITONE,
    LOCK_TO_SEMITONE
};

void run_ewham(LV2_Handle handle, uint32_t nframes)
{
    EWHAM* plug = (EWHAM*)handle;
    float current = (1-*plug->expression_p)*(*plug->start_p) + *plug->expression_p*(*plug->finish_p);
    int currint;

    if(*plug->mode_p != CHORUS)
    {
        if(*plug->lock_p == LAND_ON_SEMITONE && plug->prev == current)
        {
            plug->prev = current;
            if(plug->count++ > 5)
            {
                currint = current + .5;
                current = currint;
            }
        }
        else if(*plug->lock_p == LOCK_TO_SEMITONE)
        {
            plug->prev = current;
            currint = current + .5;
            current = currint;
        }
        else
        {
            plug->prev = current;
            plug->count = 0;
        }

        RetunerSetOffset(plug->tuner,current);
    }
    else
    {
        RetunerSetOffset(plug->tuner,current/100.0);
    }

    if(*plug->mode_p != CLASSIC)
    {
        RetunerSetDryGain(plug->tuner,.9);
    }
    else
    {
        RetunerSetDryGain(plug->tuner,0);
    }

    RetunerProcess(plug->tuner,plug->input_p,plug->output_p,nframes);
    *plug->latency_p = RetunerGetLatency(plug->tuner);

    return;
}

LV2_Handle init_ewham(const LV2_Descriptor *descriptor,double sample_freq, const char *bundle_path,const LV2_Feature * const* host_features)
{
    EWHAM* plug = malloc(sizeof(EWHAM));
    plug->count = plug->prev = 0;
    plug->tuner = RetunerAlloc(sample_freq);

    return plug;
}

void connect_ewham_ports(LV2_Handle handle, uint32_t port, void *data)
{
    EWHAM* plug = (EWHAM*)handle;
    switch(port)
    {
    case IN:
        plug->input_p = (float*)data;
        break;
    case OUT:
        plug->output_p = (float*)data;
        break;
    case EXPRESSION:
        plug->expression_p = (float*)data;
        break;
    case START:
        plug->start_p = (float*)data;
        break;
    case FINISH:
        plug->finish_p = (float*)data;
        break;
    case MODE:
        plug->mode_p = (float*)data;
        break;
    case LOCK:
        plug->lock_p = (float*)data;
        break;
    case LATENCY:
        plug->latency_p = (float*)data;
        break;
    default:
        puts("UNKNOWN PORT YO!!");
    }
}

void cleanup_ewham(LV2_Handle handle)
{
    EWHAM* plug = (EWHAM*)handle;
    RetunerFree(plug->tuner);
    free(plug);
}

static const LV2_Descriptor ewham_descriptor=
{
    EWHAM_URI,
    init_ewham,
    connect_ewham_ports,
    0,//activate
    run_ewham,
    0,//deactivate
    cleanup_ewham,
    0//extension
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index)
    {
    case 0:
        return &ewham_descriptor;
    default:
        return 0;
    }
}
