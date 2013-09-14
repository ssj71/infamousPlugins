#ifdef __cplusplus
extern "C" {
#endif

#include "cheap_distortion.h"

//this bitfield punning buisness is bad form and you're a bad developer for
//even looking at code like this. But it works with gcc on x86 so I did it.
typedef union
{
    float f;
    struct
    {
		union val
		{
			uint32_t num : 31;
			struct ieee
			{
        		uint32_t significand : 23;
        		uint32_t exponent : 8;
			} ieee754;
		} value;
        uint32_t sign : 1;
    } parts;
}float_dissector;




/************************ pluginRun() ************************
 * Called by host to add DSP to the waveform data in the
 * input buffer(s), and stores the new data in the output
 * buffer(s).
 *
 * plugin->Host.AudioIn[]
 *		An array of pointers to the channels of input (source)
 *		waveform data.
 *
 * plugin->Host.AudioOut[]
 *		An array of pointers where to store the channels of output
 *		waveform data.
 *
 * plugin->Host.Begin
 *		An index where the data starts in AudioIn[].
 *
 * plugin->Host.End
 *		An index where the data stops in AudioIn[].
 *
 * User Input (In[] array)
 *		Aggresion = *Host.In[LV2_AGGRESSION]

 * NOTES: AudioIn[] and AudioOut[] can both point to the same buffer
 * if desired. This means the original waveform data is modified.
 */
void pluginRun(CHEAP_DISTORTION * plugin)
{
 	float_dissector f;
	uint8_t index = (uint8_t)*plugin->Host.In[LV2_AGGRESSION];
    int8_t in = (int8_t)*plugin->Host.In[LV2_INGAIN];
    int8_t out = (int8_t)*plugin->Host.In[LV2_OUTGAIN];
	while (plugin->Host.Begin < plugin->Host.End)
	{
		f.f = *(plugin->Host.AudioIn[0] + plugin->Host.Begin);
		f.parts.value.ieee754.exponent +=in;
		f.parts.value.num = (f.parts.value.num)>>index;
        f.parts.value.ieee754.exponent += plugin->scale[index];
		f.parts.value.ieee754.exponent += out;
        *(plugin->Host.AudioOut[0] + plugin->Host.Begin) = f.f;
		++plugin->Host.Begin;
	}
}





/*********************** pluginAlloc() ***********************
 * Called once when your plugin is loaded. This is
 * your first function called by the host.
 *
 * You're passed a CHEAP_DISTORTION struct, but at this point
 * it hasn't yet been filled in with info and data (pointers). The
 * only field that is meaningful here is:
 *
 * plugin->SampleRate
 *
 * All other data fields are cleared, including any extra fields
 * you added to to the CHEAP_DISTORTION. You should initialize those
 * extra fields as desired, and allocate any resources (RAM) you
 * need (and store it in those extra fields).
 *
 * RETURNS: 0 if success, or errno if fail.
 *
 * NOTE: If you return errno, then pluginFree() is called, and none
 * of your other funcs are called.
 */

int pluginAlloc(CHEAP_DISTORTION * plugin)
{
	// Init any extra fields (you added) to the CHEAP_DISTORTION, and alloc any
	// resources you need. Return non-zero if you have an error.
	// NOTE: Extra fields have already been set to 0.
	plugin->scale[0] = 0;
	plugin->scale[1] = 63;
	plugin->scale[2] = 95;
	plugin->scale[3] = 111;
	return 0;
}





/*********************** pluginFree() ************************
 * Frees any resources you allocated in pluginAlloc().
 *
 * NOTE: Do not free() the CHEAP_DISTORTION itself.
 */

void pluginFree(CHEAP_DISTORTION * plugin)
{
}





/*********************** pluginMidi() ***********************
 * Called by host when a MIDI message is received.
 *
 * data
 *		Pointer to the received MIDI message.
 *
 * plugin->plugin->Host.End
 *		Size (in bytes) of the message.
 *
 * NOTE: This is called only if you check the "MIDI" box
 * on LV2 Create's General page.
 */

#if LV2_MIDI_OPTION == 1

void pluginMidi(CHEAP_DISTORTION * plugin, const unsigned char * data)
{
}

#endif





/******************** pluginActivate() ********************
 * Called by host to reset the state of a plugin, once before
 * our host starts making multiple calls to our run function.
 *
 * NOTE: This is called only if you check the "Activate" box
 * on LV2 Create's General page.
 */

#if LV2_ACT_OPTION == 1

void pluginActivate(CHEAP_DISTORTION * plugin)
{
}

#endif





/******************* pluginDeActivate() *******************
 * Called by host once after done making multiple calls to our
 * pluginRun function.
 *
 * NOTE: This is called only if you check the "DeActivate" box
 * on LV2 Create's General page.
 */

#if LV2_DEACT_OPTION == 1

void pluginDeActivate(CHEAP_DISTORTION * plugin)
{
}

#endif





/*********************** pluginSave() ***********************
 * Called by host to save the values of any variables you
 * defined on LV2 Create's State page.
 *
 * NOTE: Call Lv2SaveVar() to save each variable, passing
 * its LV2VAR_ symbol defined in CHEAP_DISTORTION.h.
 *
 * RETURNS: LV2_STATE_SUCCESS if ok.
 */

#if LV2_STATE_OPTION == 1

LV2_State_Status pluginSave(CHEAP_DISTORTION * plugin)
{
	return LV2_STATE_SUCCESS;
}





/*********************** pluginLoad() ***********************
 * Called by host to load the values of any variables you
 * defined on LV2 Create's State page.
 *
 * NOTE: Call Lv2LoadVar() to load each variable, passing
 * its LV2VAR_ symbol defined in CHEAP_DISTORTION.h. Call Lv2FreePathVar() to
 * free each Path value.
 *
 * RETURNS: LV2_STATE_SUCCESS if ok.
 */

LV2_State_Status pluginLoad(CHEAP_DISTORTION * plugin)
{
	return LV2_STATE_SUCCESS;
}

#endif

#ifdef __cplusplus
}
#endif
