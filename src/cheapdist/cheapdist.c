//Spencer Jackson
//cheapdist.c
#include<lv2.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<cheapdist.h>


//this bitfield punning buisness is bad form and you're a bad developer for
//even looking at code like this. But it works with gcc on x86 so I did it.
typedef union
{
    float f;
    struct
    {
        union val
        {
            uint32_t num : 31;
            struct ieee
            {
                uint32_t significand : 23;
                uint32_t exponent : 8;
            } ieee754;
        } value;
        uint32_t sign : 1;
    } parts;
} float_dissector;


typedef struct _CHEAPDIST
{
    uint8_t scale[4];

    float *input_p;
    float *output_p;
    float *aggression_p;
} CHEAPDIST;

void run_cheapdist(LV2_Handle handle, uint32_t nframes)
{
    CHEAPDIST* plug = (CHEAPDIST*)handle;

    float_dissector f;
    uint32_t i;
    uint8_t index = *plug->aggression_p;

    for(i=0; i<nframes; i++)
    {
        f.f = plug->input_p[i];
        f.parts.value.num = (f.parts.value.num)>>index;
        f.parts.value.ieee754.exponent += plug->scale[index];
        plug->output_p[i] = f.f;
    }
}

LV2_Handle init_cheapdist(const LV2_Descriptor *descriptor,double sample_rate, const char *bundle_path,const LV2_Feature * const* host_features)
{
    CHEAPDIST* plug = malloc(sizeof(CHEAPDIST));

    plug->scale[0] = 0;
    plug->scale[1] = 63;
    plug->scale[2] = 95;
    plug->scale[3] = 111;

    return plug;
}

void connect_cheapdist_ports(LV2_Handle handle, uint32_t port, void *data)
{
    CHEAPDIST* plug = (CHEAPDIST*)handle;
    switch(port)
    {
    case IN:
        plug->input_p = (float*)data;
        break;
    case OUT:
        plug->output_p = (float*)data;
        break;
    case AGGRESSION:
        plug->aggression_p = (float*)data;
        break;
    default:
        puts("UNKNOWN PORT YO!!");
    }
}

void cleanup_cheapdist(LV2_Handle handle)
{
    CHEAPDIST* plug = (CHEAPDIST*)handle;
    free(plug);
}

static const LV2_Descriptor cheapdist_descriptor=
{
    CHEAPDIST_URI,
    init_cheapdist,
    connect_cheapdist_ports,
    0,//activate
    run_cheapdist,
    0,//deactivate
    cleanup_cheapdist,
    0//extension
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index)
    {
    case 0:
        return &cheapdist_descriptor;
    default:
        return 0;
    }
}
