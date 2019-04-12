//Spencer Jackson

//a search for the perfect sine function
#include<math.h>
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

//octave:1> pi/hex2dec('80000000')
// ans =    1.46291807926716e-09
//octave:2> hex2dec('80000000')/pi
// ans =  683565275.576432
// 683565276
#define INT2FLOAT M_PI/(float)0x80000000
#define FLOAT2INT 0x80000000/M_PI

float mySin(float x)
{
    float y = 1.27323954474*x - 0.40528473456*x*(x>0?x:-x);
    return 0.225*(y*(y>0?y:-y) - y) + y;
}
float mySinAbs(float x)
{
    float y = 1.27323954474*x - 0.40528473456*x*fabs(x);
    return 0.225*(y*fabs(y) - y) + y;
}
float mySin1Abs(float x)
{
    float y = fabs(x);
    y *= x;
    y *= -0.40528473456;
    x *= 1.27323954474;
    y += x;
    x = fabs(y);
    x *= y;
    x -= y;
    x *= 0.225;
    return x + y;
}
float myIntSinAbs(uint32_t i)
{
    float x = INT2FLOAT*i;
    float y = 1.27323954474*x - 0.40528473456*x*fabs(x);
    return 0.225*(y*fabs(y) - y) + y;
}
float myintSin1f(float i)
{
    int32_t y,m,x;
    x = FLOAT2INT*i;
    y = x>>15;
    m = y>>31;
    y *= ((y^m)-m)>>1;
    x -= y;
    x >>= 15;

    m = x>>31;
    y = x;
    y *= (y^m)-m;
    y >>= 16;
    y *= 37549;
    x *= 32334;
    y += x;
    return INT2FLOAT*y;
}

int32_t intSinOld(int32_t x)
{
    int32_t y,m;
    x = x>>15;
    m = x>>31;
    y = (41722*(x - (((x>>1)*((x^m)-m))>>15)))>>15;
    m = y>>31;
    return 23162*((y*((y^m)-m))>>16) +25395*y;
}
int32_t intSinOldAbs(int32_t x)
{
    int32_t y;
    x = x>>15;
    y = (41722*(x - ((x*labs(x))>>16)))>>15;
    return 23162*((y*labs(y))>>16) +25395*y;
}
int32_t intSinOldIf(int32_t x)
{
    int32_t y;
    x = x>>15;
    y = (41722*(x - (((x>>1)*(x<0?-x:x))>>15)))>>15;
    return 23162*((y*(y<0?-y:y))>>16) +25395*y;
}

int32_t intSin(int32_t x)
{
    int32_t y,m;
    y = x>>15;
    m = y>>16;
    y = (x - (((y>>1)*((y^m)-m))))>>15;
    m = y>>16;
    return 37549*((y*((y^m)-m))>>16) +32334*y;
} 
int32_t intSinAbs(int32_t x)
{
    int32_t y;
    y = x>>15;
    y = (x - ((y*labs(y))>>1))>>15;
    return 37549*((y*labs(y))>>16) +32334*y;
} 
int32_t intSinIf(int32_t x)
{
    int32_t y,m;
    y = x>>15;
    y = (x - ((y>>1)*(y<0?-y:y)))>>15;
    return 37549*((y*(y<0?-y:y))>>16) +32334*y;
} 

int32_t intSin1(int32_t x)//same as intsin but ~1 op per line
{
    int32_t y,m;
    y = x>>15;
    m = y>>31;
    y *= ((y^m)-m)>>1;
    x -= y;
    x >>= 15;

    m = x>>31;
    y = x;
    y *= (y^m)-m;
    y >>= 16;
    y *= 37549;
    x *= 32334;
    return y+x;
}
int32_t intSin1Abs(int32_t x)
{
    int32_t y,m;
    y = x>>15;
    y *= labs(y>>1);//((y^m)-m)>>1;
    x -= y;
    x >>= 15;

    y = x;
    y *= labs(y);
    y >>= 16;
    y *= 37549;
    x *= 32334;
    return y+x;
}
float intSin1f(int32_t x)
{
    int32_t y,m;
    y = x>>15;
    m = y>>31;
    y *= ((y^m)-m)>>1;
    x -= y;
    x >>= 15;

    m = x>>31;
    y = x;
    y *= (y^m)-m;
    y >>= 16;
    y *= 37549;
    x *= 32334;
    y += x;
    return INT2FLOAT*y;
}
float myintSin1Abs(int32_t xi)
{
    float x = INT2FLOAT*xi;
    float y = fabs(x);
    y *= x;
    y *= -0.40528473456;
    x *= 1.27323954474;
    y += x;
    x = fabs(y);
    x *= y;
    x -= y;
    x *= 0.225;
    return x + y;
}


