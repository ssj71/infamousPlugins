//constants.h

#include<stdbool.h>
#include <stdint.h>

//harmonic stuff
#define MAX_N_HARMONICS 16
#define HARMONIC_MODE_SINC 0
#define HARMONIC_MODE_SAW 1
#define HARMONIC_MODE_SQR 2
#define HARMONIC_MODE_TRI 3

#define FUNC_SIN 0
#define FUNC_SAW 1
#define FUNC_SQR 2
#define FUNC_TRI 3
#define FUNC_WHITE 4
#define FUNC_RAND 5

//midi stuff
#define MIDI_NOTE_OFF        0x80
#define MIDI_NOTE_ON         0x90
#define MIDI_KEYPRESSURE     0xA0
#define MIDI_CONTROL_CHANGE  0xB0
#define MIDI_PROGRAMCHANGE   0xC0
#define MIDI_CHANNELPRESSURE 0xD0
#define MIDI_PITCHBEND       0xE0

#define MIDI_TYPE_MASK       0xF0
#define MIDI_CHANNEL_MASK    0x0F
#define MIDI_DATA_MASK       0x7F
#define MIDI_PITCH_CENTER    0x2000
#define MIDI_SUSTAIN_PEDAL   0x40
#define MIDI_ALL_NOTES_OFF   123
#define MIDI_ALL_SOUND_OFF   120



//angles
#define PI 3.1415926535897932384626433832795
#define INV_A .00227272727272727272727272727272727272727

//envelope states
#define ENV_ATTACK  0
#define ENV_DECAY   1
#define ENV_BREAK   2
#define ENV_SWELL   3
#define ENV_SUSTAIN 4
#define ENV_RELEASE 5
