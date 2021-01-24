//Spencer Jackson
//mindi.c
#include<mindi.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<lv2.h>
#include<lv2/lv2plug.in/ns/ext/urid/urid.h>
#include<lv2/lv2plug.in/ns/ext/midi/midi.h>
#include<lv2/lv2plug.in/ns/ext/atom/util.h>
#include "lv2/lv2plug.in/ns/ext/time/time.h"
#include "lv2/lv2plug.in/ns/ext/atom/forge.h"

//midi stuff
#define MIDI_NOTE_OFF        0x80
#define MIDI_NOTE_ON         0x90
#define MIDI_KEYPRESSURE     0xA0
#define MIDI_CONTROL_CHANGE  0xB0
#define MIDI_PROGRAMCHANGE   0xC0
#define MIDI_CHANNELPRESSURE 0xD0
#define MIDI_PITCHBEND       0xE0
#define MIDI_SYSTEMMSG       0xF0

#define MIDI_TYPE_MASK       0xF0
#define MIDI_CHANNEL_MASK    0x0F
#define MIDI_DATA_MASK       0x7F
#define MIDI_PITCH_CENTER    0x2000
#define MIDI_SUSTAIN_PEDAL   0x40
#define MIDI_ALL_NOTES_OFF   123
#define MIDI_STOP            252

typedef struct _MINDI
{
    float enable;
    float noteccpg;
    float value;
    float startup;
    float msPerFrame;
    bool oneshot;
    bool notesent;
    bool momentstate;

    //midi
    LV2_URID_Map* urid_map;
    LV2_URID midi_ev_urid;
    LV2_Atom_Forge forge;
    LV2_Atom_Forge_Frame frame;

    //ports
    LV2_Atom_Sequence* midi_out_p;
    float* enable_p;
    float* msgtype_p;
    float* chan_p; 
    float* noteccpg_p;
    float* value_p;
    float* delay_p;
    float* autoff_p;
    float* moment_p;
    float* momentaryvalue_p;
} MINDI;

//main functions
LV2_Handle init_mindi(const LV2_Descriptor *descriptor,double sample_rate, const char *bundle_path,const LV2_Feature * const* host_features)
{
    MINDI* plug = malloc(sizeof(MINDI));
    plug->enable = 1;
    plug->noteccpg = 0;
    plug->value = 0;
    plug->startup = 0;
    plug->msPerFrame = 1000.0/sample_rate;
    plug->oneshot = false;
    plug->notesent = false;
    plug->momentstate = false;

    //get urid map value for midi events
    for (int i = 0; host_features[i]; i++)
    {
        if (strcmp(host_features[i]->URI, LV2_URID__map) == 0)
        {
            plug->urid_map = (LV2_URID_Map *) host_features[i]->data;
            if (plug->urid_map)
            {
                plug->midi_ev_urid = plug->urid_map->map(plug->urid_map->handle, LV2_MIDI__MidiEvent);
                break;
            }
        }
    }

    lv2_atom_forge_init(&plug->forge,plug->urid_map);

    return plug;
}


void connect_mindi_ports(LV2_Handle handle, uint32_t port, void *data)
{
    MINDI* plug = (MINDI*)handle;
    if(port == MIDI_OUT)            plug->midi_out_p = (LV2_Atom_Sequence*)data;
    else if(port == ENABLE)         plug->enable_p = (float*)data;
    else if(port == MSGTYPE)        plug->msgtype_p = (float*)data;
    else if(port == CHAN)           plug->chan_p = (float*)data;
    else if(port == NOTECCPG)       plug->noteccpg_p = (float*)data;
    else if(port == VALUE)          plug->value_p = (float*)data;
    else if(port == DELAY)          plug->delay_p = (float*)data;
    else if(port == AUTOFF)         plug->autoff_p = (float*)data;
    else if(port == MOMENT)         plug->moment_p = (float*)data;
    else if(port == MOMENTARYVALUE) plug->momentaryvalue_p = (float*)data;
}

