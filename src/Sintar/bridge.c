//Spencer Jackson
//bridge.c
#include<bridge.h>

#define BRIDGELEN   30//mm
#define BMASS       2//kg
#define BDAMP       2//kg/s
#define BSPRING     2//kg/s^2


void init_bridge(BRIDGE* self, double samplerate)
{
    self->sample_rate = samplerate;
    self->dt = 1/samplerate;
    self->c1  = -BDAMP/BMASS;
    self->c2 = -BSPRING/BMASS;
    self->c3 = 1/BMASS;
    self->length = BRIDGELEN;
    self->dampning = BDAMP;
    self->spring = 1/BSPRING;
    self->input_force = 0;
    self->y = 0;
    self->v = 0;
}



//vbridge = (xb - xbprev)/dt;
//ddy = 1/m*[ -d*dy - k*y + fin]
void update_bridge(BRIDGE* self)
{
    float accel = self->c1*self->v + self->c2*self->y + self->c3*self->input_force;
    self->v += accel*self->dt;
    self->y += self->v*self->dt;
    self->input_force = 0;//reset input for next sample
}
