//spencer jackson
//rms_calc.c - an rms calculation library thing.
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include"rms_calc.h"

void rms_init(RMS_CALC* calc, unsigned short size)
{
    unsigned short i;
    calc->buf = (float*)malloc(sizeof(float)*size);
    calc->size = size;
    calc->indx = 0;
    calc->sum = 0;
    calc->rms = 0;
    for(i=0;i<size;i++)
        calc->buf[i] = 0;
}

void rms_deinit(RMS_CALC* calc)
{
    free(calc->buf);
}

float rms_shift(RMS_CALC* calc, float x)
{
    calc->sum -= calc->buf[calc->indx];
    calc->buf[calc->indx] = x*x;
    calc->sum += calc->buf[calc->indx++];
    calc->indx = calc->indx<calc->size?calc->indx:0;
    calc->sum = calc->sum>=0?calc->sum:0;
    return calc->rms = sqrt(calc->sum/(float)calc->size);
}

void rms_shift_no_out(RMS_CALC* calc, float x)
{
    calc->sum -= calc->buf[calc->indx];
    calc->buf[calc->indx] = x*x;
    calc->sum += calc->buf[calc->indx++];
    calc->indx = calc->indx<calc->size?calc->indx:0;
    calc->sum = calc->sum>=0?calc->sum:0;
}

float rms_calculate(RMS_CALC* calc)
{
    return calc->rms = sqrt(calc->sum/(float)calc->size);
}

float rms_block_fill(RMS_CALC* calc, float x[], unsigned short nframes)
{  
    //unsigned short i = calc->size - calc->indx;
    //unsigned short j;
    unsigned short i;
    for(i=0;i<nframes-1;i++)
    {
        rms_shift_no_out(calc,x[i]);
    }
    return rms_shift(calc,x[i]);
    /*
    if(nframes>=calc->size)
    {
        memcpy(calc->buf,&(x[nframes-calc->size]),sizeof(float)*calc->size);
        calc->sum = 0;
        for(j=0;j<calc->size;j++)
        {
            calc->sum += calc->buf[j] = calc->buf[j]*calc->buf[j];
        }
        calc->indx = 0;
    }
    else if(calc->indx+nframes >= calc->size)
    { 
        memcpy(&(calc->buf[calc->indx]),x,sizeof(float)*(i));
        memcpy(calc->buf,&(x[i-1]),sizeof(float)*(nframes-i));
        for(j=0;j<nframes-i;j++)
        { 
            calc->sum += calc->buf[j] = calc->buf[j]*calc->buf[j];
        }
        for(;j<calc->indx;j++)
        {
            calc->sum += calc->buf[j];
        }
        for(;j<calc->size;j++)
        {
            calc->sum += calc->buf[j] = calc->buf[j]*calc->buf[j];
        }
        calc->indx = nframes - i;
    }
    else
    {
        memcpy(&(calc->buf[calc->indx]),x,sizeof(float)*(nframes));
        for(j=0;j<calc->indx;j++)
        {
            calc->sum += calc->buf[j];
        }
        for(;j<calc->size;j++)
        {
            calc->sum += calc->buf[j] = calc->buf[j]*calc->buf[j];
        }
        calc->indx += nframes;
    }
    return calc->rms = sqrt(calc->sum/(float)calc->size);
    */
} 
