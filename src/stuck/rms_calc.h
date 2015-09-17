//spencer jackson
//rms_calc.c - an rms calculation library thing.
#include<stdint.h>

typedef struct _RMS_CALC
{
    uint16_t size;
    uint16_t indx;
    float* buf;
    float sum;
    float rms;
} RMS_CALC;

void rms_init(RMS_CALC* calc, uint16_t size);
void rms_deinit(RMS_CALC* calc);
float rms_shift(RMS_CALC* calc, float x);
void rms_shift_no_out(RMS_CALC* calc, float x);
float rms_calculate(RMS_CALC* calc);
float rms_block_fill(RMS_CALC* calc, float x[], uint32_t nframes);
