//Spencer Jackson
//envfollower.c
#include<envfollower.h>
#include<constants.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>


//main functions
LV2_Handle init_envfollower(const LV2_Descriptor *descriptor,double sample_rate, const char *bundle_path,const LV2_Feature * const* host_features)
{
    envfollower* plug = malloc(sizeof(envfollower));
    unsigned char i;

    plug->sample_rate = sample_rate;

    plug->nsum = 0;
    plug->sum = 0;

    //get urid map value for midi events
    for (int i = 0; host_features[i]; i++)
    {
        if (strcmp(host_features[i]->URI, LV2_URID__map) == 0)
        {
            LV2_URID_Map *urid_map = (LV2_URID_Map *) host_features[i]->data;
            if (urid_map)
            {
                plug->midi_event_type = urid_map->map(urid_map->handle, LV2_MIDI__MidiEvent);
                plug->other_type = urid_map->map(urid_map->handle, LV2_ATOM__Blank);
                plug->long_type = urid_map->map(urid_map->handle, LV2_ATOM__Long);
                plug->float_type = urid_map->map(urid_map->handle, LV2_ATOM__Float);
                plug->time_info_type = urid_map->map(urid_map->handle, LV2_TIME__Position);
                plug->beatsperbar_type = urid_map->map(urid_map->handle, LV2_TIME__barBeat);
                plug->bpm_type = urid_map->map(urid_map->handle, LV2_TIME__beatsPerMinute);
                plug->speed_type = urid_map->map(urid_map->handle, LV2_TIME__speed);
                plug->frame_type = urid_map->map(urid_map->handle, LV2_TIME__frame);
                plug->framespersec_type = urid_map->map(urid_map->handle, LV2_TIME__framesPerSecond);
                break;
            }
        }
    }

    return plug;
}

void connect_envfollower_ports(LV2_Handle handle, uint32_t port, void *data)
{
    envfollower* plug = (envfollower*)handle;
    if(port == INPUT)           plug->input_p = (float*)data;
    else if(port == OUTPUT)     plug->output_p = (float*)data;
    else if(port == MIDI_OUT)   plug->midi_out_p = (LV2_Atom_Sequence*)data;
    else if(port == CHANNEL)    plug->channel_p = (float*)data;
    else if(port == CONTROL_NO) plug->control_p = (float*)data;
    else if(port == MINV)       plug->min_p = (float*)data;
    else if(port == MAXV)       plug->max_p = (float*)data;
    else if(port == PEAKRMS)    plug->peakrms_p = (float*)data;
    else if(port == THRESHOLD)  plug->threshold_p = (float*)data;
    else if(port == SATURATION) plug->saturation_p = (float*)data;
    else if(port == ATIME)      plug->atime_p = (float*)data;
    else if(port == DTIME)      plug->dtime_p = (float*)data;
    else puts("UNKNOWN PORT YO!!");
}


static void
update_position(MidiFilter* self, const LV2_Atom_Object* obj)
{
    const MidiFilterURIs* uris = &self->uris;

    // Received new transport position/speed
    LV2_Atom *beat = NULL, *bpm = NULL, *speed = NULL;
    LV2_Atom *fps = NULL, *frame = NULL;
    lv2_atom_object_get(obj,
    uris->time_barBeat, &beat,
    uris->time_beatsPerMinute, &bpm,
    uris->time_speed, &speed,
    uris->time_frame, &frame,
    uris->time_fps, &fps,
    NULL);
    if (bpm && bpm->type == uris->atom_Float) {
        // Tempo changed, update BPM
        self->bpm = ((LV2_Atom_Float*)bpm)->body;
        self->available_info |= NFO_BPM;
    }
    if (speed && speed->type == uris->atom_Float) {
        // Speed changed, e.g. 0 (stop) to 1 (play)
        self->speed = ((LV2_Atom_Float*)speed)->body;
        self->available_info |= NFO_SPEED;
    }
    if (beat && beat->type == uris->atom_Float) {
        const double samples_per_beat = 60.0 / self->bpm * self->samplerate;
        self->bar_beats = ((LV2_Atom_Float*)beat)->body;
        self->beat_beats = self->bar_beats - floor(self->bar_beats);
        self->pos_bbt = self->beat_beats * samples_per_beat;
        self->available_info |= NFO_BEAT;
    }
    if (fps && fps->type == uris->atom_Float) {
        self->frames_per_second = ((LV2_Atom_Float*)frame)->body;
        self->available_info |= NFO_FPS;
    }
    if (frame && frame->type == uris->atom_Long) {
        self->pos_frame = ((LV2_Atom_Long*)frame)->body;
        self->available_info |= NFO_FRAME;
    }
}


void run_envfollower( LV2_Handle handle, uint32_t nframes)
{
    envfollower* plug = (envfollower*)handle;
    u_int32_t i;
    unsigned char j,k;
    float* buf = synth->output_p;
    LV2_Atom_Event event;
    uint32_t frame_no = 0;
    unsigned char* message;
    unsigned char type;
    unsigned char num, val;
    short bend;
    bool firstnote = true;
    NOTE* note;
    double astep = synth->waves.func_domain*(*synth->amod_freq_p)/synth->sample_rate;
    double fstep = synth->waves.func_domain*(*synth->fmod_freq_p)/synth->sample_rate;//need to decide where to calculate this. Probably not here.

    synth->ncells = *synth->nharmonics_p;
    synth->cell_lifetime = synth->sample_rate*(*synth->cell_life_p);
    synth->amod_g = *synth->amod_gain_p;
    synth->fmod_g = *synth->fmod_gain_p;


    memset(buf,0, sizeof(float)*nframes);//start by filling buffer with 0s, we'll add to this



    //finish off whatever frames are left
    if(frame_no != nframes-1)
    {
        //run_active_notes
        for(j=0;j<synth->nactive;j++)
        {
            note = &(synth->note[synth->active[j]]);
            play_note( note,
                       &(synth->waves),
                       nframes - frame_no,
                       &(buf[frame_no]),
                       synth->pitchbend,
                       *synth->master_gain_p,
                       (unsigned char)*synth->rule_p,
                       *synth->wave_p,
                       *synth->fmod_wave_p,
                       fstep,
                       *synth->amod_wave_p,
                       astep);

            //cleanup dead notes
            if(note->note_dead)
            {
                synth->nactive--;
                for(k=j;k<synth->nactive;k++)
                {
                    synth->active[k] = synth->active[k+1];
                }
            }
        }//active notes
    }//leftovers

}


void cleanup_envfollower(LV2_Handle handle)
{
    ENVFOLLOWER* plug = (ENVFOLLOWER*) handle;
    free(plug);
}