void accuracy(uint32_t samples)
{
    uint32_t i,iphase,idphase;
    float max, min, err, pmax, pmin;
    float phase, dphase;

    //float versions
    dphase = 2*M_PI/samples;

    max = min = 0;
    phase = -M_PI;
    for(i=0;i<samples;i++)
    {
        err = sin(phase) - sinf(phase);
        if(err > max)
        {
            max = err;
            pmax = phase;
        }
        else if (err < min)
        {
            min = err;
            pmin = phase;
        }
        phase += dphase; 
    }
    printf("sinf\nmin %f, @%f\nmax %f, @%f\n\n",min,pmin,max,pmax);

    max = min = 0;
    phase = -M_PI;
    for(i=0;i<samples;i++)
    {
        err = sin(phase) - mySin(phase);
        if(err > max)
        {
            max = err;
            pmax = phase;
        }
        else if (err < min)
        {
            min = err;
            pmin = phase;
        }
        phase += dphase; 
    }
    printf("mySin\nmin %f, @%f\nmax %f, @%f\n\n",min,pmin,max,pmax);

    max = min = 0;
    phase = -M_PI;
    for(i=0;i<samples;i++)
    {
        err = sin(phase) - mySinAbs(phase);
        if(err > max)
        {
            max = err;
            pmax = phase;
        }
        else if (err < min)
        {
            min = err;
            pmin = phase;
        }
        phase += dphase; 
    }
    printf("mySinAbs\nmin %f, @%f\nmax %f, @%f\n\n",min,pmin,max,pmax);

    max = min = 0;
    phase = -M_PI;
    for(i=0;i<samples;i++)
    {
        err = sin(phase) - mySin1Abs(phase);
        if(err > max)
        {
            max = err;
            pmax = phase;
        }
        else if (err < min)
        {
            min = err;
            pmin = phase;
        }
        phase += dphase; 
    }
    printf("mySin1Abs\nmin %f, @%f\nmax %f, @%f\n\n",min,pmin,max,pmax);

    max = min = 0;
    phase = -M_PI;
    for(i=0;i<samples;i++)
    {
        err = sin(phase) - myintSin1f(phase);
        if(err > max)
        {
            max = err;
            pmax = phase;
        }
        else if (err < min)
        {
            min = err;
            pmin = phase;
        }
        phase += dphase; 
    }
    printf("myintSin1f\nmin %f, @%f\nmax %f, @%f\n\n",min,pmin,max,pmax);

    //int versions
    idphase = FLOAT2INT*dphase;

    max = min = 0;
    phase = -M_PI;
    iphase = -0x80000000;
    for(i=0;i<samples;i++)
    {
        err = sin(phase) - INT2FLOAT*intSinAbs(iphase);
        if(err > max)
        {
            max = err;
            pmax = phase;
        }
        else if (err < min)
        {
            min = err;
            pmin = phase;
        }
        phase += dphase; 
        iphase += idphase;
    }
    printf("phase err %f\n", phase-INT2FLOAT*iphase);
    printf("intSinAbs\nmin %f, @%f\nmax %f, @%f\n\n",min,pmin,max,pmax);

    max = min = 0;
    phase = -M_PI;
    iphase = -0x80000000;
    for(i=0;i<samples;i++)
    {
        err = sin(phase) - INT2FLOAT*intSin(iphase);
        if(err > max)
        {
            max = err;
            pmax = phase;
        }
        else if (err < min)
        {
            min = err;
            pmin = phase;
        }
        phase += dphase; 
        iphase += idphase;
    }
    printf("intSin\nmin %f, @%f\nmax %f, @%f\n\n",min,pmin,max,pmax);

    max = min = 0;
    phase = -M_PI;
    iphase = -0x80000000;
    for(i=0;i<samples;i++)
    {
        err = sin(phase) - INT2FLOAT*intSinIf(iphase);
        if(err > max)
        {
            max = err;
            pmax = phase;
        }
        else if (err < min)
        {
            min = err;
            pmin = phase;
        }
        phase += dphase; 
        iphase += idphase;
    }
    printf("intSinIf\nmin %f, @%f\nmax %f, @%f\n\n",min,pmin,max,pmax);

    max = min = 0;
    phase = -M_PI;
    iphase = -0x80000000;
    for(i=0;i<samples;i++)
    {
        err = sin(phase) - INT2FLOAT*intSin1(iphase);
        if(err > max)
        {
            max = err;
            pmax = phase;
        }
        else if (err < min)
        {
            min = err;
            pmin = phase;
        }
        phase += dphase; 
        iphase = phase*FLOAT2INT;
    }
    printf("intSin1\nmin %f, @%f\nmax %f, @%f\n\n",min,pmin,max,pmax);

    max = min = 0;
    phase = -M_PI;
    iphase = -0x80000000;
    for(i=0;i<samples;i++)
    {
        err = sin(phase) - INT2FLOAT*intSin1Abs(iphase);
        if(err > max)
        {
            max = err;
            pmax = phase;
        }
        else if (err < min)
        {
            min = err;
            pmin = phase;
        }
        phase += dphase; 
        iphase = phase*FLOAT2INT;
    }
    printf("intSin1Abs\nmin %f, @%f\nmax %f, @%f\n\n",min,pmin,max,pmax);

    max = min = 0;
    phase = -M_PI;
    iphase = -0x80000000;
    for(i=0;i<samples;i++)
    {
        err = sin(phase) - INT2FLOAT*intSinOld(iphase);
        if(err > max)
        {
            max = err;
            pmax = phase;
        }
        else if (err < min)
        {
            min = err;
            pmin = phase;
        }
        phase += dphase; 
        iphase += idphase;
    }
    printf("intSinOld\nmin %f, @%f\nmax %f, @%f\n\n",min,pmin,max,pmax);

    max = min = 0;
    phase = -M_PI;
    iphase = -0x80000000;
    for(i=0;i<samples;i++)
    {
        err = sin(phase) - INT2FLOAT*intSinOldAbs(iphase);
        if(err > max)
        {
            max = err;
            pmax = phase;
        }
        else if (err < min)
        {
            min = err;
            pmin = phase;
        }
        phase += dphase; 
        iphase += idphase;
    }
    printf("intSinOldAbs\nmin %f, @%f\nmax %f, @%f\n\n",min,pmin,max,pmax);

    max = min = 0;
    phase = -M_PI;
    iphase = -0x80000000;
    for(i=0;i<samples;i++)
    {
        err = sin(phase) - INT2FLOAT*intSinOldIf(iphase);
        if(err > max)
        {
            max = err;
            pmax = phase;
        }
        else if (err < min)
        {
            min = err;
            pmin = phase;
        }
        phase += dphase; 
        iphase += idphase;
    }
    printf("intSinOldIf\nmin %f, @%f\nmax %f, @%f\n\n",min,pmin,max,pmax);

    max = min = 0;
    phase = -M_PI;
    iphase = -0x80000000;
    for(i=0;i<samples;i++)
    {
        err = sin(phase) - myIntSinAbs(iphase);
        if(err > max)
        {
            max = err;
            pmax = phase;
        }
        else if (err < min)
        {
            min = err;
            pmin = phase;
        }
        phase += dphase; 
        iphase = phase*FLOAT2INT;
    }
    printf("myIntSinAbs\nmin %f, @%f\nmax %f, @%f\n\n",min,pmin,max,pmax);

    max = min = 0;
    phase = -M_PI;
    iphase = -0x80000000;
    for(i=0;i<samples;i++)
    {
        err = sin(phase) - intSin1f(iphase);
        if(err > max)
        {
            max = err;
            pmax = phase;
        }
        else if (err < min)
        {
            min = err;
            pmin = phase;
        }
        phase += dphase; 
        iphase = phase*FLOAT2INT;
    }
    printf("intSin1f\nmin %f, @%f\nmax %f, @%f\n\n",min,pmin,max,pmax);

    max = min = 0;
    phase = -M_PI;
    iphase = -0x80000000;
    for(i=0;i<samples;i++)
    {
        err = sin(phase) - myintSin1f(iphase);
        if(err > max)
        {
            max = err;
            pmax = phase;
        }
        else if (err < min)
        {
            min = err;
            pmin = phase;
        }
        phase += dphase; 
        iphase = phase*FLOAT2INT;
    }
    printf("myintSin1f\nmin %f, @%f\nmax %f, @%f\n\n",min,pmin,max,pmax);
}

