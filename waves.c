//Spencer Jackson
//waves.c

#include<waves.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

void init_waves()
{
    unsigned short i =0;
    unsigned char j;
    char k=0;
    double phase = 0;
    half_phase = TABLE_LENGTH/2;
    saw_step = 2*PI/TABLE_LENGTH;

    //saw
    for(i=0;i<TABLE_LENGTH;i++)
    {
        saw_table[i] = 0;
        k=1;
        for(j=0;j<MAX_N_HARMONICS;j++)
        {
            saw_table[i] += k*sin(phase)/(j+1);
            k = -k;
        }
        phase += saw_step;
    }

    //tri
    for(i=0;i<TABLE_LENGTH;i++)
    {
        tri_table[i] = 0;
        k=1;
        for(j=0;j<MAX_N_HARMONICS;j++)
        {
            tri_table[i] += k*sin(phase)/((j+1)*(j+1));
            k = -k;
        }
        phase += saw_step;
    }

    //white and random
    srandom ((unsigned int) time (NULL));
    V = V2 = 2*random() / (float)RAND_MAX - 1;
    last = random();

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
    if(i<0)
        return u.d/(double)(1<<-i);
    else
        return u.d*(double)(1<<i);
}

double mySin(double x)
{
    double y = 1.27323954474*x - 0.40528473456*x*(x>0?x:-x);
    return 0.225*(y*(y>0?y:-y) - y) + y;
}

double saw(double phase)
{
    unsigned short hi,lo;
    lo = (unsigned short) phase;
    hi = lo +1;
    return saw_table[lo] + (phase - lo)*(saw_table[hi] - saw_table[lo])/saw_step;
}

double square(double phase)
{
    if(phase > half_phase)
    {
        return saw(phase) - saw(phase - half_phase);
    }
    else
    {
        return saw(phase) - saw(phase + half_phase);
    }
}

double triangle(double phase)
{
    unsigned short hi,lo;
    lo = (unsigned short) phase;
    hi = lo +1;
    return tri_table[lo] + (phase - lo)*(tri_table[hi] - tri_table[lo])/saw_step;
}

//normal distribution approximation calculated by a modified Marsaglia polar method
double white(double phase)
{
    float U = 2.0* random() / (float)RAND_MAX - 1;//rand E(-1,1)
    float V2 = V*V;
    float S = U*U + V2;//map 2 random vars to unit circle

   if(S>=1)//repull RV if outside unit circle
   {
       U = 2.0* random() / (float)RAND_MAX - 1;
       S = U*U + V2;
       if(S>=1)
       {
           U = 2.0* random() / (float)RAND_MAX - 1;
           S = U*U + V2;
           if(S>=1)
           {//guarantee an exit, value will be unchanged
               U=0;
           }
       }
   }

   if(U)
   {
       V = U;//store V for next round
       return U*sqrt(-2*log(S)/S);
   }
   else
   {
       return V;
   }


}

//currently a uniform distribution
//returns 2 random values per cycle
//this isn't going to work becuase there will be multiple callers
double randomsnh(double phase)
{
    if(!above != !(phase > half_phase))
    {
        last = random();
    }
    return last;
}
