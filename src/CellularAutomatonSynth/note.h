//Spencer Jackson
//note.h
#include<constants.h>
#include<waves.h>


typedef struct _NOTE
{
    //midi stuff
    unsigned char value;
    float velocity;
    double pitchbend;
    uint32_t start_frame;
    uint32_t release_frame;
    bool sus;

    //harmonics stuff
    unsigned char* nharmonics;
    float* harm_length;
    unsigned short cells; //list of currently alive harmonics
    bool harmonic[MAX_N_HARMONICS];
    uint32_t nframes_since_harm_change;
    float harm_gain[MAX_N_HARMONICS+1];
    float fwidth[MAX_N_HARMONICS]; //frequency error/width of harmonics

    double step[MAX_N_HARMONICS+1];//step size between frames
    double phase[MAX_N_HARMONICS+1];//phase of all waves + fundamental
    
    double (*base_func)(WAVESOURCE*, HYSTERESIS*, double); //sin, tri, sqr, white, rand, other?
    unsigned char base_wave;
    //double base_func_min;//domain of function i.e. [-pi,pi]
    //double base_func_max;
    HYSTERESIS hyst[MAX_N_HARMONICS + 1];

    //the envelope transitions are handled through recursing, midi events through multiple calls of play
    float env_gain;
    unsigned char env_state;//0a, 1d, 2b, 3s, 4s, 5r
    float envelope[6];//slope/slope/val/slope/val/slope of envelope ADBSSR
    bool note_dead;

    unsigned char amod_wave;
    float* amod_gain;
    double amod_step;
    double amod_phase;
    HYSTERESIS ahyst;

    unsigned char fmod_wave;
    float* fmod_gain;//gain 1 mods \pm 1 semitone
    double fmod_step;
    double fmod_phase;
    HYSTERESIS fhyst;
}NOTE;

void init_note(NOTE *self, WAVESOURCE* waves, double sample_rate, unsigned char value, unsigned char* nharmonics, float* harmonic_length, float* amod_gain, float* fmod_gain);
void start_note(NOTE *self, WAVESOURCE* waves, unsigned char velocity, uint32_t start_frame, float harmonic_gain[], unsigned short harmonics, float width, float envelope[]);
void play_note(NOTE *self, WAVESOURCE* waves, uint32_t nframes, float buffer[], double pitchbend, float gain, unsigned short rule, unsigned char base_wave, unsigned char fmod_wave, double fmod_step, unsigned char amod_wave, double amod_step);
void end_note(NOTE *self, uint32_t release_frame);
void release(NOTE *self, unsigned short harmonics);
