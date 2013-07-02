//Spencer JAckson
//sstring.c

#include<sstring.h>
#include<math.h>
#include<stdlib.h>

#define CONSTB      .97//from paper
#define CONSTD      .00005
#define BRONZEDEN   .0087//g/mm^3
#define RGYRATE     .003//m
#define YOUNGMOD    100//N/m^2



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

1st 0,30 mm steel
2nd 0,40 mm bronze
3rd 0,55 mm bronze
4th 0,85 mm brass
5th 0,27 mm steel
6th/7th & taraf 0,22 mm steel

7th string (Chikari) - tuning two octaves higher than the keynote
6th string (Chikari) - tuning an octave higher than the keynote
5th string (Pancham-Chikari) - is the fifth over the keynote
4th string (Kharaj) - tuning an octave lower than the keynote
3th string (Pancham) - is the fifth in the lower octave
2nd string (Jure) - tuning to the keynote
1st string is the main playing string (Baj) and is tuned to the fourth
  */
void init_string(STRING* self, BRIDGE* bridge, float len, float radius, float freq, double samplerate, float in)
{
    float area = PI*radius*radius;//m^2
    float den = BRONZEDEN*area;//linear density g/m
    float tension = den*sqrt(2*freq*len)/1000;//N
    float c = sqrt(tension/den);//m/s
    self->bridge = bridge;
    self->length = len;
    self->mass = len*den/1000;//kg
    self->lbridge = BRIDGELEN;
    self->a = 2*b*d -1;
    self->g = 1-d;
    self->dt = 1/samplerate;
    self->dx = c*self->dt;
    self->Q = YOUNGMOD*area*RGYRATE*RGYRATE/(den*c*c*c*c*slef->dt*self->dt);
    self->input = (unsigned short)in/self->dx;
    self->output = out;
    self->npoints = (unsigned long)len/self->dx;
    self->nbridge = (unsigned short)bridge->length/self->dx;

    self->prevstate = calloc(self->npoints,sizeof(float));
    self->state = calloc(self->npoints,sizeof(float));
    self->newstate = calloc(self->npoints,sizeof(float));
}

float calc_string(STRING* self, float length)
{
    unsigned short i;
    float next;
    float bridgedy = self->dx*self->bridge->y/self->bridge->length;
    float* arrholder;
    float newv;
    unsigned long npoints = self->npoints;

    if(length)
    {
        if(length<self->length)
        {
            npoints = (unsigned long)length/self->dx;
        }
    }

    //y(x,t+dt) = g*[y(x+dx,t) + y(x-dx,t)] - a*y(x,t-dt) - Q*[y(x+2dx,t) + y(x-2dx,t) - 4y(x+dx,t) - 4y(x-dx,t) + 6*y(x,t)]
    self->newstate[0] = 0;//endpoint is fixed
    self->newstate[1] = self->g*(self->state[i-1] + self->state[i+1])
                        - self->a*self->prevstate[i]
                        - self->Q*(0 + self->state[i+2]
                                   - 4*self->state[i-1] - 4*self->state[i+1]
                                   + 6*self->state[i]);//this prevents index out of range
    for(i=2;i<self->nbridge;i++)
    {
        next = self->g*(self->state[i-1] + self->state[i+1])
                - self->a*self->prevstate[i]
                - self->Q*(self->state[i-2] + self->state[i+2]
                           - 4*self->state[i-1] - 4*self->state[i+1]
                           + 6*self->state[i]);

        if(next<i*bridgedy)//can't be lower than bridge
        {
            next = i*bridgedy;
        }
        self->newstate[i] = next;
    }
    for(i=self->nbridge;i<self->npoints-2;i++)
    {
        self->newstate[i] = self->g*(self->state[i-1] + self->state[i+1])
                            - self->a*self->prevstate[i]
                            - self->Q*(self->state[i-2] + self->state[i+2]
                                       - 4*self->state[i-1] - 4*self->state[i+1]
                                       + 6*self->state[i]);
    }
    self->newstate[i++] = self->g*(self->state[i-1] + self->state[i+1])
                        - self->a*self->prevstate[i]
                        - self->Q*(self->state[i-2] + 0
                                   - 4*self->state[i-1] - 4*self->state[i+1]
                                   + 6*self->state[i]);//this prevents index out of range
    self->newstate[i] = 0;//endpoint is fixed

    //apply input
    if(inval)
    {
        self->newstate[input] = inval;
    }

    //apply force to bridge
    if(self->newstate[self->nbridge -1] == self->bridge->y)
    {
        newv = self->bridge->v;
    }
    else
    {
        newv = (self->self->newstate[self->nbridge -1] - self->prevstate[self->nbridge -1])/self->dt;
    }
    self->bridge->input_force += self->mass*(newv - self->v)/self->dt;
    self->v = newv;

    //rotate array pointers
    arrholder = self->prevstate;
    self->prevstate = self->state;
    self->state = self->newstate;
    self->newstate = arrholder;
}
