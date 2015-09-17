//Spencer Jackson
//note.h
#include<constants.h>
#include<waves.h>


typedef struct _NOTE
{
    //midi stuff
    uint8_t value;
    float velocity;
    double pitchbend;
    uint32_t start_frame;
    uint32_t release_frame;
    bool sus;
    float gain;//master gain

    //harmonics stuff
    uint8_t* nharmonics;
    float* harm_length;
    uint16_t cells; //list of currently alive harmonics
    bool harmonic[MAX_N_HARMONICS];
    uint32_t nframes_since_harm_change;
    float harm_gain[MAX_N_HARMONICS+1];
    float fwidth[MAX_N_HARMONICS]; //frequency error/width of harmonics

    double step[MAX_N_HARMONICS+1];//step size between frames
    double phase[MAX_N_HARMONICS+1];//phase of all waves + fundamental

    double (*base_func)(WAVESOURCE*, HYSTERESIS*, double); //sin, tri, sqr, white, rand, other?
    uint8_t base_wave;
    //double base_func_min;//domain of function i.e. [-pi,pi]
    //double base_func_max;
    HYSTERESIS hyst[MAX_N_HARMONICS + 1];

    //the envelope transitions are handled through recursing, midi events through multiple calls of play
    float env_gain;
    uint8_t env_state;//0a, 1d, 2b, 3s, 4s, 5r
    float envelope[6];//slope/slope/val/slope/val/slope of envelope ADBSSR
    bool note_dead;

    uint8_t amod_wave;
    float* amod_gain;
    double amod_step;
    double amod_phase;
    HYSTERESIS ahyst;

    uint8_t fmod_wave;
    float* fmod_gain;//gain 1 mods \pm 1 semitone
    double fmod_step;
    double fmod_phase;
    HYSTERESIS fhyst;
} NOTE;

void init_note(NOTE *self, WAVESOURCE* waves, double sample_rate, uint8_t value, uint8_t* nharmonics, float* harmonic_length, float* amod_gain, float* fmod_gain);
void start_note(NOTE *self, WAVESOURCE* waves, uint8_t velocity, uint32_t start_frame, float harmonic_gain[], uint16_t harmonics, float width, float envelope[]);
void play_note(NOTE *self, WAVESOURCE* waves, uint32_t nframes, float buffer[], double pitchbend, float gain, uint16_t rule, uint8_t base_wave, uint8_t fmod_wave, double fmod_step, uint8_t amod_wave, double amod_step);
void end_note(NOTE *self, uint32_t release_frame);
void release(NOTE *self, uint16_t harmonics);
