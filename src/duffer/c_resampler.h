//Spencer Jackson
//c_resampler.h

// c wrapper for the excellent zita-resampler library
// to learn more about this library and its useage you can read the documentation
// at http://kokkinizita.linuxaudio.org/linuxaudio/zita-resampler/resampler.html
#ifndef __C_RESAMPLER_H
#define __C_RESAMPLER_H


#ifdef __cplusplus
extern "C" {
#endif

typedef void* RESAMPLER_HANDLE;

RESAMPLER_HANDLE ResamplerAlloc();
void ResamplerFree( RESAMPLER_HANDLE );
int ResamplerSetup( RESAMPLER_HANDLE , unsigned int   fs_inp, unsigned int fs_out, unsigned int nchan, unsigned int hlen );
void ResamplerClear( RESAMPLER_HANDLE );
int ResamplerReset( RESAMPLER_HANDLE );
int ResamplerProcess( RESAMPLER_HANDLE );
int ResamplerNChan( RESAMPLER_HANDLE );
int ResamplerInpSize( RESAMPLER_HANDLE );
double ResamplerInpDist( RESAMPLER_HANDLE );

//access to public members
unsigned int ResamplerGetInpCount( RESAMPLER_HANDLE );
void ResamplerSetInpCount( RESAMPLER_HANDLE , unsigned int count);
unsigned int ResamplerGetOutCount( RESAMPLER_HANDLE );
void ResamplerSetOutCount( RESAMPLER_HANDLE , unsigned int count);
float* ResamplerGetInpData ( RESAMPLER_HANDLE );
void ResamplerSetInpData ( RESAMPLER_HANDLE , float * data);
float* ResamplerGetOutData ( RESAMPLER_HANDLE );
void ResamplerSetOutData ( RESAMPLER_HANDLE , float * data);

#ifdef __cplusplus
}
#endif
#endif
