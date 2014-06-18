//spencer jackson
//rms_calc.c - an rms calculation library thing.


typedef struct _RMS_CALC
{
    unsigned short size;
    unsigned short indx;
    float buf[];
    float sum;
    float rms;
}RMS_CALC;

void rms_init(RMS_CALC* calc, unsigned short size); 
void rms_deinit(RMS_CALC *calc);
float rms_shift(RMS_CALC* calc, float x); 
void rms_shift_no_out(RMS_CALC* calc, float x); 
float rms_calculate(RMS_CALC* calc);

/* DO NOT USE!
float rms_block_fill(RMS_CALC* calc, float x[], unsigned short nframes);
*/
