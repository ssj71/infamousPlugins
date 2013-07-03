//Spencer Jackson
//bridge.c
#include<bridge.h>

#define BRIDGELEN   30//mm
#define BMASS       .5//kg
#define BDAMP       13151//kg/s
#define BSPRING     8671000//kg/s^2


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
//
//Y(s)/F(s) = (ms^2 + ds + k)^-1
//          = m^-1/(s^2 +d/ms + k/m)
//
//G(s) = w^2/(s^2 = 2zws + w^2)
//w = res. freq = sqrt(k/m) = 2093
//z = damping factor = (d/m)/2/sqrt(k/m) = d/(2sqrt(km)) = 1
void update_bridge(BRIDGE* self)
{
    float accel = self->c1*self->v + self->c2*self->y + self->c3*self->input_force;
    self->v += accel*self->dt;
    self->y += self->v*self->dt;
    self->input_force = 0;//reset input for next sample
}

/*octave script
m = 2;
zeta = 1;
omega = 2093;%hz

k = m*(2*pi*omega)^2
d = zeta*2*sqrt(k*m)


*/
