//Spencer Jackson
//note.h
#include<constants.h>


typedef struct _NOTE
{
    //midi stuff
    unsigned char value;
    unsigned char velocity;
    short pitchbend;
    unsigned char mod;

    //harmonics stuff
    unsigned char nharmonics;
    unsigned short harmonics; //list of currently alive harmonics
    uint32_t nframes_since_harm_change;
    unsigned char harmonic_mode;//harmonic gains are set according to this mode
    float harm_gain[MAX_N_HARMONICS+1];

    double step[MAX_N_HARMONICS+1];//step size between frames
    double phase[MAX_N_HARMONICS+1];//phase of all waves + fundamental
    
    void (*base_func)(double); //sin, tri, sqr, other?
    double base_func_min;//domain of function i.e. [-pi,pi]
    double base_func_max;


    //the envelope transitions are handled through recursing, midi events through multiple calls of play
    float env_gain;
    unsigned char env_state;//0a, 1d, 2b, 3s, 4s, 5r
    float envelope[6];//slope/slope/val/slope/val/slope of envelope ADBSSR
    bool note_dead;

    void (*amod_func)(double);
    float amod_gain;
    double amod_step;
    double amod_phase;
    double amod_func_min;//domain of function i.e. [-pi,pi]
    double amod_func_max;

    void (*fmod_func)(double);
    float fmod_gain;
    double fmod_step;
    double fmod_phase;
    double fmod_func_min;//domain of function i.e. [-pi,pi]
    double fmod_func_max;

}NOTE;

void playnote(NOTE *self, uint32_t nframes, uint32_t start_frame, float buffer[] );

//these must be called when a new note is played
NOTE* init_note(NOTE *self, unsigned char value, unsigned char velocity, unsigned char nharmonics, bool *harmonics);

//these must be called before play is called
void set_envelope(NOTE *self, float slope);
void set_harmonics(NOTE *self, unsigned short harmonics);
void set_pitchbend(NOTE *self, short pitchbend);
void end_note(NOTE *self);
