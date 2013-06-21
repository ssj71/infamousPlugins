//Spencer Jackson
//envfollower.h
#include<lv2.h>
#include<lv2/lv2plug.in/ns/ext/urid/urid.h>
#include<lv2/lv2plug.in/ns/ext/midi/midi.h>
#include<lv2/lv2plug.in/ns/ext/atom/util.h>
#include "lv2/lv2plug.in/ns/ext/time/time.h"
#include "lv2/lv2plug.in/ns/ext/atom/forge.h"

#define ENVFOLLOWER_URI "http://sourceforge.net/projects/infamousplugins:envfollower"

typedef struct _ENVFOLLOWER{
    float sample_rate;

    float peak;
    float rms;
    float current;
    float prev;
    unsigned char mout;
    unsigned char mprev;

    uint64_t nsum;
    double sum;
    float out;

    float atime;
    float up[3];
    float dtime;
    float dn[3];

    //midi stuff
    LV2_URID midi_event_type;
    LV2_Atom_Forge forge;
    LV2_Atom_Forge_Frame frame;

    //ports
    float* input_p;
    float* output_p;
    LV2_Atom_Sequence* midi_out_p;

    float* channel_p;
    float* control_p;
    float* min_p;
    float* max_p;
    float* peakrms_p;
    float* threshold_p;
    float* saturation_p;
    float* atime_p;
    float* dtime_p;


}ENVFOLLOWER;


//lv2 stuff
LV2_Handle init_envfollower(const LV2_Descriptor *descriptor,double sample_rate, const char *bundle_path,const LV2_Feature * const* host_features);
void connect_envfollower_ports(LV2_Handle handle, uint32_t port, void *data);
void run_envfollower( LV2_Handle handle, uint32_t nframes);
void cleanup_envfollower(LV2_Handle handle);

static const LV2_Descriptor envfollower_descriptor={
    ENVFOLLOWER_URI,
    init_envfollower,
    connect_envfollower_ports,
    NULL,//activate
    run_envfollower,
    NULL,//deactivate
    cleanup_envfollower,
    NULL//extension
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index) {
    case 0:
        return &envfollower_descriptor;
    default:
        return NULL;
    }
}

enum envfollower_ports
{
    INPUT = 0,
    OUTPUT,
    MIDI_OUT,
    CHANNEL,
    CONTROL_NO,
    MINV,//5
    MAXV,
    PEAKRMS,
    THRESHOLD,
    SATURATION,
    ATIME,//10
    DTIME
};
