//Spencer Jackson
//waves.h
#include<constants.h>

#define TABLE_LENGTH 2520
//1920 = (2^7)(3)5
//2520 = (2^3)(3^2)(5)(7)
#define SAW_MIN 0;
#define SAW_MAX TABLE_LENGTH;


//make it OO
typedef struct _HYSTERESIS
{
    double prev_phase;
    double prev_val;

} HYSTERESIS;

struct _WAVESOURCE;
typedef struct _WAVESOURCE WAVESOURCE;

struct _WAVESOURCE
{
    double saw_table[TABLE_LENGTH];
    double tri_table[TABLE_LENGTH];
    double saw_step;
    double half_phase;
    double phase_coeff;
    double phase_offset;

    double (*wave_func[6])(WAVESOURCE* , HYSTERESIS* , double);
    double (*sin_func)(WAVESOURCE* , HYSTERESIS* , double);
    double (*saw_func)(WAVESOURCE* , HYSTERESIS* , double);
    double (*sqr_func)(WAVESOURCE* , HYSTERESIS* , double);
    double (*tri_func)(WAVESOURCE* , HYSTERESIS* , double);
    double (*white_func)(WAVESOURCE* , HYSTERESIS* , double);
    double (*rand_func)(WAVESOURCE* , HYSTERESIS* , double);

    double func_min;
    double func_max;
    double func_domain;

    double V;
    double V2;
};

double myPow2(double x);

void init_waves(WAVESOURCE* self);
void init_hysteresis(HYSTERESIS *self);
double mySin(WAVESOURCE* self, HYSTERESIS* mem, double x);
double saw(WAVESOURCE* self, HYSTERESIS* mem, double phase);
double square(WAVESOURCE* self, HYSTERESIS *mem, double phase);
double triangle(WAVESOURCE* self, HYSTERESIS *mem, double phase);
double white(WAVESOURCE* self, HYSTERESIS *mem, double phase);
double randomsnh(WAVESOURCE* self, HYSTERESIS *mem, double phase);


