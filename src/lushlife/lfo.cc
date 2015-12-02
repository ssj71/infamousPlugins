//spencer jackson

//gpl v2 and all that

//a simple and kinda boring lfo implementation
#include<stdlib.h>
#include<time.h>
#include"lfo.h"

#define PI 3.1415926535897932384626433832795

Lfo::Lfo(double sample_rate, uint32_t fragsize)
{
    //init public vars that callers will set
    shape = 0;
    gain = 0;
    freq = 0;

    //init states
    srand ((unsigned int) time (NULL));
    phase = 2*PI*rand() / (float)RAND_MAX - PI;
    y0 = y1 = x1 = 0;
    
    //const vars
    phastep = 2*PI*fragsize/sample_rate;//w = 2*pi*f; sin(wt) = sin(2*pi*f*t) = sin(2*pi*f*n/fs)
    ro = 2*sample_rate/fragsize;
}

Lfo::~Lfo()
{
}

float 
Lfo::out(float _shape)
{
    shape = _shape;
    return out();
}

float 
Lfo::out()
{
    //step
    phase += phastep*freq;
    if(phase > PI)
    {
        phase -= 2*PI;
    }

    // sin approx based on an algorithm by Nicolas Capens
    // domain [-pi,pi]
    double y = 1.27323954474*phase - 0.40528473456*phase*(phase>0?phase:-phase);
    float s =  0.225*(y*(y>0?y:-y) - y) + y;

    //pink noise method by paul kellet
    /*
    float r = 2.0*rand() / (float)RAND_MAX -1.0;
    y0 = 0.99765 * y0 + r * 0.0990460;
    y1 = 0.96300 * y1 + r * 0.2965164;
    y2 = 0.57000 * y2 + r * 1.0526913;
    r = y0 + y1 + y2 + r * 0.1848;
    */ 
    //this is a LPF with cutoff at freq
    float r = 3*2.0*rand() / (float)RAND_MAX -1.0;//extra 3 factor because lpf seems to need a bit more gain
    float a = 2*PI*freq;
    float b = 1/(ro+a);
    y0 = a*b*(x1 + r - y1) + ro*b*y1;
    y1 = y0;
    x1 = r;
    //blend shapes
    return gain*((s-y0)*shape + y0);

}

void
Lfo::reset()
{
    phase = 0;
    y0 = y1 =  x1 = 0;
}
