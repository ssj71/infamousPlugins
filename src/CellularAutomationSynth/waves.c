//Spencer Jackson
//waves.c

#include<waves.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

void init_waves(WAVESOURCE* self)
{
    unsigned short i =0;
    unsigned char j;
    char k=0;
    double phase = 0;
    self->half_phase = TABLE_LENGTH/2;
    self->saw_step = 2*PI/TABLE_LENGTH;

    //saw
    for(i=0;i<TABLE_LENGTH;i++)
    {
        self->saw_table[i] = 0;
        k=1;
        for(j=0;j<MAX_N_HARMONICS;j++)
        {
            self->saw_table[i] += k*sin(phase)/(j+1);
            k = -k;
        }
        phase += self->saw_step;
    }

    //tri
    for(i=0;i<TABLE_LENGTH;i++)
    {
        self->tri_table[i] = 0;
        k=1;
        for(j=0;j<MAX_N_HARMONICS;j++)
        {
            self->tri_table[i] += k*sin(phase)/((j+1)*(j+1));
            k = -k;
        }
        phase += self->saw_step;
    }

    //white and random
    srandom ((unsigned int) time (NULL));
    self->V = 2*random() / (float)RAND_MAX - 1;
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


    self->func_max[FUNC_SIN] = PI;
    self->func_max[FUNC_SAW] = TABLE_LENGTH;
    self->func_max[FUNC_SQR] = TABLE_LENGTH;
    self->func_max[FUNC_TRI] = TABLE_LENGTH;
    self->func_max[FUNC_WHITE] = TABLE_LENGTH;
    self->func_max[FUNC_RAND] = TABLE_LENGTH;

    self->func_min[FUNC_SIN] = -PI;
    self->func_min[FUNC_SAW] = 0;
    self->func_min[FUNC_SQR] = 0;
    self->func_min[FUNC_TRI] = 0;
    self->func_min[FUNC_WHITE] = 0;
    self->func_min[FUNC_RAND] = 0;

    for(i=0;i<6;i++)
    {
        self->func_domain[i] = self->func_max[i] - self->func_min[i];
    }
}

void init_hysteresis(HYSTERESIS *self)
{
    self->prev_val = 2*random() / (float)RAND_MAX - 1;
    self->prev_phase = 0;
}

//based on an algorithm by Martin Ankerl
double myPow2(double x)
{
    char i = (char)x;
    union {
      double d;
      long a[2];
    }u;
    u.a[1] = (long)((x-i)*1109377 + 1072632447);
    u.a[0] = 0;
    //need to calculate 2^i
    if(x<0)
        return u.d/(double)(1<<-i);
    else if(x>0)
        return u.d*(double)(1<<i);
    else
        return 1;
}

//based on an algorithm by Nicolas Capens
double mySin(WAVESOURCE *self, HYSTERESIS *mem, double x)
{
    double y = 1.27323954474*x - 0.40528473456*x*(x>0?x:-x);
    return 0.225*(y*(y>0?y:-y) - y) + y;
}

double saw(WAVESOURCE* self, HYSTERESIS* mem, double phase)
{
    unsigned short hi,lo;
    lo = (unsigned short) phase;
    hi = lo +1;
    return self->saw_table[lo] + (phase - lo)*(self->saw_table[hi] - self->saw_table[lo])/self->saw_step;
}

double square(WAVESOURCE* self, HYSTERESIS* mem, double phase)
{
    if(phase > self->half_phase)
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
    unsigned short hi,lo;
    lo = (unsigned short) phase;
    hi = lo +1;
    return self->tri_table[lo] + (phase - lo)*(self->tri_table[hi] - self->tri_table[lo])/self->saw_step;
}

//normal distribution approximation calculated by a modified Marsaglia polar method
double white(WAVESOURCE* self, HYSTERESIS *mem, double phase)
{
    float U = 2.0* random() / (float)RAND_MAX - 1;//rand E(-1,1)
    float S = U*U + self->V2;//map 2 random vars to unit circle

   if(S>=1)//repull RV if outside unit circle
   {
       U = 2.0* random() / (float)RAND_MAX - 1;
       S = U*U + self->V2;
       if(S>=1)
       {
           U = 2.0* random() / (float)RAND_MAX - 1;
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
        mem->prev_val = 2*random() / (float)RAND_MAX - 1;
    }
    mem->prev_phase = phase;
    return mem->prev_val;
}
