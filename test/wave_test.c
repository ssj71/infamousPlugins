//Spencer Jackson
//waves.c

#include"waves.h"
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<stdio.h>

void init_waves(WAVESOURCE* self)
{
    unsigned short i =0;
    unsigned char j;
    char k=0;
    bool even = false;
    double phase = 0;
    self->half_phase = PI;
    self->saw_step = 2*PI/TABLE_LENGTH;
    self->phase_coeff = TABLE_LENGTH/(2*PI);
    self->phase_offset = TABLE_LENGTH/2;

    //saw
    for(i=0;i<TABLE_LENGTH;i++)
    {
        self->saw_table[i] = 0;
        k=1;
        for(j=0;j<MAX_N_HARMONICS;j++)
        {
            self->saw_table[i] += k*sin(j*phase)/(j+1);
            k = -k;
        }
        phase += self->saw_step;
    }

    //tri
    for(i=0;i<TABLE_LENGTH;i++)
    {
        self->tri_table[i] = 0;
        k=7;
        for(j=0;j<MAX_N_HARMONICS;j++)
        {
            even = !even;
            if(even)
                continue;
            self->tri_table[i] += k*sin(j*phase)/((j+1)*(j+1));
            k = -k;
        }
        phase += self->saw_step;
    }

    //white and random
    srand ((unsigned int) time (NULL));
    self->V = 2*rand() / (float)RAND_MAX - 1;
    self->V2 = self->V*self->V;

    //pointers
    self->sin_func = &mySin;
    self->saw_func = &saw;
    self->sqr_func = &square;
    self->tri_func = &triangle;
    self->white_func = &white;
    self->rand_func = &randomsnh;

    self->wave_func[FUNC_SIN] = self->sin_func;
    self->wave_func[FUNC_SAW] = self->saw_func;
    self->wave_func[FUNC_SQR] = self->sqr_func;
    self->wave_func[FUNC_TRI] = self->tri_func;
    self->wave_func[FUNC_WHITE] = self->white_func;
    self->wave_func[FUNC_RAND] = self->rand_func;


    self->func_max = PI;
    self->func_min = -PI;
    self->func_domain = self->func_max - self->func_min;
}

void init_hysteresis(HYSTERESIS *self)
{
    self->prev_val = 2*rand() / (float)RAND_MAX - 1;
    self->prev_phase = 0;
}

//8th order series approximation of pow(2,x) suggested by benjamin guihaire
double myPow2(double x)
{
    double p;  
    if(x>=0) p = (1+x *0.00270760617406228636491106297445); //LN2/256 = 0.00270760617406228636491106297445
    else p = 1/(1-x*0.00270760617406228636491106297445); 
    p *=p;p *=p;p *=p;p *=p;
    p *=p;p *=p;p *=p;
    return p*p; 
}

//based on an algorithm by Nicolas Capens
double mySin(WAVESOURCE *self, HYSTERESIS *mem, double x)
{
    double y = 1.27323954474*x - 0.40528473456*x*(x>0?x:-x);
    return 0.225*(y*(y>0?y:-y) - y) + y;
}

double saw(WAVESOURCE* self, HYSTERESIS* mem, double phase)
{
    phase = phase*self->phase_coeff + self->phase_offset;
    unsigned short hi,lo;
    lo = (unsigned short) phase;
    hi = lo +1;
    return self->saw_table[lo] + (phase - lo)*(self->saw_table[hi] - self->saw_table[lo]);
}

double square(WAVESOURCE* self, HYSTERESIS* mem, double phase)
{
    if(phase > 0)
    {
        return saw(self,mem,phase) - saw(self,mem,phase - self->half_phase);
    }
    else
    {
        return saw(self,mem,phase) - saw(self,mem,phase + self->half_phase);
    }
}

double triangle(WAVESOURCE* self, HYSTERESIS *mem, double phase)
{
    phase = phase*self->phase_coeff + self->phase_offset;
    unsigned short hi,lo;
    lo = (unsigned short) phase;
    hi = lo +1;
    return self->tri_table[lo] + (phase - lo)*(self->tri_table[hi] - self->tri_table[lo]);
}

//normal distribution approximation calculated by a modified Marsaglia polar method
double white(WAVESOURCE* self, HYSTERESIS *mem, double phase)
{
    float U = 2.0* rand() / (float)RAND_MAX - 1;//rand E(-1,1)
    float S = U*U + self->V2;//map 2 random vars to unit circle

   if(S>=1)//repull RV if outside unit circle
   {
       U = 2.0* rand() / (float)RAND_MAX - 1;
       S = U*U + self->V2;
       if(S>=1)
       {
           U = 2.0* rand() / (float)RAND_MAX - 1;
           S = U*U + self->V2;
           if(S>=1)
           {//guarantee an exit, value will be unchanged
               U=0;
           }
       }
   }

   if(U)
   {
       self->V = U;//store V for next round
       self->V2 = U*U;
       return U*sqrt(-2*log(S)/S);
   }
   else
   {
       return self->V;
   }


}

//currently a uniform distribution
double randomsnh(WAVESOURCE* self, HYSTERESIS* mem, double phase)
{
    if(phase < mem->prev_phase)
    {
        mem->prev_val = 2*rand() / (float)RAND_MAX - 1;
    }
    mem->prev_phase = phase;
    return mem->prev_val;
}

double addsaw(double phase)
{ 
    unsigned char j,k=1;
    double out = 0;
    for(j=0;j<MAX_N_HARMONICS;j++)
    {
        out += k*mySin(0,0,j*phase)/(j+1);
        k = -k;
    }
}

//
void main()
{
    WAVESOURCE waves; 
    double d=6.0/100000.0, x=-3.1;

    init_waves(&waves); 
    for(x=-3.1;x<3.1;x+=d)
    {
        saw(&waves,0,x); 
//	printf("%f, ",x);
    }

    for(x=-3.1;x<3.1;x+=d)
    {
        addsaw(x);
    }

}