//naive implementation
float square(int32_t x)
{
    return (float)((x&0x80000000)>>30)-1.0;
}
// (abs(x-d)-abs(x+d) + abs(x-1+d)-abs(x+1-d) + 2x)/(-2d)
float abssquare(int32_t x)
{
    const int32_t d = 1<<24;
    const int32_t d2 = 0x80000000-d;
    return (float)(labs(x-d)-labs(x+d)) + (float)(labs(x-d2)-labs(x+d2)) + (float)2.0*x;
}
float abssquaref(int32_t xi)
{
    const float d = .01;
    const int32_t d2 = 1-d;
    float x = xi/(float)0x80000000;
    return fabs(x-d)-fabs(x+d) + fabs(x-d2)-fabs(x+d2) + 2.0*x;
}
//1/(1+(x/c)^n) Butterworth function
float buttersquare(int32_t x)
{
    int32_t y = x/0x20000000;
    y *= y; //^2
    y *= y; //^4
    y *= y; //^8
    y *= y; //^16
    y *= y; //^32
    y *= y; //^64
    y += 1;
    return 1.0/y; 
}
float buttersquare2(int32_t x)
{
    int32_t y = x/0x20000000;
    y *= y; //^2
    y *= y*y; //^6
    y *= y*y; //^24
    y *= y*y; //^72
    y += 1;
    return 1.0/y;
}
float ifsquare(int32_t x)
{
    if(x < -0x7f000000 || x > 0x7f000000)
        return -(x+0x7fffffff)/(float)0x7f0000000;
    else if(x < -0x01000000)
        return -1.0;
    else if(x < 0x01000000)
        return x/(float)0x7f0000000;
    else
        return 1.0; 
}

