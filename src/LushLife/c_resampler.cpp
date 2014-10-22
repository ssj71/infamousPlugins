//Spencer Jackson
//resampler.cpp
#include"c_resampler.h"
#include<zita-resampler/resampler.h>

// c wrapper for the excellent zita-resampler library
// to learn more about this library and its useage you can read the documentation
// at http://kokkinizita.linuxaudio.org/linuxaudio/zita-resampler/resampler.html

typedef struct _Rsampler
{
    Resampler rsmp;
}Rsampler;

RESAMPLER_HANDLE ResamplerAlloc()
{
   Rsampler* r;
   r = (Resampler *)malloc(sizeof(Rsampler));
   return (void *)r;
}

void ResamplerFree(RESAMPLER_HANDLE r)
{
   free((Rsampler *)r);
}

int ResamplerSetup(RESAMPLER_HANDLE r, unsigned int   fs_inp, unsigned int fs_out, unsigned int nchan, unsigned int hlen)
{
   return (Rsampler *)r->rsmp.setup(fs_inp,fs_out,nchan,hlen);
}

void ResamplerClear(RESAMPLER_HANDLE r)
{
   (Rsampler *)r->rsmp.clear();
}

int ResamplerReset(RESAMPLER_HANDLE r)
{
   return (Rsampler *)r->rsmp.reset();
}

int ResamplerProcess(RESAMPLER_HANDLE r)
{
   return (Rsampler *)r->rsmp.process();
}

int ResamperNChan(RESAMPLER_HANDLE r)
{
   return (Rsampler *)r->rsmp.nchan();
}

int ResamplerInpSize(RESAMPLER_HANDLE r)
{
   return (Rsampler *)r->rsmp.inpsize();
}

double ResamplerInpDist(RESAMPLER_HANDLE r)
{
   return (Rsampler *)r->rsmp.inpdist();
}


//access to public members
unsigned int ResamplerGetInpCount(RESAMPLER_HANDLE r)
{
   return (Rsampler *)r->rsmp.inp_count;
}

void ResamplerSetInpCount(RESAMPLER_HANDLE r, unsigned int count)
{
   (Rsampler *)r->rsmp.inp_count = count;
}

unsigned int ResamplerGetOutCount(RESAMPLER_HANDLE r)
{
   return (Rsampler *)r->rsmp.out_count;
}

void ResamplerSetInpCount(RESAMPLER_HANDLE r, unsigned int count)
{
   (Rsampler *)r->rsmp.out_count = count;
}

float* ResamplerGetInpData(RESAMPLER_HANDLE r)
{
   return (Rsampler *)r->rsmp.inp_data;

}

void ResamplerSetInpData(RESAMPLER_HANDLE r, float * data)
{
   (Rsampler *)r->rsmp.inp_data = data;
}

float* ResamplerGetOutData(RESAMPLER_HANDLE r)
{
   return (Rsampler *)r->rsmp.out_data;
}

void ResamplerSetOutData(RESAMPLER_HANDLE r, float * data)
{
   (Rsampler *)r->rsmp.out_data = data;
}







//VResampler Functions

typedef struct _VRsampler
{
    VResampler rsmp;
}VRsampler;

VRESAMPLER_HANDLE VResamplerAlloc(){
   VRsampler* r;
   r = (VResampler *)malloc(sizeof(VRsampler));
   return (void *)r;
}

void VResamplerFree(VRESAMPLER_HANDLE r)
{
    free((VRsampler *)r);
}

int VResamplerSetup(VRESAMPLER_HANDLE r, double ratio, unsigned int nchan, unsigned int hlen)
{
    return (VRsampler *)r->rsmp.setup(ratio,nchan,hlen);
}

void VResamplerClear(VRESAMPLER_HANDLE r)
{
    return (VRsampler *)r->rsmp.clear();
}

int VResamplerReset(VRESAMPLER_HANDLE r)
{
    return (VRsampler *)r->rsmp.reset();
}

int VResamplerProcess(VRESAMPLER_HANDLE r)
{
    return (VRsampler *)r->rsmp.process();
}

int VResamperNChan(VRESAMPLER_HANDLE r)
{
    return (VRsampler *)r->rsmp.nchan();
}

int VResamplerInpSize(VRESAMPLER_HANDLE r)
{
    return (VRsampler *)r->rsmp.inpsize();
}

double VResamplerInpDist(VRESAMPLER_HANDLE r)
{
    return (VRsampler *)r->rsmp.inp_dist();
}

void VResamplerSetRRatio(VRESAMPLER_HANDLE r, double ratio)
{
    (VRsampler *)r->rsmp.set_rratio(ratio);
}

void VResamplerSetRRFilt(VRESAMPLER_HANDLE r, double time)
{
    (VRsampler *)r->rsmp.set_rrfilt(time);
}


//access to public members
unsigned int VResamplerGetInpCount(VRESAMPLER_HANDLE r)
{
    return (VRsampler *)r->rsmp.inp_count;
}

void VResamplerSetInpCount(VRESAMPLER_HANDLE r, unsigned int count)
{
    (VRsampler *)r->rsmp.inp_count = count;
}

unsigned int VResamplerGetOutCount(VRESAMPLER_HANDLE r)
{
    return (VRsampler *)r->rsmp.out_count;
}

void VResamplerSetInpCount(VRESAMPLER_HANDLE r, unsigned int count)
{
    (VRsampler *)r->rsmp.inp_count = count;
}

float* VResamplerGetInpData(VRESAMPLER_HANDLE r)
{
    return (VRsampler *)r->rsmp.inp_data;
}

void VResamplerSetInpData(VRESAMPLER_HANDLE r, float * data)
{
    (VRsampler *)r->rsmp.inp_data = data;
}

float* VResamplerGetOutData(VRESAMPLER_HANDLE r)
{
    return (VRsampler *)r->rsmp.out_data;
}

void VResamplerSetOutData(VRESAMPLER_HANDLE r, float * data)
{
    (VRsampler *)r->rsmp.out_data = data;
}
