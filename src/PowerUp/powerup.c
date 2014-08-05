//Spencer Jackson
//stuck.c
#include<lv2.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

#define POWERUP_URI "http://infamousplugins.sourceforge.net/plugs.html#powerup"
//#define CV_PORTS

typedef struct _POWERUP
{
    unsigned long w;//current write point in buffer
    unsigned long r;//current read point in buffer
    unsigned long t;//nframes processed after trigger
    unsigned long bufmask;//size of buffer 
    unsigned long max_latency;
    double sample_freq;
    
    float *buf;
    float indx; 
    float dcprevin;
    float dcprevout;
    
    float startup_curve;
    float startup_time;

    float *input_p;
    float *output_p;
    float *trigger_p;
    float *pull_the_plug_p;
    float *startup_time_p;
    float *startup_curve_p;
    float *latency_p;
    float *dbg_p;
}POWERUP;

enum _POWERUP_PORTS
{
    IN =0,
    OUT,
    PULL_THE_PLUG,
    DECAY_TIME,
    DECAY_CURVE,
    TRIGGER,
    LATENCY,
    DBG
};

void run_powerup(LV2_Handle handle, uint32_t nframes)
{
    POWERUP* plug = (POWERUP*)handle;
    uint32_t i=0;
    float startup_length = (float)(*plug->startup_time*plug->sample_freq);
    
#ifdef CV_PORTS
    if(*plug->pull_the_plug_p >= 1 || plug->trigger_p[nframes-1] >= 1)
#else
    if(*plug->pull_the_plug_p>= 1)
#endif
    {
        //triggered, start cow face
	if(!dcprevout)
	{
	    //just starting, lock in values 
	    plug->startup_time = *plug->startup_time_p;
	    plug->startup_curve = *plug->startup_curve_p;
            startup_length = (float)(*plug->startup_time*plug->sample_freq);
	    //calculate start position
	    if(*plug->startup_curve > 0)//logarithmic (convex)
	    {
		//plug->indx += .1*log2(1024-1023*plug->t/startup_length);
		plug->indx += 1/(*plug->startup_curve_p)*log2(exp_startup - (exp_startup-1)*plug->t/startup_length);
		for(i=0;i<startup_length;i++);
		{
		    //add
		}
	    }
	    else if(*plug->startup_curve == 0)//linear
	    {
		plug->indx = (plug->w - (startup_length - (startup_length+1)/2))&plug->bufmask;
	    }
	    else//exponential (concave)
	    {
		//plug->indx += exp2(-10.0*plug->t/startup_length);
		plug->indx += (exp_startup*exp2(plug->t**plug->startup_curve_p/startup_length) - 1)/(exp_startup - 1);
	    }
	    plug->indx = 1.5;//not really
	    plug->r = ((unsigned long)plug->indx)&plug->bufmask;
	    dcprevin = plug->buf[plug->r];
	}

	float a,b,c,d,x,tmp,exp_startup;
	exp_startup = exp2(*plug->startup_curve>0?*plug->startup_curve:-*plug->startup_curve);

        a = plug->buf[(plug->r-1)&plug->bufmask];
	b = plug->buf[plug->r&plug->bufmask];
	c = plug->buf[(plug->r+1)&plug->bufmask];
	d = plug->buf[(plug->r+2)&plug->bufmask];

	for(i=0;i<nframes && plug->t<=startup_length;i++)
	{
	    //increment indx the amount for current (starting up) sample rate
	    if(*plug->startup_curve_p > 0)//logarithmic (convex)
	    {
		//plug->indx += .1*log2(1024-1023*plug->t/startup_length);
		plug->indx += 1 - 1/(*plug->startup_curve_p)*log2(exp_startup - (exp_startup-1)*plug->t/startup_length);
	    }
	    else if(*plug->startup_curve_p == 0)//linear
	    {
		plug->indx += plug->t/startup_length;
	    }
	    else//exponential (concave)
	    {
		//plug->indx += exp2(-10.0*plug->t/startup_length);
		plug->indx += 1 - (exp_startup*exp2(plug->t**plug->startup_curve_p/startup_length) - 1)/(exp_startup - 1);
	    }
	    if(plug->r < (unsigned long)plug->indx)
	    {
		plug->r = (unsigned long)plug->indx;
		a = b; b=c; c=d;
		if(plug->r+2 < plug->w)
		{
		    d = plug->buf[(plug->r+2)&plug->bufmask];
		}
		else
		{
		    //extrapolate
		    d = 2*c-b;
		}
	    }
	    x = plug->indx - plug->r;
	    tmp = b + 0.5 * x*(c - a + x*(2.0*a - 5.0*b + 4.0*c - d + x*(3.0*(b - c) + d - a)));
	    plug->output_p[i] = .999*plug->dcprevout + tmp - plug->dcprevin;
	    plug->dcprevin = tmp;
	    plug->dcprevout = plug->output_p[i];
	    plug->t++;
	}
	if(plug->t>startup_length)
	{
	    for(;i<nframes;i++)
	    {
	        plug->output_p[i] = plug->buf[plug->r++];
	        plug->r &= plug->bufmask;
	    }
	}
    }
    else
    {
	//if aborting a startup
	if(plug->dcprevout != 0)
	{
	    for(i=0;i<nframes;i++)
	    {
	        plug->buf[plug->w++] = plug->input_p[i];
	        plug->w &= plug->bufmask;
	        plug->output_p[i] = i/(float)nframes*plug->input_p[i] + (1-i/(float)nframes)*plug->dcprevout;
	    }
	}
	else
	{ 
	    for(i=0;i<nframes;i++)
	    {
	        plug->buf[plug->w++] = plug->input_p[i];
	        plug->w &= plug->bufmask;
	        plug->output_p[i] = 0;
	    }
	}

	plug->t = 0;
	plug->dcprevin = 0;
	plug->dcprevout = 0;
    }
    return;
}

