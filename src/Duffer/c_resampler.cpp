//Spencer Jackson
//resampler.cpp
#include"c_resampler.h"
#include"c_vresampler.h"
#include<zita-resampler/resampler.h>
#include<zita-resampler/vresampler.h>

// c wrapper for the excellent zita-resampler library
// to learn more about this library and its useage you can read the documentation
// at http://kokkinizita.linuxaudio.org/linuxaudio/zita-resampler/resampler.html

extern "C"{

RESAMPLER_HANDLE ResamplerAlloc()
{
   Resampler* r = new Resampler();
   //r = (Resampler *)malloc(sizeof(Resampler));
   return (void *)r;
}

void ResamplerFree(RESAMPLER_HANDLE r)
{
   //free(static_cast<Resampler*>(r));
   delete[] static_cast<Resampler*>(r);
}

int ResamplerSetup(RESAMPLER_HANDLE r, unsigned int   fs_inp, unsigned int fs_out, unsigned int nchan, unsigned int hlen)
{
   return static_cast<Resampler*>(r)->setup(fs_inp,fs_out,nchan,hlen);
}

void ResamplerClear(RESAMPLER_HANDLE r)
{
   static_cast<Resampler*>(r)->clear();
}

int ResamplerReset(RESAMPLER_HANDLE r)
{
   return static_cast<Resampler*>(r)->reset();
}

int ResamplerProcess(RESAMPLER_HANDLE r)
{
   return static_cast<Resampler*>(r)->process();
}

int ResamperNChan(RESAMPLER_HANDLE r)
{
   return static_cast<Resampler*>(r)->nchan();
}

int ResamplerInpSize(RESAMPLER_HANDLE r)
{
   return static_cast<Resampler*>(r)->inpsize();
}

double ResamplerInpDist(RESAMPLER_HANDLE r)
{
   return static_cast<Resampler*>(r)->inpdist();
}


//access to public members
unsigned int ResamplerGetInpCount(RESAMPLER_HANDLE r)
{
   return static_cast<Resampler*>(r)->inp_count;
}

void ResamplerSetInpCount(RESAMPLER_HANDLE r, unsigned int count)
{
   static_cast<Resampler*>(r)->inp_count = count;
}

unsigned int ResamplerGetOutCount(RESAMPLER_HANDLE r)
{
   return static_cast<Resampler*>(r)->out_count;
}

void ResamplerSetOutCount(RESAMPLER_HANDLE r, unsigned int count)
{
   static_cast<Resampler*>(r)->out_count = count;
}

float* ResamplerGetInpData(RESAMPLER_HANDLE r)
{
   return static_cast<Resampler*>(r)->inp_data;

}

void ResamplerSetInpData(RESAMPLER_HANDLE r, float * data)
{
   static_cast<Resampler*>(r)->inp_data = data;
}

float* ResamplerGetOutData(RESAMPLER_HANDLE r)
{
   return static_cast<Resampler*>(r)->out_data;
}

void ResamplerSetOutData(RESAMPLER_HANDLE r, float * data)
{
   static_cast<Resampler*>(r)->out_data = data;
}






//VResampler Functions


VRESAMPLER_HANDLE VResamplerAlloc(){
   VResampler* r = new VResampler();
   return (void *)r;
}

void VResamplerFree(VRESAMPLER_HANDLE r)
{
    delete[] static_cast<VResampler*>(r);
}

int VResamplerSetup(VRESAMPLER_HANDLE r, double ratio, unsigned int nchan, unsigned int hlen)
{
    return static_cast<VResampler*>(r)->setup(ratio,nchan,hlen);
}

void VResamplerClear(VRESAMPLER_HANDLE r)
{
    return static_cast<VResampler*>(r)->clear();
}

int VResamplerReset(VRESAMPLER_HANDLE r)
{
    return static_cast<VResampler*>(r)->reset();
}

int VResamplerProcess(VRESAMPLER_HANDLE r)
{
    return static_cast<VResampler*>(r)->process();
}

int VResamplerNChan(VRESAMPLER_HANDLE r)
{
    return static_cast<VResampler*>(r)->nchan();
}

int VResamplerInpSize(VRESAMPLER_HANDLE r)
{
    return static_cast<VResampler*>(r)->inpsize();
}

double VResamplerInpDist(VRESAMPLER_HANDLE r)
{
    return static_cast<VResampler*>(r)->inpdist();
}

void VResamplerSetRRatio(VRESAMPLER_HANDLE r, double ratio)
{
    static_cast<VResampler*>(r)->set_rratio(ratio);
}

void VResamplerSetRRFilt(VRESAMPLER_HANDLE r, double time)
{
    static_cast<VResampler*>(r)->set_rrfilt(time);
}


//access to public members
unsigned int VResamplerGetInpCount(VRESAMPLER_HANDLE r)
{
    return static_cast<VResampler*>(r)->inp_count;
}

void VResamplerSetInpCount(VRESAMPLER_HANDLE r, unsigned int count)
{
    static_cast<VResampler*>(r)->inp_count = count;
}

unsigned int VResamplerGetOutCount(VRESAMPLER_HANDLE r)
{
    return static_cast<VResampler*>(r)->out_count;
}

void VResamplerSetOutCount(VRESAMPLER_HANDLE r, unsigned int count)
{
    static_cast<VResampler*>(r)->inp_count = count;
}

float* VResamplerGetInpData(VRESAMPLER_HANDLE r)
{
    return static_cast<VResampler*>(r)->inp_data;
}

void VResamplerSetInpData(VRESAMPLER_HANDLE r, float * data)
{
    static_cast<VResampler*>(r)->inp_data = data;
}

float* VResamplerGetOutData(VRESAMPLER_HANDLE r)
{
    return static_cast<VResampler*>(r)->out_data;
}

void VResamplerSetOutData(VRESAMPLER_HANDLE r, float * data)
{
    static_cast<VResampler*>(r)->out_data = data;
}



}//extern c