void run_mindi( LV2_Handle handle, uint32_t nframes)
{
    MINDI* plug = (MINDI*)handle;
    LV2_Atom midiatom;
    uint8_t msg[3];

    if( (*plug->enable_p && 
          ( (plug->noteccpg != *plug->noteccpg_p) ||
            (plug->value != *plug->value_p) ||
            (plug->enable != *plug->enable_p) ||
            (!plug->oneshot && plug->startup > *plug->delay_p) ||
            (plug->momentstate != *plug->moment_p) )
        ) ||
        (!*plug->enable_p && plug->notesent && *plug->msgtype_p == 0x09) 
      )
    {
        if(plug->startup >= *plug->delay_p)
            plug->oneshot = true;
        if(!plug->oneshot)
            plug->startup += nframes*plug->msPerFrame;

        plug->noteccpg = *plug->noteccpg_p;
        plug->value = *plug->value_p;

        float valuetosend = (*plug->moment_p) ? (*plug->momentaryvalue_p) : (*plug->value_p);

        //get midi port ready
        const uint32_t capacity = plug->midi_out_p->atom.size;
        lv2_atom_forge_set_buffer(&plug->forge,(uint8_t*)plug->midi_out_p, capacity);
        lv2_atom_forge_sequence_head(&plug->forge, &plug->frame, 0);
        midiatom.type = plug->midi_ev_urid;
        midiatom.size = 3;//midi CC

        //make event
        msg[0] = (((uint8_t)*plug->msgtype_p)<<4) + (uint8_t)(*plug->chan_p);
        //convert to note-off if appropriate
        if(((!*plug->moment_p && plug->momentstate) || !*plug->enable_p) && plug->notesent && *plug->msgtype_p == 0x09)
        {
            plug->notesent = false;
            msg[0] -= 0x10;
        }
        else if(*plug->autoff_p && *plug->msgtype_p == 0x09)
            plug->notesent = true; 

        if(*plug->msgtype_p == 0x0D)
        {
            // Channel Pressure messages use value (only)
            msg[1] = MIDI_DATA_MASK & (uint8_t)valuetosend;
        }
        else
        {        
            msg[1] = MIDI_DATA_MASK & (uint8_t)plug->noteccpg;
            msg[2] = MIDI_DATA_MASK & (uint8_t)valuetosend;
        }

        midiatom.type = plug->midi_ev_urid;

        switch(msg[0]&MIDI_TYPE_MASK)
        {
        case MIDI_NOTE_OFF:
        case MIDI_NOTE_ON:
        case MIDI_KEYPRESSURE:
        case MIDI_CONTROL_CHANGE:
        case MIDI_PITCHBEND:
            midiatom.size = 3;
            break; 
        
        case MIDI_PROGRAMCHANGE:
        case MIDI_CHANNELPRESSURE:
            midiatom.size = 2;
            break;
        }

        lv2_atom_forge_frame_time(&plug->forge,0);
        lv2_atom_forge_raw(&plug->forge,&midiatom,sizeof(LV2_Atom));
        lv2_atom_forge_raw(&plug->forge,msg,midiatom.size);
        lv2_atom_forge_pad(&plug->forge,midiatom.size+sizeof(LV2_Atom));
    }
    else if(!plug->oneshot && plug->startup)
        plug->startup += nframes*plug->msPerFrame;
    plug->enable = *plug->enable_p;
    plug->momentstate = *plug->moment_p;
}

void cleanup_mindi(LV2_Handle handle)
{
    MINDI* plug = (MINDI*) handle;
    free(plug);
}


//lv2 stuff
static const LV2_Descriptor mindi_descriptor=
{
    MINDI_URI,
    init_mindi,
    connect_mindi_ports,
    NULL,//activate
    run_mindi,
    NULL,//deactivate
    cleanup_mindi,
    NULL//extension
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index)
    {
    case 0:
        return &mindi_descriptor;
    default:
        return NULL;
    }
}
