//Spencer Jackson
//duffer.c
#include<lv2.h>
#include<lv2/lv2plug.in/ns/ext/urid/urid.h>
#include<lv2/lv2plug.in/ns/ext/atom/util.h>
#include<lv2/lv2plug.in/ns/ext/buf-size/buf-size.h>
#include<lv2/lv2plug.in/ns/ext/options/options.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"rk4.h"
#include"c_resampler.h"

#define DUFFER_URI "http://ssj71.github.io/infamousPlugins/plugs.html#duffer"

typedef struct _DUFFER
{
    float p1;
    float p2; //previous samples for cubic interpolation
    double sample_freq;
    double sample_time;

    float *buf;
    double intermediate[16];
    double* state;
    RESAMPLER_HANDLE resampler;

    float *input_p;
    float *output_p;
    // /ddot{x} + /delta*/dot{x} + /beta*x + /alpha*x^3 = /gamma/text{forcing function}
    float *delta_p;//damping
    float *alpha_p;//spring nonlinearity
    float *beta_p;//spring stiffness
    float *gamma_p;//input gain
    float *unstable_p;
} DUFFER;

enum duffer_ports
{
    IN =0,
    OUT,
    DELTA,
    ALPHA,
    BETA,
    GAMMA,
    UNSTABLE
};

//forcing function is just the input buffer
float forcing_function(void* data, double t)
{
    DUFFER* plug = (DUFFER*)data;
    //uint32_t i = 2*t*plug->sample_freq;
    uint32_t i = 2*t;
    return plug->buf[i];
}

//returns the derivative of the state according to a duffing oscillator
// /ddot{x} + /delta*/dot{x} + /beta*x + alpha*x^3 = /gamma/text{forcing function}
double* duffing_equation(double t, int n, double u[], void* data, double buf[])
{
    DUFFER* plug = (DUFFER*)data;
    n++;//has no effect, just avoids warning
    buf[0] = -*plug->delta_p*u[0] - *plug->beta_p*u[1] - *plug->alpha_p*u[1]*u[1]*u[1] + *plug->gamma_p*forcing_function(data, t);
    buf[1] = u[0];
    return buf;
}

void run_duffer(LV2_Handle handle, uint32_t nframes)
{
    uint32_t i=0;
    double t=0;
    DUFFER* plug = (DUFFER*)handle;
    double *state = plug->state;

    //upsample for midpoints used by rk4
    ResamplerSetInpCount(plug->resampler,nframes);
    ResamplerSetInpData(plug->resampler,plug->input_p);
    ResamplerSetOutCount(plug->resampler,2*nframes);
    ResamplerSetOutData(plug->resampler,plug->buf);
    ResamplerProcess(plug->resampler);

    for(i=0; i<nframes; i++)
    {
        state = rk4vecRT(t, 2, state, 44100*plug->sample_time, duffing_equation, (void*)plug, plug->intermediate);
        plug->output_p[i] = state[1];
    }
    *plug->unstable_p = 0;
    //outout is exploding! reset state
    if((plug->output_p[0]*plug->output_p[0] > 10 && state[1]*state[1] > 10) || isnan(state[1]) )
    {
        state[0] = 0;
        state[1] = 0;
        *plug->unstable_p = 1;
    }

    return;
}

LV2_Handle init_duffer(const LV2_Descriptor *descriptor,double sample_freq, const char *bundle_path,const LV2_Feature * const* host_features)
{
    DUFFER* plug = malloc(sizeof(DUFFER));

    plug->sample_freq = sample_freq;
    plug->sample_time = 1/sample_freq;

    plug->resampler = ResamplerAlloc();
    ResamplerSetup(plug->resampler,1,2,1,32);// 32 is medium quality.
    // Prefeed some input samples to remove delay.
    ResamplerSetInpCount(plug->resampler,ResamplerInpSize(plug->resampler)-1);
    ResamplerSetInpData(plug->resampler,0);
    ResamplerSetOutCount(plug->resampler,0);
    ResamplerSetOutData(plug->resampler,0);
    ResamplerProcess(plug->resampler);

    //get input buffersize to allocate space for upsampling
    uint8_t i,j;
    int max=1024;//default
    struct urids
    {
        LV2_URID    atom_Float;
        LV2_URID    atom_Int;
        LV2_URID    bufsz_max;

    } URIDs;
    LV2_URID_Map *urid_map;
    for(i=0; host_features[i]; i++)
    {
        if(!strcmp(host_features[i]->URI,LV2_OPTIONS__options))
        {
            LV2_Options_Option* option;
            option = (LV2_Options_Option*)host_features[i]->data;
            for(j=0; option[j].key; j++)
            {
                if(option[j].key == URIDs.bufsz_max)
                {
                    if(option[j].type == URIDs.atom_Int)
                    {
                        max = *(const int*)option[j].value;
                    }
                    //other types?
                }
            }
        }
        else if(!strcmp(host_features[i]->URI,LV2_URID__map))
        {
            urid_map = (LV2_URID_Map *) host_features[i]->data;
            if(urid_map)
            {
                URIDs.atom_Int = urid_map->map(urid_map->handle,LV2_ATOM__Int);
                URIDs.atom_Float = urid_map->map(urid_map->handle,LV2_ATOM__Float);
                URIDs.bufsz_max = urid_map->map(urid_map->handle,LV2_BUF_SIZE__maxBlockLength);
            }
        }
    }

    plug->buf = (float*)malloc(sizeof(float)*2*max);

    plug->state = &plug->intermediate[14];
    plug->state[0] = 0;
    plug->state[1] = 0;

    return plug;
}

void connect_duffer_ports(LV2_Handle handle, uint32_t port, void *data)
{
    DUFFER* plug = (DUFFER*)handle;
    switch(port)
    {
    case IN:
        plug->input_p = (float*)data;
        break;
    case OUT:
        plug->output_p = (float*)data;
        break;
    case DELTA:
        plug->delta_p = (float*)data;
        break;
    case ALPHA:
        plug->alpha_p = (float*)data;
        break;
    case BETA:
        plug->beta_p = (float*)data;
        break;
    case GAMMA:
        plug->gamma_p = (float*)data;
        break;
    case UNSTABLE:
        plug->unstable_p = (float*)data;
        break;
    default:
        puts("UNKNOWN PORT YO!!");
    }
}

void cleanup_duffer(LV2_Handle handle)
{
    DUFFER* plug = (DUFFER*)handle;
    free(plug->buf);
    free(plug);
}

static const LV2_Descriptor duffer_descriptor=
{
    DUFFER_URI,
    init_duffer,
    connect_duffer_ports,
    0,//activate
    run_duffer,
    0,//deactivate
    cleanup_duffer,
    0//extension
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index)
    {
    case 0:
        return &duffer_descriptor;
    default:
        return 0;
    }
}
