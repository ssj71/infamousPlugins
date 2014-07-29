#ifdef __cplusplus
extern "C" {
#endif

#include "cheap_distortion.h"

#define SIZEOF_URI_STRING 57
#define SIZEOF_EXT_URI_STRING 25

// Our own URI we made up for our plugin. Must match the one in our TTL file
static const char UriStr[] = URI_STRING;

static const char MapUriStr[] = "http://lv2plug.in/ns/ext/urid#map";





/*************************** run() ***************************
 * Called by host to add DSP to the waveform data in the
 * input buffer(s), and stores the new data in the output
 * buffer(s).
 *
 * instance = Ptr to our CHEAP_DISTORTION.
 * sampleFrames =	How many floats to process per channel.
 */

static void run(LV2_Handle instance, uint32_t sampleFrames)
{
	register CHEAP_DISTORTION *	plugin;

	if ((plugin = (CHEAP_DISTORTION *)instance))
	{
		plugin->Host.Begin = 0;

		plugin->Host.End = sampleFrames - plugin->Host.Begin;
		pluginRun(plugin);
	}
}





/************************* cleanup() **************************
 * Called by host to free the plugin instance (i.e. the
 * CHEAP_DISTORTION gotten via instantiate()).
 *
 * instance =	Our own CHEAP_DISTORTION.
 */

static void cleanup(LV2_Handle instance)
{
	if (instance)
	{
		// Let the DSP code free any extra resources it allocated
		pluginFree((CHEAP_DISTORTION *)instance);

		free(instance);
	}
}





/*********************** instantiate() ************************
 * Called by host to alloc/init a new plugin instance.
 *
 * RETURNS: If success, a pointer to our own CHEAP_DISTORTION
 * that holds all data needed to implement our plugin.
 */

static LV2_Handle instantiate(const LV2_Descriptor * descriptor, double rate, const char * path, const LV2_Feature * const * features)
{
	register CHEAP_DISTORTION *	plugin;

	// Create an instance of CHEAP_DISTORTION (defined in cheap_distortion.h)
	if ((plugin = (CHEAP_DISTORTION *)malloc(sizeof(CHEAP_DISTORTION))))
	{
		memset(plugin, 0, sizeof(CHEAP_DISTORTION));

		plugin->Host.SampleRate = (float)rate;

		// Let the DSP Code do any further init of its CHEAP_DISTORTION
		if (pluginAlloc(plugin))
		{
			cleanup(plugin);
			plugin = 0;
		}
	}

	// Return our CHEAP_DISTORTION to the host (and the
	// host passes back to our functions)
	return (LV2_Handle)plugin;
}





/*********************** connectPort() ************************
 * Called by host to connect a port to a data location (ie, allow
 * us to store a pointer to a host-supplied data or buffer. NOTE:
 * all host data is a float).
 *
 * instance =	Our own CHEAP_DISTORTION.
 * port =		Indicates what hostData is being supplied.
 * hostData =	Pointer to host float data, or buffer of floats.
 */

static void connectPort(LV2_Handle instance, uint32_t port, void * hostData)
{
	register CHEAP_DISTORTION *	plugin;

	plugin = (CHEAP_DISTORTION *)instance;
	if (plugin && port < LV2_NUM_ALL_PORTS)
	{
				if (port < LV2_NUM_AUDIO_INS)
			plugin->Host.AudioIn[port] = (float *)hostData;
		else
		{
			port -= LV2_NUM_AUDIO_INS;
			if (port < LV2_NUM_AUDIO_OUTS)
				plugin->Host.AudioOut[port] = (float *)hostData;
			else
			{
				port -= LV2_NUM_AUDIO_OUTS;
				plugin->Host.In[port] = (float *)hostData;
			}
		}
	}
}





/********************* lv2_descriptor() **********************
 * Returns a pointer to our LV2_Descriptor struct at the
 * requested index.
 *
 * index =	The plugin index.
 *
 * NOTE: "index" ranges from 0 to how many plugins we support
 * (minus 1). For this example, we have 1 plugin. We'll assign an
 * index of 0 for it. Any other index values, we return a 0 to
 * indicate we have no further plugin types.
 *
 * This function must be named "lv2_descriptor", and can't be
 * static. Our plugin must contain this function.
 */

static const LV2_Descriptor PluginDescriptor = {
	UriStr,
	instantiate,
	connectPort,
	NULL,
	run,
	NULL,
	cleanup,
	NULL};

LV2_SYMBOL_EXPORT const LV2_Descriptor * lv2_descriptor(uint32_t index)
{
	if (!index) return &PluginDescriptor;
	return 0;
}

#ifdef __cplusplus
}
#endif
