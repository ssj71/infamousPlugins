//Spencer Jackson
//note.h
#include<constants.h>


typedef struct
{
    unsigned char value;
    unsigned char velocity;
    unsigned char nharmonics;
    unsigned short harmonics[MAX_N_CELL_CHANGES]; //list of currently alive harmonics
    unsigned char nharm_chng;
    uint32_t harm_chng_frame[MAX_N_CELL_CHANGES];
    unsigned char harmonic_mode;//harmonic gains are set according to this mode
    uint32_t start_frame;//may not even use these, just pass in shortened buffer
    uint32_t stop_frame;
    double phase[MAX_N_HARMONICS+1];//phase of all waves + fundamental
    
    void (*base_func)(double); //sin, tri, sqr, other?
    double base_func_min;//domain of function i.e. [-pi,pi]
    double base_func_max;


    float env_gain;
    float envelope[3];//slope of envelope
    unsigned char nenv_chng;
    uint32_t env_chng_frame[3];

    void (*play)(int,float*);//loads buffer with  int  samples
            
}NOTE;

NOTE* init_note(NOTE *self, unsigned char value, unsigned char velocity, unsigned char nharmonics, bool *harmonics);
void set_envelope(NOTE *self, float slope, uint32_t frame_no);
void set_harmonics(NOTE *self, unsigned short harmonics, uint32_t frame_no);