float ifsquaref(float x)
{
    const float s = .18237;
    const float sl = (M_PI-.18237)/2;
    const float sh = (M_PI+.18237)/2;
    if(x < -sh || x > sh)
        return -1;
    else if(x < -sl)
        return s*(x + M_PI/2.0);//slope up
    else if(x < sl)
        return 1;
    else
        return -s*(x + M_PI/2.0);//slope down
}

void testsquares(int32_t samples)
{
    int32_t i,iphase,idphase,pmin,pmax, points[] = {-0x7fffffff,-0xc0000000,-0xe0000000,-1,0,0x40000000,0x7fffffff};
    printf("\nalg   -max -half, -quarter -1, 0 half max");
    float v,min,max;

    idphase = 0x100000000/samples;

    printf("\n%s ","square");
    for(i=0; i<7;i++)
        printf("%f ",square(points[i]));

    min = max = 0;
    iphase = -0x80000000; 
    for(i=0;i<samples;i++)
    {
        v = square(iphase);
        iphase += idphase;
        if(v > max)
        {
            max = v;
            pmax = iphase;
        }
        else if (v < min)
        {
            min = v;
            pmin = iphase;
        }
        iphase += idphase;
    }
    printf("square\nmin %f, @%i\nmax %f, @%i\n\n",min,pmin,max,pmax);

    printf("\n%s ","abssquare");
    for(i=0; i<7;i++)
        printf("%f ",abssquare(points[i]));
    min = max = 0;
    iphase = -0x80000000; 
    for(i=0;i<samples;i++)
    {
        v = abssquare(iphase);
        iphase += idphase;
        if(v > max)
        {
            max = v;
            pmax = iphase;
        }
        else if (v < min)
        {
            min = v;
            pmin = iphase;
        }
        iphase += idphase;
    }
    printf("abssquare\nmin %f, @%i\nmax %f, @%i\n\n",min,pmin,max,pmax);

    printf("\n%s ","abssquaref");
    for(i=0; i<7;i++)
        printf("%f ",abssquaref(points[i]));
    min = max = 0;
    iphase = -0x80000000; 
    for(i=0;i<samples;i++)
    {
        v = abssquaref(iphase);
        iphase += idphase;
        if(v > max)
        {
            max = v;
            pmax = iphase;
        }
        else if (v < min)
        {
            min = v;
            pmin = iphase;
        }
        iphase += idphase;
    }
    printf("abssquaref\nmin %f, @%i\nmax %f, @%i\n\n",min,pmin,max,pmax);

    printf("\n%s ","buttersquare");
    for(i=0; i<7;i++)

        printf("%f ",buttersquare(points[i]));
    min = max = 0;
    iphase = -0x80000000; 
    for(i=0;i<samples;i++)
    {
        v = buttersquare(iphase);
        iphase += idphase;
        if(v > max)
        {
            max = v;
            pmax = iphase;
        }
        else if (v < min)
        {
            min = v;
            pmin = iphase;
        }
        iphase += idphase;
    }
    printf("buttersquare\nmin %f, @%i\nmax %f, @%i\n\n",min,pmin,max,pmax);

    printf("\n%s ","buttersquare2");
    for(i=0; i<7;i++)
        printf("%f ",buttersquare2(points[i]));
    min = max = 0;
    iphase = -0x80000000; 
    for(i=0;i<samples;i++)
    {
        v = buttersquare2(iphase);
        iphase += idphase;
        if(v > max)
        {
            max = v;
            pmax = iphase;
        }
        else if (v < min)
        {
            min = v;
            pmin = iphase;
        }
        iphase += idphase;
    }
    printf("buttersquare2\nmin %f, @%i\nmax %f, @%i\n\n",min,pmin,max,pmax);

    printf("\n%s ","ifsquare");
    for(i=0; i<7;i++)
        printf("%f ",ifsquare(points[i]));
    min = max = 0;
    iphase = -0x80000000; 
    for(i=0;i<samples;i++)
    {
        v = ifsquare(iphase);
        iphase += idphase;
        if(v > max)
        {
            max = v;
            pmax = iphase;
        }
        else if (v < min)
        {
            min = v;
            pmin = iphase;
        }
        iphase += idphase;
    }
    printf("ifsquare\nmin %f, @%i\nmax %f, @%i\n\n",min,pmin,max,pmax);

    printf("\n");

}

