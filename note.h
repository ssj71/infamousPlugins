//Spencer Jackson
//note.h
#include<constants.h>

#define ENV_ATTACK  0
#define ENV_DECAY   1
#define ENV_BREAK   2
#define ENV_SWELL   3
#define ENV_SUSTAIN 4
#define ENV_RELEASE 5

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

    double step[MAX_N_HARMONICS+1];//step size between frames
    double phase[MAX_N_HARMONICS+1];//phase of all waves + fundamental
    
    double (*base_func)(double); //sin, tri, sqr, white, rand, other?
    unsigned char base_wave;
    double base_func_min;//domain of function i.e. [-pi,pi]
    double base_func_max;


    //the envelope transitions are handled through recursing, midi events through multiple calls of play
    float env_gain;
    unsigned char env_state;//0a, 1d, 2b, 3s, 4s, 5r
    float envelope[6];//slope/slope/val/slope/val/slope of envelope ADBSSR
    bool note_dead;

    double (*amod_func)(double);
    unsigned char amod_wave;
    float* amod_gain;
    double amod_step;
    double amod_phase;
    double amod_func_min;//domain of function i.e. [-pi,pi]
    double amod_func_max;

    double (*fmod_func)(double);
    unsigned char fmod_wave;
    float* fmod_gain;//gain 1 mods \pm 1 semitone
    double fmod_step;
    double fmod_phase;
    double fmod_func_min;//domain of function i.e. [-pi,pi]
    double fmod_func_max;
}NOTE;

void init_note(NOTE *self, double sample_rate, unsigned char value, unsigned char* nharmonics, float* harmonic_length, float* amod_gain, float* fmod_gain);
void start_note(NOTE *self, unsigned char velocity, uint32_t start_frame, float harmonic_gain[], unsigned short harmonics, float envelope[], unsigned char base_wave, unsigned char amod_wave, unsigned char fmod_wave);
void play_note(NOTE *self, uint32_t nframes, float buffer[], double pitchbend, float gain, unsigned short rule, double amod_step, double fmod_step);
void end_note(NOTE *self, uint32_t release_frame);
void release(NOTE *self, unsigned short harmonics);

inline double fastPrecisePow(double a, double b) {
  // calculate approximation with fraction of the exponent
  int e = (int) b;
  union {
    double d;
    int x[2];
  } u = { a };
  u.x[1] = (int)((b - e) * (u.x[1] - 1072632447) + 1072632447);
  u.x[0] = 0;

  // exponentiation by squaring with the exponent's integer part
  // double r = u.d makes everything much slower, not sure why
  double r = 1.0;
  while (e) {
    if (e & 1) {
      r *= a;
    }
    a *= a;
    e >>= 1;
  }

  return r * u.d;
}

inline double fastPow(double a, double b) {
  union {
    double d;
    int x[2];
  } u = { a };
  u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);1073741824 - 1072632447
  u.x[0] = 0;
  return u.d;
}

//based on algorithms by Martin Ankerl
inline double myPow(double x)
{
    union {
      double d;
      short a[2];
    }u;
    u.a[1] = (short)(x*1109377 - 1072632447);
    u.a[0] = 0;
    return u.d;
}
inline double myPow2(double x)
{
    char i = (char)x;
    union {
      double d;
      short a[2];
    }u;
    u.a[1] = (short)((x-i)*1109377 - 1072632447);
    u.a[0] = 0;
    //need to calculate 2^i
    if(1<0)
        1/(1<<-i) + u.d;
    else
        return (1<<i) + u.d;
}
