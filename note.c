//Spencer Jackson
//note.c

#include<note.h>
#include<math.h>

#define ENV_ATTACK  0
#define ENV_DECAY   1
#define ENV_BREAK   2
#define ENV_SWELL   3
#define ENV_SUSTAIN 4
#define ENV_RELEASE 5
//private function prototypes

void init_note(NOTE *self, double sample_rate, unsigned char value, float* nharmonics, float* harmonic_length, float* amod_gain, float* fmod_gain)
{
    unsigned char i;
    self->value = value;
    self->velocity = .8;
    self->pitchbend = 0;//pow(2,pitchbend/49152);//convert to step coefficient //MOVE TO SYNTH!!!

    //currently hardcoding in function, may use optimised or selectable versions later
    self->base_wave = FUNC_SIN;
    self->base_func = &sin;
    self->base_func_min = -PI;
    self->base_func_max = PI;

    self->nharmonics = nharmonics;
    self->harm_length = harmonic_length;
    for(i=0;i<MAX_N_HARMONICS;i++)
    {
        self->phase[i] = 0;
        self->step[i] = (self->base_func_max - self->base_func_min)*440/sample_rate*pow(2,(value-69)/12);

    }
    phase[MAX_N_HARMONICS] = 0;//0th harmonic is root

    self->env_gain = 0;
    self->stop_frame = 0;
    for(i=0;i<6;i++)
    {
        self->envelope[i] = envelope[i];
    }

    self->fmod_func = &sin;
    self->fmod_gain = 0;//start this at 0
    self->fmod_phase = 0;
    self->fmod_step = 0;

    self->amod_func = &sin;
    self->amod_gain = 0;//start this at 0
    self->amod_phase = 0;
    self->amod_step = 0;
}

void start_note(NOTE*           self,
                unsigned char   velocity,
                float           harmonic_gain[],
                unsigned short  harmonics,
                float           envelope[],
                unsigned char   base_wave,
                unsigned char   amod_wave,
                unsigned char   fmod_wave)
{
    unsigned char i;
    self->velocity = (float)velocity/127;//currently linear which is lame

    //harmonics
    self->nframes_since_harm_change = 0;
    for(i=0;i<MAX_N_HARMONICS;i++)
    {
        self->harm_gain[i] = self->velocity*harmonic_gain[i];
        self->phase[i] = 0;
    }
    //and the root
    i = MAX_N_HARMONICS;
    self->harm_gain[i] = self->velocity*harmonic_gain[i];
    self->phase[i] = 0;
    if(harmonics)
        self->harmonics = harmonics;

    //envelope
    self->env_gain = 0;
    self->env_state = ENV_ATTACK;
    self->note_dead = false;
    for(i=0;i<6;i++)
        self->envelope[i] = envelope[i];

    //waveform
    if(self->base_wave != base_wave)
    {
        self->base_wave = base_wave;
        switch(base_wave)
        {
            case FUNC_SIN:
                self->base_func = &sin;
                self->base_func_min = -PI;
                self->base_func_max = PI;
                break;
            default:
                self->base_func = &sin;
                self->base_func_min = -PI;
                self->base_func_max = PI;
                break;
        }
    }

    //modulations
    self->amod_phase = 0;
    if(self->amod_wave != amod_wave)
    {
        self->amod_wave = amod_wave;
        switch(amod_wave)
        {
            case FUNC_SIN:
                self->amod_func = &sin;
                self->amod_func_min = -PI;
                self->amod_func_max = PI;
                break;
            default:
                self->amod_func = &sin;
                self->amod_func_min = -PI;
                self->amod_func_max = PI;
                break;
        }
    }

    self->fmod_phase = 0;
    if(self->fmod_wave != fmod_wave)
    {
        switch(fmod_wave)
        {
            case FUNC_SIN:
                self->fmod_func = &sin;
                self->fmod_func_min = -PI;
                self->fmod_func_max = PI;
                break;
            default:
                self->fmod_func = &sin;
                self->fmod_func_min = -PI;
                self->fmod_func_max = PI;
                break;
        }
    }
}


