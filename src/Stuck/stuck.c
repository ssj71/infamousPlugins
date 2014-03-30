//Spencer Jackson
//square.c
#include<lv2.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#define STUCK_URI "http://infamousplugins.sourceforge.net/plugs.html#stuck"

enum states
{
    INACTIVE,
    LOADING,
    LOADING_XFADE,
    PLAYING,
    RELEASING
}

typedef struct _STUCK
{
    unsigned short indx;
    unsigned short bufmask; 
    unsigned short xfade_size;
    unsigned char state;
    double sample_rate;
    
    float *buf;
    float gain;

    float *input_p;
    float *output_p;
    float *trigger_p;
    float *stick_it_p;
    float *drone_gain_p;
    float *release_p;
}STUCK;

enum stuck_ports
{
    IN =0,
    OUT,
    TRIGGER,
    STICKIT,
    DRONEGAIN,
    RELEASE
};

void run_stuck(LV2_Handle handle, uint32_t nframes)
{
    STUCK* plug = (STUCK*)handle;
    uint32_t i;

    memcpy(plug->output_p,plug->input_p,nframes*sizeof(float));
    if(plug->state == INACTIVE)
    {//decide if triggered
        if(*plug->stick_it_p >= 1 || plug->trigger_p[nframes-1] >= 1)
           plug->state = LOADING;
        else return;
    }
    for(i=0;i<nfames;)
    {
        if(plug->state == LOADING)
	{//decidee if xfade will start in this period
	}
	if(plug->state == LOADING_XFADE)
	{//decide if xfade ends in this period
        }
        if(plug->state == PLAYING)
	{//decide if released
	}
	if(plug->state == RELEASING)
	{
        }
    }
}

LV2_Handle init_stuck(const LV2_Descriptor *descriptor,double sample_rate, const char *bundle_path,const LV2_Feature * const* host_features)
{
    STUCK* plug = malloc(sizeof(STUCK));

    unsigned char i;
    unsigned short tmp;
    plug->stample_rate = sample_rate; 
    tmp = 16384;
    if(sample_rate<100000)
        tmp = tmp>>1;
    if(sample_rate<50000)
        tmp = tmp>>1;
    plug->buf = malloc(tmp*sizeof(float));
    plug->bufmask = tmp-1;
    plug->xfade_size = tmp>>2;
    plug->indx = 0;
    plug->state = INACTIVE;

    return plug;
}

void connect_stuck_ports(LV2_Handle handle, uint32_t port, void *data)
{
    STUCK* plug = (STUCK*)handle;
    switch(port)
    {
    case IN:         plug->input_p = (float*)data;break;
    case OUT:        plug->output_p = (float*)data;break;
    case TRIGGER:    plug->trigger_p = (float*)data;break;
    case STICKIT:    plug->stick_it_p = (float*)data;break;
    case DRONEGAIN:  plug->drone_gain_p = (float*)data;break;
    case RELEASE:    plug->release_p = (float*)data;break; 
    default:         puts("UNKNOWN PORT YO!!");
    }
}

void cleanup_stuck(LV2_Handle handle)
{
    STUCK* plug = (STUCK*)handle;
    free(plug->buf);
    free(plug);
}

static const LV2_Descriptor stuck_descriptor={
    STUCK_URI,
    init_stuck,
    connect_stuck_ports,
    0,//activate
    run_stuck,
    0,//deactivate
    cleanup_stuck,
    0//extension
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index) {
    case 0:
        return &stuck_descriptor;
    default:
        return 0;
    }
}
