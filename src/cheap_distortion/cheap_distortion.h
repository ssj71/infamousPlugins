#include "plugin.h"

// A CHEAP_DISTORTION is allocated by the framework CHEAP_DISTORTION.c. The
// framework fills in the CHEAP_DISTORTION2 sub-structure with info/data
// from the host, and passes it to your plugin functions below. You may add
// any fields you want, after the sub-structure. Typically you need this
// to store your own data across multiple calls to your pluginRun().
typedef struct {
	CHEAP_DISTORTION2		Host;

	// ====================================
	// Add any extra data fields you need here
	// ====================================
	uint32_t scale[4];

} CHEAP_DISTORTION;


void pluginRun(CHEAP_DISTORTION * );
#if LV2_MIDI_OPTION == 1
void pluginMidi(CHEAP_DISTORTION * , const unsigned char *);
#endif
#if LV2_ACT_OPTION == 1
void pluginActivate(CHEAP_DISTORTION * );
#endif
#if LV2_DEACT_OPTION == 1
void pluginDeActivate(CHEAP_DISTORTION * );
#endif
#if LV2_STATE_OPTION == 1
LV2_State_Status pluginSave(CHEAP_DISTORTION * );
LV2_State_Status pluginLoad(CHEAP_DISTORTION * );
#endif
void pluginFree(CHEAP_DISTORTION *);
int pluginAlloc(CHEAP_DISTORTION *);
