//Spencer Jackson
//casynth.h
#include<lv2.h>
#include<lv2/lv2plug.in/ns/ext/urid/urid.h>
#include<lv2/lv2plug.in/ns/ext/midi/midi.h>
#include<lv2/lv2plug.in/ns/ext/atom/util.h>
#include<note.h>

typedef struct _CASYNTH
{
    double sample_rate;
    NOTE note[127];
    unsigned char active[127];
    unsigned char nactive;
    bool sus;
    unsigned char sustained[127];
    unsigned char nsustained;

    double pitchbend;

    unsigned char harmonic_mode;
    float harm_gain_sinc[MAX_N_HARMONICS+1];
    float harm_gain_saw[MAX_N_HARMONICS+1];
    float harm_gain_sqr[MAX_N_HARMONICS+1];
    float harm_gain_tri[MAX_N_HARMONICS+1];
    float* harm_gains;//points to appropriate array

    float envelope[6];

    //lv2 stuff
    uint32_t midi_event_type;

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


}CASYNTH;


//lv2 stuff
LV2_Handle init_casynth(const LV2_Descriptor *descriptor,double sample_rate, const char *bundle_path,const LV2_Feature * const* host_features);
void connect_casynth_ports(LV2_Handle handle, uint32_t port, void *data);
void run_casynth( LV2_Handle handle, uint32_t nframes);
void cleanup_casynth(LV2_Handle handle);


enum casynth_ports
{
    MIDI_IN =0,
    OUTPUT,
    CHANNEL,
    MASTER_GAIN,
    RULE,
    CELL_LIFE,
    INIT_CELLS,
    NHARMONICS,
    HARM_MODE,
    WAVE,
    ENV_A,
    ENV_D,
    ENV_B,
    ENV_SWL,
    ENV_SUS,
    ENV_R,
    AMOD_WAV,
    AMOD_FREQ,
    AMOD_GAIN,
    FMOD_WAV,
    FMOD_FREQ,
    FMOD_GAIN
};
