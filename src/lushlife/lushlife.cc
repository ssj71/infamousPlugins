//Spencer Jackson
//lushlife.c
#include<lv2.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"lushlife.h"
#include"retuner.h"


#define NWOOSH 6

typedef struct _LUSHLIFE
{
    Retuner* tuner;
    double sample_freq;
    float prev;
    unsigned int count;

    uint32_t latency;
    
    float *input_p;
    float *outputl_p;
    float *outputr_p;
    float *latency_p;

    float *mastergain_p;
    float *dry_gain_p;
    float *dry_pan_p;
    float *lfo_shape_p;
    float *sync_lfo_p;

    float *active_p[NWOOSH];
    float *shift_p[NWOOSH];
    float *slfoa_p[NWOOSH];
    float *slfof_p[NWOOSH];
    float *delay_p[NWOOSH];
    float *dlfoa_p[NWOOSH];
    float *dlfof_p[NWOOSH];
    float *gain_p[NWOOSH];
    float *pan_p[NWOOSH];
}LUSHLIFE;


void run_lushlife(LV2_Handle handle, uint32_t nframes)
{
    LUSHLIFE* plug = (LUSHLIFE*)handle;

    plug->tuner->set_gain(*plug->dry_gain_p**plug->mastergain_p,NWOOSH);
    plug->tuner->set_pan(*plug->dry_pan_p,NWOOSH);

    unsigned int i;
    for(i=0;i<NWOOSH;i++)
    {
        plug->tuner->set_active((int)*plug->active_p[i],i);
        plug->tuner->set_delay(*plug->delay_p[i],i);
        plug->tuner->set_corroffs(*plug->shift_p[i],i);
        plug->tuner->set_gain(*plug->gain_p[i]**plug->mastergain_p,i);
        plug->tuner->set_pan(*plug->pan_p[i],i);

        plug->tuner->set_offs_lfo_amount(*plug->slfoa_p[i],i);
        plug->tuner->set_offs_lfo_freq(*plug->slfof_p[i],i);
        plug->tuner->set_delay_lfo_amount(*plug->dlfoa_p[i],i);
        plug->tuner->set_delay_lfo_freq(*plug->dlfof_p[i],i);
    }
    plug->tuner->set_lfo_shape(*plug->lfo_shape_p);
    if(*plug->sync_lfo_p)
        plug->tuner->sync_lfos();

    plug->tuner->process(nframes,plug->input_p,plug->outputl_p,plug->outputr_p);

    *plug->latency_p = plug->latency;

return;
}

