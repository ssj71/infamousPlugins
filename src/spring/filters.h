#ifndef FILTERS_FOR_INFAMY
#define FILTERS_FOR_INFAMY

typedef void* FILTER;

typedef enum sakfabdkja
{
    BUTTERWORTH,
    CHEBYCHEV1,
    CHEBYCHEV2,
    ELLIPTIC,
    ALLPASS,
    DELAY
} FILTERTYPE;

//TODO: move to .c
typedef struct flielter
{
    float* num;
    uint8_t numsize;
    float* den;
    uint8_t densize;
    uint16_t in;//array index
    uint16_t out;//array index
    uint8_t stages;
    float* buf;
} _FILTER;
//for a delay just set the in index delay samples behind the previous out index

//initialize a filter
//TODO: Add q?
FILTER initFilter(uint8_t order, BANDTYPE band, FILTERTYPE type, float cutoff, float samplerate);
FILTER reinitFilter(uint8_t order, float cutoff);

typedef void* FILTERBANK;

//TODO: move to .c
typedef struct feilleter
{
    float buf[0xFFFF];
    FILTER* filters;
    uint8_t nfilters;
} _FILTERBANK

void addFilter(FILTERBANK bank, FILTER filter);
void changeFilter(FILTERBANK bank, uint8_t index, FILTER newfilter);
void changeDelay(FILTERBANK bank, uint8_t index, uint16_t delay);
void processBank(FILTERBANK bank,float* input, float* output, uint16_t nsamples);

#endif
