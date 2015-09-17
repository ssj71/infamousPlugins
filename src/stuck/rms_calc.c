//spencer jackson
//rms_calc.c - an rms calculation library thing.
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<stdint.h>
#include"rms_calc.h"

void rms_init(RMS_CALC* calc, uint16_t size)
{
    uint16_t i;
    calc->buf = (float*)malloc(sizeof(float)*size);
    calc->size = size;
    calc->indx = 0;
    calc->sum = 0;
    calc->rms = 0;
    for(i=0; i<size; i++)
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

float rms_block_fill(RMS_CALC* calc, float x[], uint32_t nframes)
{
    uint32_t i;
    for(i=0; i<nframes-1; i++)
    {
        rms_shift_no_out(calc,x[i]);
    }
    return rms_shift(calc,x[i]);
}
