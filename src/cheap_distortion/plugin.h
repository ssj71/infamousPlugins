#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#if I_AM_LADSPA == 1
typedef void * LV2_Handle;
#else
#include <lv2/lv2plug.in/ns/lv2core/lv2.h>

// URI strings
#define URI_STRING "http://sourceforge.net/projects/infamousplugins:cheapdist"
#endif

// Port indexes
#define INDEX_AUDIO_IN_1 0
#define INDEX_AUDIO_OUT_1 1
#define INDEX_AGGRESSION_2
#define INDEX_INGAIN_3
#define INDEX_OUTGAIN_4

// Misc stuff for the skeleton code
#define LV2_NUM_AUDIO_INS 1
#define LV2_NUM_AUDIO_OUTS 1
#define LV2_NUM_INS 3
#define LV2_NUM_OUTS 0
#define LV2_NUM_ALL_PORTS 5
#define LV2_MIDI_OPTION 0
#define LV2_STATE_OPTION 0
#define LV2_EXT_OPTION 0
#define LV2_ACT_OPTION 0
#define LV2_DEACT_OPTION 0

// Indexes for accessing struct CHEAP_DISTORTION->In[] array
#define LV2_AGGRESSION 0
#define LV2_INGAIN 1
#define LV2_OUTGAIN 2

// Your plugin struct that the host passes to your DSP functions
typedef struct {
	float *	AudioIn[LV2_NUM_AUDIO_INS];
	float *	AudioOut[LV2_NUM_AUDIO_OUTS];
	float *	In[LV2_NUM_INS];
	uint32_t	Begin;
	uint32_t	End;
	float		SampleRate;
} CHEAP_DISTORTION2 ;

#ifdef __cplusplus
}
#endif