LV2_Handle init_lushlife(const LV2_Descriptor *descriptor,double sample_freq, const char *bundle_path,const LV2_Feature * const* host_features)
{
    LUSHLIFE* plug = (LUSHLIFE*)malloc(sizeof(LUSHLIFE));
    plug->tuner = new Retuner(sample_freq, NWOOSH+1);
    plug->sample_freq = sample_freq;

    plug->latency = plug->tuner->get_latency();

    plug->tuner->set_corrgain(0);
    //se last woosh as dry signal
    plug->tuner->set_active(1,NWOOSH);
    plug->tuner->set_corroffs(0,NWOOSH);

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
    case LATENCY:       plug->latency_p = (float*)data;break;

    case GAIN:          plug->mastergain_p = (float*)data;break;
    case DRY_GAIN:      plug->dry_gain_p = (float*)data;break;
    case DRY_PAN:       plug->dry_pan_p = (float*)data;break;
    case LFOSHAPE:      plug->lfo_shape_p = (float*)data;break;
    case SYNCLFO:       plug->sync_lfo_p = (float*)data;break;
    
    case ACTIVE0:       plug->active_p[0] = (float*)data;break;
    case SHIFT0:        plug->shift_p[0] = (float*)data;break;
    case SLFOA0:        plug->slfoa_p[0] = (float*)data;break;
    case SLFOF0:        plug->slfof_p[0] = (float*)data;break;
    case DELAY0:        plug->delay_p[0] = (float*)data;break;
    case DLFOA0:        plug->dlfoa_p[0] = (float*)data;break;
    case DLFOF0:        plug->dlfof_p[0] = (float*)data;break;
    case GAIN0:         plug->gain_p[0] = (float*)data;break;
    case PAN0:          plug->pan_p[0] = (float*)data;break;
    
    case ACTIVE1:       plug->active_p[1] = (float*)data;break;
    case SHIFT1:        plug->shift_p[1] = (float*)data;break;
    case SLFOA1:        plug->slfoa_p[1] = (float*)data;break;
    case SLFOF1:        plug->slfof_p[1] = (float*)data;break;
    case DELAY1:        plug->delay_p[1] = (float*)data;break;
    case DLFOA1:        plug->dlfoa_p[1] = (float*)data;break;
    case DLFOF1:        plug->dlfof_p[1] = (float*)data;break;
    case GAIN1:         plug->gain_p[1] = (float*)data;break;
    case PAN1:          plug->pan_p[1] = (float*)data;break;
    
    case ACTIVE2:       plug->active_p[2] = (float*)data;break;
    case SHIFT2:        plug->shift_p[2] = (float*)data;break;
    case SLFOA2:        plug->slfoa_p[2] = (float*)data;break;
    case SLFOF2:        plug->slfof_p[2] = (float*)data;break;
    case DELAY2:        plug->delay_p[2] = (float*)data;break;
    case DLFOA2:        plug->dlfoa_p[2] = (float*)data;break;
    case DLFOF2:        plug->dlfof_p[2] = (float*)data;break;
    case GAIN2:         plug->gain_p[2] = (float*)data;break;
    case PAN2:          plug->pan_p[2] = (float*)data;break;
    
    case ACTIVE3:       plug->active_p[3] = (float*)data;break;
    case SHIFT3:        plug->shift_p[3] = (float*)data;break;
    case SLFOA3:        plug->slfoa_p[3] = (float*)data;break;
    case SLFOF3:        plug->slfof_p[3] = (float*)data;break;
    case DELAY3:        plug->delay_p[3] = (float*)data;break;
    case DLFOA3:        plug->dlfoa_p[3] = (float*)data;break;
    case DLFOF3:        plug->dlfof_p[3] = (float*)data;break;
    case GAIN3:         plug->gain_p[3] = (float*)data;break;
    case PAN3:          plug->pan_p[3] = (float*)data;break;
    
    case ACTIVE4:       plug->active_p[4] = (float*)data;break;
    case SHIFT4:        plug->shift_p[4] = (float*)data;break;
    case SLFOA4:        plug->slfoa_p[4] = (float*)data;break;
    case SLFOF4:        plug->slfof_p[4] = (float*)data;break;
    case DELAY4:        plug->delay_p[4] = (float*)data;break;
    case DLFOA4:        plug->dlfoa_p[4] = (float*)data;break;
    case DLFOF4:        plug->dlfof_p[4] = (float*)data;break;
    case GAIN4:         plug->gain_p[4] = (float*)data;break;
    case PAN4:          plug->pan_p[4] = (float*)data;break;
    
    case ACTIVE5:       plug->active_p[5] = (float*)data;break;
    case SHIFT5:        plug->shift_p[5] = (float*)data;break;
    case SLFOA5:        plug->slfoa_p[5] = (float*)data;break;
    case SLFOF5:        plug->slfof_p[5] = (float*)data;break;
    case DELAY5:        plug->delay_p[5] = (float*)data;break;
    case DLFOA5:        plug->dlfoa_p[5] = (float*)data;break;
    case DLFOF5:        plug->dlfof_p[5] = (float*)data;break;
    case GAIN5:         plug->gain_p[5] = (float*)data;break;
    case PAN5:          plug->pan_p[5] = (float*)data;break;
    default:            puts("UNKNOWN PORT YO!!");
    }
}

void cleanup_lushlife(LV2_Handle handle)
{
    LUSHLIFE* plug = (LUSHLIFE*)handle;
    delete plug->tuner;
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
