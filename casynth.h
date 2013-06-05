//Spencer Jackson
//casynth.h
#include<lv2.h>
#include<note.h>

typedef struct _CASYNTH
{
    NOTE note[127];
    unsigned char active[127];
    unsigned char nactive;

    double sample_rate;

}CASYNTH;


//lv2 stuff
static LV2_Handle init_casynth(const LV2_Descriptor *descriptor,double sample_rate, const char *bundle_path,const LV2_Feature * const* host_features);
static void cleanup_casynth(LV2_Handle handle);
static void connect_casynth_ports(LV2_Handle handle, uint32_t port, void *data);
