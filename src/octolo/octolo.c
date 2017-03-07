    //Spencer Jackson
//octolo.c
#include<lv2.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"octolo.h"

//OCTOLO - Playback Modulation Shifter (what else could it stand for?)

#define TOLERANCE .0010

typedef struct _OCTOLO
{
    uint16_t w; //current write point in buffer
    float *buf;
    float r; //read point in buffer
    uint16_t prog; //number of samples passed in the period
    float sample_freq;
    float period;
    int8_t sign;

    float *input_p;
    float *output_p;
    float *period_p;
    float *wet_p;
    float *dry_p;
    float *dn_p;
    float *up_p;
    float *pdn_p;
    float *pup_p;
    float *seq_p;
    float *dbg_p;
} OCTOLO;

float intSin(uint32_t phase)
{
    //old algo x E [-pi,pi]
    //double y = 1.27323954474*x - 0.40528473456*x*(x>0?x:-x);
    //return 0.225*(y*(y>0?y:-y) - y) + y;
    return phase/10000;
}

void run_octolo(LV2_Handle handle, uint32_t nframes)
{
    OCTOLO* plug = (OCTOLO*)handle;
    float* in, *out, *buf;
    uint16_t i, chunk;
    uint32_t j, rint;
    uint16_t w,t1,t2;
    float r, step, smooth, stub;

    *plug->dbg_p = 0;

    in = plug->input_p;
    out = plug->output_p;
    buf = plug->buf;
    r = plug->r;
    w = plug->w;

    step = powf(2.0,*plug->shift_p/12.0);
    t1 = .01**plug->duty_p * 0.001**plug->period_p * plug->sample_freq;// samples of low rate
    t2 = (1 -.01**plug->duty_p) * 0.001**plug->period_p * plug->sample_freq;// samples of high rate

    plug->period += plug->sign*rand()/(float)RAND_MAX; 
    if(plug->period >= 20)
        plug->sign = -5;
    else if(plug->period < 5)
        plug->sign = 5;
    for(i=0; i<nframes; )
    {
        //t1 = .01**plug->duty_p * 0.001*plug->period * plug->sample_freq;// samples of low rate
        //t2 = (1 -.01**plug->duty_p) * 0.001*plug->period * plug->sample_freq;// samples of high rate
        if(plug->prog < t1)
        {
            //slow mo
            chunk = t1 - plug->prog;
            if(chunk > nframes - i)
                chunk = nframes - i;
            for(chunk += i ; i!=chunk; i++ )
            {
                buf[w++] = in[i];
                rint = (uint16_t)r;
                out[i] = buf[rint];// TODO: add interpolation
                r += step; 
                r = fmod(r,0xffff);
                //if(r > 0xffff)
                //    r -= 0xffff;
                plug->prog++;
            }
        }
        else
        {
            //fast play
            chunk = t2 + t1 - plug->prog;
            smooth = (w + chunk - r)/(float)chunk;
            if(r>w)
                smooth = (w + chunk - r + 0xffff)/(float)chunk;
            if(chunk > nframes - i)
                chunk = nframes - i;
            if(smooth < 1)
                chunk = 0; //I don't know if we should ever get here
            for(chunk += i ; i!=chunk; i++ )
            {
                buf[w++] = in[i];
                rint = r;
                stub = 1.- (r - rint); //how much of this sample is left
                rint &= 0xffff;
                out[i] = stub*buf[rint]; // subsample
                for(j=rint+1; j<=r+smooth-stub; j++) //full samples in between
                    out[i] += buf[j&0xffff];
                rint = r+smooth;
                stub = r + smooth - rint; //how much of this sample is used here (rest will be in the next smoothing
                rint &= 0xffff;
                out[i] += stub*buf[rint]; // subsample
                out[i] /= smooth;
                r += smooth; 
                r = fmod(r,0xffff);
                //if(r > 0xffff)
                //    r -= 0xffff;
                plug->prog++;
            }
            if(plug->prog >= t1 + t2)
            {
                plug->prog = 0;
                r = w;
                plug->period += plug->sign*rand()/RAND_MAX; 
                if(plug->period >= 20)
                    plug->sign = -5;
                else if(plug->period < 5)
                    plug->sign = 5;
            }
        }
    } 

    plug->r = r;
    plug->w = w;

    return;
}

LV2_Handle init_octolo(const LV2_Descriptor *descriptor,double sample_freq, const char *bundle_path,const LV2_Feature * const* host_features)
{
    uint16_t i;

    OCTOLO* plug = malloc(sizeof(OCTOLO));

    //this makes the max period a function of samplerate, but you're dumb if you are using anything but 44100 or 48k
    plug->buf = (float*)malloc(0x10000*sizeof(float));
    plug->r = 0;
    plug->w = 0;
    plug->prog = 0;
    plug->sign = 5;
    plug->period = 5;

    plug->sample_freq = sample_freq;

    plug->buf[0] = 0;
    for(i=1;i;i++)
        plug->buf[i] = 0;
    return plug;
}

void connect_octolo_ports(LV2_Handle handle, uint32_t port, void *data)
{
    OCTOLO* plug = (OCTOLO*)handle;
    switch(port)
    {
    case IN:
        plug->input_p = (float*)data;
        break;
    case OUT:
        plug->output_p = (float*)data;
        break;
    case PERIOD:
        plug->period_p = (float*)data;
        break;
    case DRY:
        plug->dry_p = (float*)data;
        break;
    case WET:
        plug->wet_p = (float*)data;
        break;
    case OCTDOWN:
        plug->dn_p = (float*)data;
        break;
    case OCTUP:
        plug->up_p = (float*)data;
        break;
    case PHASEDOWN:
        plug->pdn_p = (float*)data;
        break;
    case PHASEUP:
        plug->pup_p = (float*)data;
        break;
    case SEQUENCE:
        plug->seq_p = (float*)data;
        break;
    case DBG:
        plug->dbg_p = (float*)data;
        break;
    default:
        puts("UNKNOWN PORT YO!!");
    }
}

void cleanup_octolo(LV2_Handle handle)
{
    OCTOLO* plug = (OCTOLO*)handle;
    free(plug->buf);
    free(plug);
}

static const LV2_Descriptor octolo_descriptor=
{
    OCTOLO_URI,
    init_octolo,
    connect_octolo_ports,
    0,//activate
    run_octolo,
    0,//deactivate
    cleanup_octolo,
    0//extension
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index)
    {
    case 0:
        return &octolo_descriptor;
    default:
        return 0;
    }
}
