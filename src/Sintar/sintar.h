//Spencer Jackson
//casynth.h
#include<lv2.h>
#include<lv2/lv2plug.in/ns/ext/urid/urid.h>
#include<lv2/lv2plug.in/ns/ext/midi/midi.h>
#include<lv2/lv2plug.in/ns/ext/atom/util.h>
#include<lv2/lv2plug.in/ns/ext/time/time.h>
#include<sstring.h>
#include<stdint.h>

#define SINTAR_URI "http://sourceforge.net/projects/infamousplugins:sintar"


typedef struct _SINTAR
{
    double sample_rate;
    STRING main[4];
    STRING drone[3];
    STRING sympathetic[13];
    BRIDGE bridge;


    WAVESOURCE waves;
    NOTE note[127];
    unsigned char active[127];
    unsigned char nactive;
    bool sus;
    unsigned char sustained[127];
    unsigned char nsustained;
    float ibpm;

    uint32_t nframessince;
    double pitchbend;

    unsigned char harmonic_mode;
    unsigned char ncells;
    float cell_lifetime;
    float harm_gain_sinc[MAX_N_HARMONICS+1];
    float harm_gain_saw[MAX_N_HARMONICS+1];
    float harm_gain_sqr[MAX_N_HARMONICS+1];
    float harm_gain_tri[MAX_N_HARMONICS+1];
    float* harm_gains;//points to appropriate array

    float envelope[6];

    float amod_g;
    float fmod_g;

    //lv2 stuff
    LV2_URID midi_event_type;
    LV2_URID other_type;
    //LV2_URID atom_Sequence;
    LV2_URID float_type;
    LV2_URID long_type;
    LV2_URID time_info_type;
    LV2_URID beatsperbar_type;
    LV2_URID bpm_type;
    LV2_URID speed_type;
    LV2_URID frame_type;
    LV2_URID framespersec_type;

    //ports
    LV2_Atom_Sequence* midi_in_p;
    float* output_p;

    float* channel_p;

    float* master_gain_p;
    float* cell_life_p;
    float* rule_p;
    float* init_cells_p;
    float* nharmonics_p;
    float* harmonic_mode_p;
    float* wave_p;

    float* env_a_p;
    float* env_d_p;
    float* env_b_p;
    float* env_swl_p;
    float* env_sus_p;
    float* env_r_p;

    float* amod_wave_p;
    float* amod_freq_p;
    float* amod_gain_p;
    float* fmod_wave_p;
    float* fmod_freq_p;
    float* fmod_gain_p;


}SINTAR;


//lv2 stuff
LV2_Handle init_sintar(const LV2_Descriptor *descriptor,double sample_rate, const char *bundle_path,const LV2_Feature * const* host_features);
void connect_sintar_ports(LV2_Handle handle, uint32_t port, void *data);
void run_sintar( LV2_Handle handle, uint32_t nframes);
void cleanup_sintar(LV2_Handle handle);

static const LV2_Descriptor sintar_descriptor={
    SINTAR_URI,
    init_sintar,
    connect_sintar_ports,
    NULL,//activate
    run_sintar,
    NULL,//deactivate
    cleanup_sintar,
    NULL//extension
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index) {
    case 0:
        return &sintar_descriptor;
    default:
        return NULL;
    }
}

enum casynth_ports
{
    MIDI_IN =0,
    OUTPUT,
    CHANNEL,
    MASTER_GAIN,
    RULE,
    CELL_LIFE,//5
    INIT_CELLS,
    NHARMONICS,
    HARM_MODE,
    WAVE,
    ENV_A,//10
    ENV_D,
    ENV_B,
    ENV_SWL,
    ENV_SUS,
    ENV_R,//15
    AMOD_WAV,
    AMOD_FREQ,
    AMOD_GAIN,
    FMOD_WAV,
    FMOD_FREQ,//20
    FMOD_GAIN
};
