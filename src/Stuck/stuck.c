//Spencer Jackson
//square.c
#include<lv2.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

#define STUCK_URI "http://infamousplugins.sourceforge.net/plugs.html#stuck"

enum states
{
    INACTIVE,
    FADE_IN,
    LOADING,
    LOADING_XFADE, 
    PLAYING,
    RELEASING,
    QUICK_RELEASING
};

typedef struct _STUCK
{
    unsigned short indx;
    unsigned short bufmask; 
    unsigned short xfade_size;
    unsigned char state;
    double sample_freq;
    
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
    uint32_t i,j,chunk=0;
    double slope;

    memcpy(plug->output_p,plug->input_p,nframes*sizeof(float));
    
    if(plug->state == INACTIVE)
    {//decide if triggered
        if(*plug->stick_it_p >= 1 || plug->trigger_p[nframes-1] >= 1)
        {
	    plug->state = LOADING;
	    plug->indx = 0;
	}
        else return;
    }
    else if(plug->state < RELEASING) 
    {//decide if released 
        if(*plug->stick_it_p < 1 || plug->trigger_p[nframes-1] < 1)
        {
	    plug->state = RELEASING;
	    plug->indx = 0;
	}
        else return;
    }
    else if(plug->state == RELEASING)
    {//decide if new trigger has been sent before release is complete
        if(*plug->stick_it_p >= 1 || plug->trigger_p[nframes-1] >= 1)
            plug->state = QUICK_RELEASING; 
    }

    for(i=0;i<nframes;)
    {    
        chunk = nframes - i;
	if(plug->state == FADE_IN)
	{
	    slope = *plug->drone_gain_p/(double)plug->xfade_size;
	    //decide if done with fade in in this period
	    if(plug->gain+chunk*slope >= *plug->drone_gain_p)
	    {
	        chunk = (*plug->drone_gain_p - plug->gain)/slope;
		plug->state = LOADING;
	    }
	    //load buffer and fade in
	    for(j=0;j<chunk;j++)
	    { 
	        plug->buf[plug->indx] = plug->input_p[i];
		plug->output_p[i++] += plug->gain*plug->buf[plug->indx++];
		plug->gain += slope;
	    }
	}
        else if(plug->state == LOADING)
	{   
	    slope = *plug->drone_gain_p/(double)chunk;
	    //decide if xfade will start in this period
            if(plug->indx+chunk >= plug->bufmask - plug->xfade_size)
	    {
	        chunk = plug->bufmask - plug->xfade_size - plug->indx;
		plug->state = LOADING_XFADE;
	    }
	    //load buffer
	    for(j=0;j<chunk;j++)
	    {
	        plug->buf[plug->indx] = plug->input_p[i];
		plug->output_p[i++] += plug->gain*plug->buf[plug->indx++];
		plug->gain += slope;
	    }
	}
	else if(plug->state == LOADING_XFADE)
	{
	    slope = *plug->drone_gain_p/(double)chunk;
	    //decide if xfade ends in this period
            if(plug->indx+chunk >= ~plug->bufmask)
	    {
	        chunk = ~plug->bufmask - plug->indx;
		plug->state = PLAYING;
	    }
	    //load buffer with xfade
	    double g = 0;
	    for(j=0;j<chunk;j++)
	    {
	        g = j/(double)(plug->xfade_size);
	        plug->buf[plug->indx] = (1.0-g)*plug->input_p[i] +g*plug->buf[j];
		plug->output_p[i++] += plug->gain*plug->buf[plug->indx++];
		plug->gain += slope;
		plug->indx &= plug->bufmask;
	    }
        }
        if(plug->state == PLAYING)
	{
	    slope = *plug->drone_gain_p/(double)chunk; 
	    for(j=0;j<chunk;j++)
	    { 
		plug->output_p[i++] += plug->gain*plug->buf[plug->indx++];
		plug->gain += slope;
		plug->indx &= plug->bufmask;
	    }
	}
	if(plug->state == RELEASING)
	{
	    slope = *plug->release_p*plug->sample_freq;
	    //decide if released in this period
	    if(plug->gain + chunk*slope <= 0)
	    {
	        chunk = plug->gain/slope;
		plug->state = INACTIVE; 
	    }
	    for(j=0;j<chunk;j++)
	    { 
		plug->output_p[i++] += plug->gain*plug->buf[plug->indx++];
		plug->gain += slope; 
		plug->indx &= plug->bufmask;
	    }
	    if(plug->gain <=0)
	    {
	        plug->indx = 0;
	    }
        }
	if(plug->state == QUICK_RELEASING)
	{
	    slope = -*plug->drone_gain_p/(double)plug->xfade_size;
	    //decide if released in this period
	    if(plug->gain + chunk*slope <= 0)
	    {
	        chunk = plug->gain/slope;
		plug->state = LOADING; 
	    }
	    for(j=0;j<chunk;j++)
	    { 
		plug->output_p[i++] += plug->gain*plug->buf[plug->indx++];
		plug->gain += slope;
		plug->indx &= plug->bufmask;
	    }
	    if(plug->gain <=0)
	    {
	        plug->indx = 0;
	    }
        }
    }
}

LV2_Handle init_stuck(const LV2_Descriptor *descriptor,double sample_freq, const char *bundle_path,const LV2_Feature * const* host_features)
{
    STUCK* plug = malloc(sizeof(STUCK));

    unsigned short tmp;
    plug->sample_freq = sample_freq; 
    tmp = 0x4000;//16384;14 bits
    if(sample_freq<100000)//88.1 or 96.1kHz
        tmp = tmp>>1;//13 bits
    if(sample_freq<50000)//44.1 or 48kHz
        tmp = tmp>>1;//12 bits
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
