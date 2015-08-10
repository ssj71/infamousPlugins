//constants.h

#include<stdbool.h>
#include <stdint.h>

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
#define MIDI_STOP            252
