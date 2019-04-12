//Spencer Jackson
//stuck.c
#include<lv2.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"powerup.h"

//#define CV_PORTS

typedef struct _POWERUP
{
    uint32_t w;//current write point in buffer
    uint32_t r;//current read point in buffer
    uint32_t t;//nframes processed after trigger
    uint32_t bufmask;//size of buffer
    uint32_t latency;
    double sample_freq;

    float *buf;
    double indx;
    float dcprevin;
    float dcprevout;

    float startup_curve;
    float startup_time;

    float *input_p;
    float *output_p;
    float *trigger_p;
    float *fire_it_up_p;
    float *startup_time_p;
    float *startup_curve_p;
    float *latency_p;
    float *dbg_p;
} POWERUP;


void run_powerup(LV2_Handle handle, uint32_t nframes)
{
    POWERUP* plug = (POWERUP*)handle;
    uint32_t i=0;
    float startup_length = (float)(plug->startup_time*plug->sample_freq);

#ifdef CV_PORTS
    if(*plug->fire_it_up_p >= 1 || plug->trigger_p[nframes-1] >= 1)
#else
    if(*plug->fire_it_up_p>= 1)
#endif
    {
        //triggered, start cow face
        float a,b,c,d,x,tmp;
        double exp_curve;
        if(!plug->t)
        {
            //just starting powerup, lock in values
            plug->startup_time = *plug->startup_time_p;
            plug->startup_curve = *plug->startup_curve_p;

            //initialize other vars
            startup_length = (float)(plug->startup_time*plug->sample_freq);
            plug->latency = startup_length;
            plug->w += plug->bufmask +1;
            plug->r = plug->w + startup_length - plug->latency;//final read position

            //calculate number samples to be read and subtract from read position
            if(plug->startup_curve > 0)//logarithmic (convex)
            {
                double seed;
                plug->indx = 0;
                exp_curve = exp2(plug->startup_curve)-1;
                for(i=0; i<startup_length;)
                {
                    //to reduce number of log2 calls, but must stay within range of double
                    for(seed = exp_curve*i++/startup_length + 1; seed<1e300 && i<startup_length;)
                    {
                        seed *= exp_curve*i++/startup_length + 1;
                    }
                    plug->indx += log2(seed);
                }
                plug->indx = plug->r - plug->indx/plug->startup_curve;
            }
            else if(plug->startup_curve == 0)//linear
            {
                plug->indx = plug->r - (startup_length - (startup_length+1)/2);
            }
            else//exponential (concave)
            {
                double coeff = exp2(plug->startup_curve/startup_length);
                double term = 1;
                plug->indx = 0;
                exp_curve = exp2(-plug->startup_curve)-1;
                for(i=0; i<startup_length; i++)
                {
                    plug->indx += term;//same here!
                    term *= coeff;
                }
                plug->indx = plug->r - (plug->indx- startup_length)/exp_curve;
            }

            //now figure the real starting read position (wrap to within buffer size)
            plug->r = (uint32_t)plug->indx;
            tmp = plug->indx - plug->r;
            plug->r &= plug->bufmask;
            plug->indx = plug->r + tmp; //from here on out w, r, & indx will grow until startup completes (no wrapping)
            plug->dcprevin = plug->buf[plug->r];
        }

        //now business as usual
        exp_curve = exp2(plug->startup_curve>0?plug->startup_curve:-plug->startup_curve);
        a = plug->buf[(plug->r-1)&plug->bufmask];
        b = plug->buf[plug->r&plug->bufmask];
        c = plug->buf[(plug->r+1)&plug->bufmask];
        d = plug->buf[(plug->r+2)&plug->bufmask];

        for(i=0; i<nframes && plug->t<startup_length; i++)
        {
            //write input
            plug->buf[plug->w++&plug->bufmask] = plug->input_p[i];
            //increment indx the amount for current (starting up) sample rate
            if(plug->startup_curve > 0)//logarithmic (convex)
            {
                plug->indx += 1/(plug->startup_curve)*log2((exp_curve-1)*plug->t/startup_length + 1);
            }
            else if(plug->startup_curve == 0)//linear
            {
                plug->indx += plug->t/startup_length;
            }
            else//exponential (concave)
            {
                plug->indx += (exp2(-plug->startup_curve*plug->t/startup_length) - 1)/(exp_curve - 1);
            }
            if(plug->r < (uint32_t)plug->indx)
            {
                plug->r = (uint32_t)plug->indx;
                a = b;
                b=c;
                c=d;
                d = plug->buf[(plug->r+2)&plug->bufmask];
            }
            x = plug->indx - plug->r;
            tmp = b + 0.5 * x*(c - a + x*(2.0*a - 5.0*b + 4.0*c - d + x*(3.0*(b - c) + d - a)));
            plug->output_p[i] = .999*plug->dcprevout + tmp - plug->dcprevin;
            plug->dcprevin = tmp;
            plug->dcprevout = plug->output_p[i];
            plug->t++;
        }
        if(plug->t >= startup_length)
        {
            plug->r = plug->w - plug->latency;
            for(; i<nframes; i++)
            {
                plug->buf[plug->w++&plug->bufmask] = plug->input_p[i];
                plug->output_p[i] = plug->buf[plug->r++&plug->bufmask];//might get anomolies from switching out dc rm filter
            }
        }
    }
    else
    {
        plug->w &= plug->bufmask;
        //if aborting a startup
        if(plug->dcprevout != 0)
        {
            for(i=0; i<nframes; i++)
            {
                plug->buf[plug->w++] = plug->input_p[i];
                plug->w &= plug->bufmask;
                plug->output_p[i] = i/(float)nframes*plug->input_p[i] + (1-i/(float)nframes)*plug->dcprevout;
            }
        }
        else
        {
            for(i=0; i<nframes; i++)
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
    *plug->latency_p = plug->latency;
    return;
}

LV2_Handle init_powerup(const LV2_Descriptor *descriptor,double sample_freq, const char *bundle_path,const LV2_Feature * const* host_features)
{
    POWERUP* plug = (POWERUP*)malloc(sizeof(POWERUP));

    uint32_t tmp;
    plug->sample_freq = sample_freq;
    tmp = 0x200000;//21 bits
    if(sample_freq<100000)//88.2 or 96kHz
        tmp = tmp>>1;//20 bits
    if(sample_freq<50000)//44.1 or 48kHz
        tmp = tmp>>1;//19 bits
    plug->buf = (float*)malloc(tmp*sizeof(float));
    plug->bufmask = tmp - 1;
    plug->indx = 0;
    plug->r = 0;
    plug->w = 0;
    plug->t = 0;
    plug->dcprevin = 0;
    plug->dcprevout = 0;
    plug->latency = tmp-(tmp>>3);

    return plug;
}

void connect_powerup_ports(LV2_Handle handle, uint32_t port, void *data)
{
    POWERUP* plug = (POWERUP*)handle;
    switch(port)
    {
    case IN:
        plug->input_p = (float*)data;
        break;
    case OUT:
        plug->output_p = (float*)data;
        break;
    case TRIGGER:
        plug->trigger_p = (float*)data;
        break;
    case FIRE_IT_UP:
        plug->fire_it_up_p= (float*)data;
        break;
    case STARTUP_TIME:
        plug->startup_time_p = (float*)data;
        break;
    case STARTUP_CURVE:
        plug->startup_curve_p = (float*)data;
        break;
    case LATENCY:
        plug->latency_p = (float*)data;
        break;
    case DBG:
        plug->dbg_p = (float*)data;
        break;
    default:
        puts("UNKNOWN PORT YO!!");
    }
}

void cleanup_powerup(LV2_Handle handle)
{
    POWERUP* plug = (POWERUP*)handle;
    free(plug->buf);
    free(plug);
}

static const LV2_Descriptor powerup_descriptor=
{
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
    switch (index)
    {
    case 0:
        return &powerup_descriptor;
    default:
        return 0;
    }
}
