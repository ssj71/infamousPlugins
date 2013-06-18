//Spencer Jackson
//waves.h
#include<constants.h>

#define TABLE_LENGTH 2520
//1920 = (2^7)(3)5
//2520 = (2^3)(3^2)(5)(7)
#define SAW_MIN 0;
#define SAW_MAX TABLE_LENGTH;


//make it OO
typedef struct _WAVESOURCE
{

}WAVESOURCE;

double saw_table[TABLE_LENGTH];
double tri_table[TABLE_LENGTH];
double saw_step;
double half_phase;

double myPow2(double x);
double mySin(double x);
double saw(double phase);
double square(double phase);
double triangle(double phase);
double white(double phase);
double arandomsnh(double phase);
double frandomsnh(double phase);

float V,V2;
float alast,flast;
float aprev,fprev;