LV2_Handle init_powerup(const LV2_Descriptor *descriptor,double sample_freq, const char *bundle_path,const LV2_Feature * const* host_features)
{
    POWERUP* plug = malloc(sizeof(POWERUP));

    unsigned long tmp;
    plug->sample_freq = sample_freq; 
    tmp = 0x40000;//19 bits
    if(sample_freq<100000)//88.2 or 96kHz
        tmp = tmp>>1;//18 bits
    if(sample_freq<50000)//44.1 or 48kHz
        tmp = tmp>>1;//17 bits
    plug->buf = (float*)malloc(tmp*sizeof(float));
    plug->bufmask = tmp - 1;
    plug->buf[0] = 0;
    plug->buf[1] = 0;
    plug->indx = 1;
    plug->r = 1;
    plug->w = 2;
    plug->t = 0;
    plug->dcprevin = 0;
    plug->dcprevout = 0;
    plug->max_latency = 100;//FIXME!

    return plug;
}

void connect_powerup_ports(LV2_Handle handle, uint32_t port, void *data)
{
    POWERUP* plug = (POWERUP*)handle;
    switch(port)
    {
    case IN:         	plug->input_p = (float*)data;break;
    case OUT:        	plug->output_p = (float*)data;break;
    case TRIGGER:    	plug->trigger_p = (float*)data;break;
    case PULL_THE_PLUG: plug->pull_the_plug_p = (float*)data;break;
    case DECAY_TIME:  	plug->startup_time_p = (float*)data;break;
    case DECAY_CURVE:   plug->startup_curve_p = (float*)data;break; 
    case LATENCY:       plug->latency_p = (float*)data;break; 
    case DBG:           plug->dbg_p = (float*)data;break; 
    default:         puts("UNKNOWN PORT YO!!");
    }
}

void cleanup_powerup(LV2_Handle handle)
{
    POWERUP* plug = (POWERUP*)handle;
    free(plug->buf);
    free(plug);
}

static const LV2_Descriptor powerup_descriptor={
    POWERUP_URI,
    init_powerup,
    connect_powerup_ports,
    0,//activate
    run_powerup,
    0,//deactivate
    cleanup_powerup,
    0//extension
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index) {
    case 0:
        return &powerup_descriptor;
    default:
        return 0;
    }
}
