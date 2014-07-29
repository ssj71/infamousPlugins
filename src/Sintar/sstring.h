//Spencer Jackson
//sstring.h
#include<bridge.h>

//this object is a sitar string it must have a bridge to be attched to


typedef struct _STRING
{
    BRIDGE* bridge;
    float length;
    float a,g,Q;
    float dx;
    float dt;
    float mass;
    float v;
    unsigned long npoints;
    unsigned short nbridge;
    unsigned short input;
    float *prevstate;
    float *state;
    float *newstate;
}STRING;



void init_string(STRING* self, BRIDGE* bridge, float len, float radius, float freq, double samplerate, float in);
float calc_string(STRING* self, float length);
void cleanup_string(STRING* self);