int main()
{
    //0x02
    //0xfe
    
    //results
    //41721.511719
    //41721.511719
    //23162.333984
    //25395.199219
    //float a = 1.27323954474*(double)(1<<15); 
    //float b = M_PI*0.40528473456*(double)(1<<15);
    //float c = M_PI*.225*(double)(1<<15);
    //float d = 0.775*(double)(1<<15);

    float a = 1.27323954474;
    float c = M_PI*.225*a*a*(double)(1<<15);
    float d = 0.775*a*(double)(1<<15);
    float p;
    int32_t phase = -30452;
    int32_t mask = phase>>31;
    phase = phase^mask - mask;//abs val

    printf("abs %i\n",phase);
    mask = -65535;
    mask = mask*-mask;
    printf("prod %i\n",mask);
    //printf("%f\n%f\n%f\n%f\n",a,b,c,d);
    printf("%f\n%f\n",c,d);
    printf("int2float %f\n",INT2FLOAT);
    printf("float2int %f\n",FLOAT2INT);
    printf("int phase 0x%x, 0x%x, 0x%x, 0x%x\n", (M_PI-.0001)*FLOAT2INT, -M_PI*INT2FLOAT, 1.0*FLOAT2INT, -1.0*FLOAT2INT);
    printf("int phase %i, %i, %i, %i\n", M_PI*FLOAT2INT, -M_PI*FLOAT2INT, 1.0*FLOAT2INT, -1.0*FLOAT2INT);
    phase = -0x80000000;
    printf("float phase %f, %f, %f, %f\n", phase*INT2FLOAT, 0x7fffffff*INT2FLOAT, 1*INT2FLOAT, -1*INT2FLOAT);
    
    phase = ((.01*2*M_PI)*FLOAT2INT/44100.0);
    printf("%i\n",phase);
    printf("\n");


    accuracy(1000000);

    testsquares(1000000);

    return 0;
}
