//Spencer Jackson
//waves.h
#include<constants.h>

#define TABLE_LENGTH 2520
//1920 = (2^7)(3)5
//2520 = (2^3)(3^2)(5)(7)
#define SAW_MIN 0;
#define SAW_MAX TABLE_LENGTH;

double saw_table[TABLE_LENGTH];
double tri_table[TABLE_LENGTH];
double saw_step;
double half_phase;
bool above;


double saw(double phase);
double square(double phase);
double triangle(double phase);
double white(double phase);
double random(double phase);

float V;
float last;

