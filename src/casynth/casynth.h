//Spencer Jackson
//casynth.h

#include<lv2.h>
#include<lv2/lv2plug.in/ns/ext/urid/urid.h>
#include<lv2/lv2plug.in/ns/ext/midi/midi.h>
#include<lv2/lv2plug.in/ns/ext/atom/util.h>
#include<lv2/lv2plug.in/ns/ext/time/time.h>
#include<note.h>

#define CASYNTH_URI "http://ssj71.github.io/infamousPlugins/plugs.html#casynth"


typedef struct _CASYNTH
{
    double sample_rate;
    WAVESOURCE waves;
    NOTE note[127];
    uint8_t active[127];
    uint8_t nactive;
    bool sus;
    uint8_t sustained[127];
    uint8_t nsustained;
    float ibpm;

    double pitchbend;

    uint8_t harmonic_mode;
    uint8_t ncells;
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
    float* harmonic_width_p;
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


} CASYNTH;

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
    HARM_WIDTH,
    WAVE,
    ENV_A,//11
    ENV_D,
    ENV_B,
    ENV_SWL,
    ENV_SUS,
    ENV_R,//16
    AMOD_WAV,
    AMOD_FREQ,
    AMOD_GAIN,
    FMOD_WAV,
    FMOD_FREQ,//21
    FMOD_GAIN
};
