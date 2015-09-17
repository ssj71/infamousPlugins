#include<stdint.h>
#include<math.h>
#include<stdio.h>

#define PI 3.1415926535897932384626433832795

//for whatever reason I decided to not make any custom structs for this library, if you want more convenience than this offers, use the filters module that utilizes these functions

void cart2polar(double re, double im, double* mag, double* ang);

void polar2cart(double mag, double ang, double* re, double* im);

//uses pre-warped bilinear transform to map poles/zeros to the z plane
// note that this reqires you to add a zero at (z+1) if no other zeros
//res - real part of s-domain pole or zero
//ims - imaginary part of s-domain pole or zero
//Ts - sample time
//rez - returned real part of z-domain zero (numerator)
//imz - returned imaginary part of z-domain zero
void tustins2z(double res, double ims, double Ts, double* rez, double* imz);

//uses matched z transform to map poles/zeros to the z plane
void s2z(double res, double ims, double Ts, double* rez, double* imz);

//good ol' fasioned convolution by the definition
//f - signal 1
//nf - length of signal 1
//g - signal 2
//ng - length of signal 2
//h - output buffer, requires sufficient length (nf+ng-1)
void convolve(float* f, uint8_t nf, float* g, uint8_t ng, float* h);

//this recursive function stores the values in tmp until all calculations
//are complete and then writes them into g[]
//naturally this requires g[] to be of sufficient size
void _cip(float* f, uint8_t nf, float* g, uint8_t ng, uint8_t t);

//in this version the result will be stored into g[];
// recursion isn't fast so probably shouldn't use this in RT
void convolve_in_place(float* f, uint8_t nf, float* g, uint8_t ng);

//return magnitude of digital FIR filter at freq_hz
//f - filter coefficients
//nf - number of filter taps
//Ts - sample time
//freq_hz - frequency (hz) to calculate magnitude at
float magnitude(float* f, uint8_t nf, float Ts, float freq_hz);

//shift zero (z-domain) for new sampling frequency
//this doesn't account for prewarp (yet)
//re/im zero - zero/pole to shift
//oldTs - sample time filter was designed to
//newTs - new sample time
//re/im - returned shifted zero
//I don't know if this really works or not
void resample_zero(float rezero, float imzero, float oldTs, float newTs, float* re, float* im);

//discrete time (z-plane) zero pole unity-frequency to filter coefficients conversion
//this does not account for prewarp
void dzpuf2filter(float* rezeros, float*imzeros,  uint8_t nzeros, float* repoles, float* impoles,  uint8_t npoles, float unityfreq, float zpTs, float filterTs,  float* filternum, float* filterden);

//continuous time or (s-plane) zero pole unity-frequency to filter coefficient conversion
//re/im zeros - arrays of zeros parts (note to only include 1 of each complex pair)
//nzeros - length of zero arrays
//re/im poles - arrays of poles parts (note to only include 1 of each complex pair)
//npoles - length of pole arrays
//unityfreq = frequency (hz) where filter should have gain == 1
//Ts - sample time
//buf - memory buffer for working, must be larger than returned num and den
//filternum - returned numerator coefficients of resulting filter
//filterden - returned denominator coefficients of resulting filter
void czpuf2filter(float* rezeros, float*imzeros,  uint8_t nzeros, float* repoles, float* impoles,  uint8_t npoles, float unityfreq, float Ts,  float* buf, float* filternum, float* filterden);

//apply a digital filter to a buffer
//num - numerator coefficients
//numsize - number of coefficients in numerator
//den - denominator coefficients
//densize - number of coefficients in denominator
//in - pointer to input in buffer note this assumes buffer is a 2^16 array
//out - pointer to output in buffer
//buf - array containing input and output samples
void filternate(float* num, uint8_t numsize, float*den, uint8_t densize, uint16_t in, uint16_t out, float* buf);

typedef enum bandtypes
{
    LPF,
    HPF,
    BANDPASS,
    BANDSTOP
} BANDTYPE;

//cheby

//find out array sizes necessary for using butter()
//order - number of poles
//type - filter type (use enum)
//bufsize - returns minimum array size required for work
//num - returns minimum array size for numerator of specified filter
//den - returns minimum array size for denominator of specified filter
void butterSize(uint8_t order, FILTERTYPE type, uint8_t *bufsize, uint8_t *numsize, uint8_t *densize);

//design an analog butterworth filter
//order - number of poles
//cutoff - cutoff frequency (hz)
//type - filter type (use enum)
//buf - memory space for work (must be > order*2)
//num - numerator of resulting difference function (must be > 2)
//den - denominator of resulting difference function (must be > order+1)
void butter(uint8_t order, float cutoff, FILTERTYPE type, float Ts, float* buf, float* num, float* den);

//print out a digital filter difference equation
void printtf(float *num, uint8_t nnum, float* den, uint8_t nden);

