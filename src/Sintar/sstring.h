//Vibrating string
#include<math.h>

#define BRIDGELEN   30//mm
#define CONSTB      .97//from paper
#define CONSTD      .00005
#define BRONZEDEN   .0087//g/mm^3
#define RGYRATE     .003//m
#define YOUNGMOD    100//N/m^2


typedef struct _BRIDGE
{
    float length;
    float dampning;
    float spring;
    float mass;
    float input_force;

}BRIDGE;

typedef struct _STRING
{
    float length;
    float lbridge;
    float a,g,Q;
    float dx;
    float dt;
    unsigned short output;
    unsigned short input;
    float *state;
    float *newstate;
}STRING;


/*typical values
  classical guitar strig T=151, mu = 7.1

  sitar string 88cm
  16th? fret = 1 dron len 530 mm
  drone lengths (from nut)
550 531 510 488 465 440 414 386 357 326 293 258
  5 fret = 13 dron 221mm

  bronze 8.7g/cm^3


A Physical Model of the Nonlinear Sitar String
Sadjad SIDDIQ
  */
void init_string(STRING* self, float len, float radius, float freq, float samplerate, float in, float out)
{
    float area = 1000*1000*PI*radius*radius;//m^2
    float den = BRONZEDEN*area;//linear density g/m
    float tension = den*sqrt(2*freq*len);//N
    float c = sqrt(tension/den);//m/s
    self->length = len;
    self->lbridge = BRIDGELEN;
    self->a = 2*b*d -1;
    self->g = 1-d;
    self->dt = 1/samplerate;
    self->dx = c*self->dt;
    self->Q = YOUNGMOD*area*RGYRATE*RGYRATE/(den*c*c*c*c*slef->dt*self->dt);
    self->input = in;
    self->output = out;
}

float calc_string(STRING* self, float inval)
{
    if(inval)
    {
        self->newstate[input] = inval;
    }


}

//string
//y(x,t+dt) = g*[y(x+dx,t) + y(x-dx,t)] - a*y(x,t-dt) - Q*[y(x+2dx,t) + y(x-2dx,t) - 4y(x+dx,t) - 4y(x-dx,t) + y(x,t)]

//x < xbridge
//fstring = mstring*(vstring - vbridge)/dt;

//x > bridge mstring*(vstring - vstrprev)/dt;

//vbridge = (xb - xbprev)/dt;
//x = 1/k*[ -d*vb - mb*(vb-vbprev)/dt + sum(fstrings)  ]
calc_string_point(STRING* self, unsigned short pos)
{

}
