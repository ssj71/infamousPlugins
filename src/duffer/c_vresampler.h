//Spencer Jackson
//c_vresampler.h

// c wrapper for the excellent zita-resampler library
// to learn more about this library and its useage you can read the documentation
// at http://kokkinizita.linuxaudio.org/linuxaudio/zita-resampler/resampler.html

#ifndef __C_VRESAMPLER_H
#define __C_VRESAMPLER_H

#ifdef __cplusplus
extern "C" {
#endif

//VVResampler Functions
typedef void* VRESAMPLER_HANDLE;
VRESAMPLER_HANDLE VResamplerAlloc();
void VResamplerFree( VRESAMPLER_HANDLE );
int VResamplerSetup( VRESAMPLER_HANDLE , double ratio, unsigned int nchan, unsigned int hlen);
void VResamplerClear( VRESAMPLER_HANDLE );
int VResamplerReset( VRESAMPLER_HANDLE );
int VResamplerProcess( VRESAMPLER_HANDLE );
int VResamplerNChan( VRESAMPLER_HANDLE );
int VResamplerInpSize( VRESAMPLER_HANDLE );
double VResamplerInpDist( VRESAMPLER_HANDLE );

//access to public members
unsigned int VResamplerGetInpCount( VRESAMPLER_HANDLE );
void VResamplerSetInpCount( VRESAMPLER_HANDLE , unsigned int count);
unsigned int VResamplerGetOutCount( VRESAMPLER_HANDLE );
void VResamplerSetOutCount( VRESAMPLER_HANDLE , unsigned int count);
float* VResamplerGetInpData ( VRESAMPLER_HANDLE );
void VResamplerSetInpData ( VRESAMPLER_HANDLE , float * data);
float* VResamplerGetOutData ( VRESAMPLER_HANDLE );
void VResamplerSetOutData ( VRESAMPLER_HANDLE , float * data);

#ifdef __cplusplus
}
#endif
#endif
