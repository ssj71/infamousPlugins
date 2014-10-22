//Spencer Jackson
//resampler.h

// c wrapper for the excellent zita-resampler library
// to learn more about this library and its useage you can read the documentation
// at http://kokkinizita.linuxaudio.org/linuxaudio/zita-resampler/resampler.html
#ifdef __cplusplus
extern "C" {
#endif

typedef void* RESAMPLER_HANDLE;
RESAMPLER_HANDLE ResamplerAlloc();
void ResamplerFree(RESAMPLER_HANDLE);
int ResamplerSetup(RESAMPLER_HANDLE, unsigned int   fs_inp, unsigned int fs_out, unsigned int nchan, unsigned int hlen);
void ResamplerClear(RESAMPLER_HANDLE);
int ResamplerReset(RESAMPLER_HANDLE);
int ResamplerProcess(RESAMPLER_HANDLE);
int ResamperNChan(RESAMPLER_HANDLE);
int ResamplerInpSize(RESAMPLER_HANDLE);
double ResamplerInpDist(RESAMPLER_HANDLE);

//access to public members
unsigned int ResamplerGetInpCount(RESAMPLER_HANDLE);
void ResamplerSetInpCount(RESAMPLER_HANDLE, unsigned int count);
unsigned int ResamplerGetOutCount(RESAMPLER_HANDLE);
void ResamplerSetInpCount(RESAMPLER_HANDLE, unsigned int count);
float* ResamplerGetInpData(RESAMPLER_HANDLE);
void ResamplerSetInpData(RESAMPLER_HANDLE, float * data);
float* ResamplerGetOutData(RESAMPLER_HANDLE);
void ResamplerSetOutData(RESAMPLER_HANDLE, float * data);

//VResampler Functions
typedef void* VRESAMPLER_HANDLE;
VRESAMPLER_HANDLE ResamplerAlloc();
void VResamplerFree(VRESAMPLER_HANDLE);
int VResamplerSetup(VRESAMPLER_HANDLE, double ratio, unsigned int nchan, unsigned int hlen);
void VResamplerClear(VRESAMPLER_HANDLE);
int VResamplerReset(VRESAMPLER_HANDLE);
int VResamplerProcess(VRESAMPLER_HANDLE);
int VResamperNChan(VRESAMPLER_HANDLE);
int VResamplerInpSize(VRESAMPLER_HANDLE);
double VResamplerInpDist(VRESAMPLER_HANDLE);
void VResamplerSetRRatio(VRESAMPLER_HANDLE, double ratio);
void VResamplerSetRRFilt(VRESAMPLER_HANDLE, double time);

//access to public members
unsigned int VResamplerGetInpCount(VRESAMPLER_HANDLE);
void VResamplerSetInpCount(VRESAMPLER_HANDLE, unsigned int count);
unsigned int VResamplerGetOutCount(VRESAMPLER_HANDLE);
void VResamplerSetInpCount(VRESAMPLER_HANDLE, unsigned int count);
float* VResamplerGetInpData(VRESAMPLER_HANDLE);
void VResamplerSetInpData(VRESAMPLER_HANDLE, float * data);
float* VResamplerGetOutData(VRESAMPLER_HANDLE);
void VResamplerSetOutData(VRESAMPLER_HANDLE, float * data);

#ifdef __cplusplus
}
#endif