void playnote(NOTE *self,
              uint32_t nframes,
              uint32_t start_frame,
              float buffer[],
              double pitchbend,
              double amod_step,
              double fmod_step)
{
    unsigned char i,j;
    //uint32_t chunk[MAX_N_CELL_CHANGES + 3];
    uint32_t *harm_chng_frame = self->harm_chng_frame;
    harm_chng_frame[self->nharm_chng++] = nframes;

    float fmod_coeff = 1;
    float amod_coeff = 1;

    //divide into chunks per envelpe region
    uint32_t chunk = nframes - start_frame;
    float env_slope = envelope[env_state];
    bool recurse = false;
    bool newcells = false;

    //need to make sure chunks aren't overlapping!
    //divide into chunks for cell lifetimes
    if(self->nframes_since_harm_change + chunk > *self->harm_length)
    {
        chunk = *self->harm_length - self->nframes_since_harm_change;
        recurse = true;
        newcells = true;
    }

    //divide into chunks for envelope
    float env_end_gain = env_gain + env_slope*chunk;
    if (self->env_state<ENV_SUSTAIN)
    {
        if(self->env_state != ENV_SWELL)
        {
            if(env_end_gain > 1.0)
            {
                //do no. frames till Attack complete
                chunk = floor((1-env_gain)/env_slope);
                self->env_state++;
                recurse = TRUE;
            }
            else if(env_end_gain <= envelope[ENV_BREAK])
            {
                //do no. frames till Decay complete
                chunk = floor((self->envelope[ENV_BREAK] - env_gain)/env_slope);
                self->env_state+=2;//skip B
                recurse = TRUE;
            }
        }
        else if(env_end_gain >= envelope[ENV_SUSTAIN])
        {
            //do no. frames till Swell complete
            chunk = floor((self->envelope[ENV_SUSTAIN] - env_gain)/env_slope);
            self->env_state++;
            recurse = TRUE;
        }
    }else if(self->env_state > ENV_SUSTAIN)//release
    {
        if (env_end_gain <= 0)
        {
            chunk = floor(env_gain/env_slope);//don't process past note death
            note_dead = TRUE;
        }
    }
    else//in sustain
    {
        env_slopef = 0;
    }


    //handle the cell lifetimes outside of the note and play chunks.
    for(i=start_frame;i<chunk+start_frame;i++ )
    {
        //modulation
        if(self->env_state == ENV_SUSTAIN)
        {
            fmod_coeff = pow(2,*self->fmod_gain*(self->fmod_func(self->fmod_phase)));
            self->fmod_phase += fmod_step;
            if(self->fmod_phase >= self->fmod_func_max)
            {
                self->fmod_phase -= self->fmod_func_max - self->fmod_func_min;
            }
            amod_coeff = 1 + *self->amod_gain*(self->amod_func(self->amod_phase));
            self->amod_phase += amod_step;
            if(self->amod_phase >= self->amod_func_max)
            {
                self->amod_phase -= self->amod_func_max - self->amod_func_min;
            }
        }
        env_gain += env_slope;

        //harmonics
        for(j=0;j<*self->nharmonics;j++)
        {
            if(self->harmonics&(1<<j))//if cell is alive
            {

                buffer[i] += (env_gain*amod_coeff*self->harm_gain[j])*(self->base_func(self->phase[j]));
                self->phase[j] += pitchbend*fmod_coeff*self->step[j];
                if(self->phase[j] >= self->base_func_max)
                {
                    self->phase[j] -= self->base_func_max - self->base_func_min;
                }
            }
        }
        //now the root
        j = MAX_N_HARMONICS;
        buffer[i] += (env_gain*amod_coeff*self->harm_gain[j])*(self->base_func(self->phase[j]));
        self->phase[j] += pitchbend*fmod_coeff*self->step[j];
        if(self->phase[j] >= self->base_func_max)
        {
            self->phase[j] -= self->base_func_max - self->base_func_min;
        }
    }

    //recurse as necessary
    if(newcells)
    if(recurse)
    {
        playnote(self,nframes,chunk+start_frame,buffer);
    }
}

void end_note(NOTE *self)
{
    self->env_state = ENV_RELEASE;//set to release
}

void set_harmonics(NOTE *self, unsigned short harmonics)
{
    unsigned char i;
    self->harmonics = harmonics;
    for(i=0;i<MAX_N_HARMONICS;i++)//harmonics
    {
        if(!harmonics&(1<<k))//if cell is !alive
            self->phase[i] = 0;
    }
}
