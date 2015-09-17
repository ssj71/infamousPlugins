//Spencer Jackson
//stuck.c
#include<lv2.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<powercut.h>

//#define CV_PORTS

typedef struct _POWERCUT
{
    uint32_t w;//current write point in buffer
    uint32_t r;//current read point in buffer
    uint32_t t;//nframes processed after trigger
    uint32_t bufmask;//size of buffer
    double sample_freq;

    float *buf;
    float indx;
    float dcprevin;
    float dcprevout;

    float *input_p;
    float *output_p;
    float *trigger_p;
    float *pull_the_plug_p;
    float *decay_time_p;
    float *decay_curve_p;
    float *dbg_p;
} POWERCUT;


void run_powercut(LV2_Handle handle, uint32_t nframes)
{
    POWERCUT* plug = (POWERCUT*)handle;
    uint32_t i=0;
    float decay_length = (float)(*plug->decay_time_p*plug->sample_freq);

#ifdef CV_PORTS
    if(*plug->pull_the_plug_p >= 1 || plug->trigger_p[nframes-1] >= 1)
#else
    if(*plug->pull_the_plug_p>= 1)
#endif
    {
        //triggered, start cow face
        float a,b,c,d,x,tmp,exp_decay;
        exp_decay = exp2(*plug->decay_curve_p>0?*plug->decay_curve_p:-*plug->decay_curve_p);

        //preload buffer for interpolation
        if(plug->w - plug->r < plug->bufmask)
        {
            plug->buf[plug->w++&plug->bufmask] = plug->input_p[0];
            plug->buf[plug->w++&plug->bufmask] = plug->input_p[1];
        }
        a = plug->buf[(plug->r-1)&plug->bufmask];//need to ensure plug->r starts at indx
        b = plug->buf[plug->r&plug->bufmask];
        c = plug->buf[(plug->r+1)&plug->bufmask];
        d = plug->buf[(plug->r+2)&plug->bufmask];

        for(i=0; i<nframes && plug->t<=decay_length; i++)
        {
            //if not about to overwrite necesary data (w<r)
            if(plug->w - plug->r < plug->bufmask && i+2 < nframes)
            {
                plug->buf[plug->w++&plug->bufmask] = plug->input_p[i+2];
            }
            //increment indx the amount for current (decaying) sample rate
            if(*plug->decay_curve_p > 0)//logarithmic (convex)
            {
                //plug->indx += .1*log2(1024-1023*plug->t/decay_length);
                plug->indx += 1/(*plug->decay_curve_p)*log2(exp_decay - (exp_decay-1)*plug->t/decay_length);
            }
            else if(*plug->decay_curve_p == 0)//linear
            {
                plug->indx += 1-plug->t/decay_length;
            }
            else//exponential (concave)
            {
                //plug->indx += exp2(-10.0*plug->t/decay_length);
                plug->indx += (exp_decay*exp2(plug->t**plug->decay_curve_p/decay_length) - 1)/(exp_decay - 1);
            }
            if(plug->r < (uint32_t)plug->indx)
            {
                plug->r = (uint32_t)plug->indx;
                a = b;
                b=c;
                c=d;
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
            //cubic interpolation and dc rm filter
            tmp = b + 0.5 * x*(c - a + x*(2.0*a - 5.0*b + 4.0*c - d + x*(3.0*(b - c) + d - a)));
            plug->output_p[i] = .999*plug->dcprevout + tmp - plug->dcprevin;
            plug->dcprevin = tmp;
            plug->dcprevout = plug->output_p[i];
            plug->t++;
        }
        if(plug->t>decay_length)
        {
            for(; i<nframes; i++)
            {
                plug->output_p[i] = 0;
            }
            plug->dcprevout = 0;
        }
    }
    else
    {
        //if not aborting a decay
        if(plug->dcprevout != 0)
        {
            for(i=0; i<nframes; i++)
            {
                plug->output_p[i] = i/(float)nframes*plug->input_p[i] + (1-i/(float)nframes)*plug->dcprevout;
            }
        }
        else
        {
            memcpy(plug->output_p,plug->input_p,nframes*sizeof(float));
        }

        plug->buf[0] = plug->input_p[nframes-2];
        plug->buf[1] = plug->input_p[nframes-1];
        plug->indx = 1;
        plug->r = 1;
        plug->w = 2;
        plug->t = 0;
        plug->dcprevin = 0;
        plug->dcprevout = 0;
    }
    return;
}

LV2_Handle init_powercut(const LV2_Descriptor *descriptor,double sample_freq, const char *bundle_path,const LV2_Feature * const* host_features)
{
    POWERCUT* plug = malloc(sizeof(POWERCUT));

    uint32_t tmp;
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

    return plug;
}

void connect_powercut_ports(LV2_Handle handle, uint32_t port, void *data)
{
    POWERCUT* plug = (POWERCUT*)handle;
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
    case PULL_THE_PLUG:
        plug->pull_the_plug_p = (float*)data;
        break;
    case DECAY_TIME:
        plug->decay_time_p = (float*)data;
        break;
    case DECAY_CURVE:
        plug->decay_curve_p = (float*)data;
        break;
    case DBG:
        plug->dbg_p = (float*)data;
        break;
    default:
        puts("UNKNOWN PORT YO!!");
    }
}

void cleanup_powercut(LV2_Handle handle)
{
    POWERCUT* plug = (POWERCUT*)handle;
    free(plug->buf);
    free(plug);
}

static const LV2_Descriptor powercut_descriptor=
{
    POWERCUT_URI,
    init_powercut,
    connect_powercut_ports,
    0,//activate
    run_powercut,
    0,//deactivate
    cleanup_powercut,
    0//extension
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index)
    {
    case 0:
        return &powercut_descriptor;
    default:
        return 0;
    }
}
