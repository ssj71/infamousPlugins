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

NOTE *init_note(NOTE *self, unsigned char value, unsigned char velocity, unsigned char nharmonics, float envelope[])
{
    unsigned char i;
    self->value = value;
    self->velocity = velocity;
    self->nharmonics = nharmonics;
    self->nharm_chng = 0;
    for(i=0;i<nharmonics;i++)
    {
        self->self->harmonics[i] = harmonics[i];
        self->phase[i] = 0;
        if(self->harmonic_mode == HARMONIC_MODE_SIN)
            self->harm_gain[i] = 1/(nharmonics+1);
        else if(self->harmonic_mode == HARMONIC_MODE_SAW)
            self->harm_gain[i] = .29/(i+2);
        else if(self->harmonic_mode == HARMONIC_MODE_SQR)
            self->harm_gain[i] = (i%2==0)*.29/(i+2);
        else if(self->harmonic_mode == HARMONIC_MODE_TRI)
            self->harm_gain[i] = .29/(i+1);

    }
    phase[nharmonics] = 0;//0th harmonic is root

    //currently hardcoding in function, may use optimised or selectable versions later
    self->base_func = &sin;
    self->base_func_min = -PI;
    self->base_func_max = PI;

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

void set_envelope(NOTE *self, float adsr)
{
    self->envelope[nharm_chng] = slope;
    self->l_env[nharmchng++] = frame_no;
}

void set_harmonics(NOTE *self, unsigned short harmonics)
{
    unsigned char i;
    self->harmonics = harmonics;
    for(i=0;i<self->nharmonics;i++)//harmonics
    {
        if(!harmonics&(1<<k))//if cell is !alive
            self->phase[i] = 0;
    }
}


void end_note(NOTE *self)
{
    self->env_state = ENV_RELEASE;//set to release
}


void playnote(NOTE *self, uint32_t nframes, uint32_t start_frame, float buffer[])
{
    unsigned char i,j,k;
    uint32_t frame = start_frame;
    //uint32_t chunk[MAX_N_CELL_CHANGES + 3];
    unsigned short harmonics = self->harmonics[0];
    uint32_t *harm_chng_frame = self->harm_chng_frame;
    harm_chng_frame[self->nharm_chng++] = nframes;

    float fmod_g = 0;
    float fmod_coeff = 1;
    float amod_g = 0;
    float amod_coeff = 1;

    //divide into chunks per envelpe region
    uint32_t chunk = nframes - start_frame;
    float env_slope = envelope[env_state];
    float env_end_gain = env_gain + env_slope*chunk;
    bool recurse = FALSE;
    if (self->env_state<ENV_SUSTAIN)
    {
        if(self->env_state != ENV_SWELL)
        {
            if(env_end_gain > 1.0)
            {
                //do no. frames till Attack complete
                self->env_state++;
                recurse = TRUE;
            }
            else if(env_end_gain <= envelope[ENV_BREAK])
            {
                //do no. frames till Decay complete

                self->env_state+=2;//skip B
                recurse = TRUE;
            }
        }
        else if(env_end_gain >= envelope[ENV_SUSTAIN])
        {
            //do no. frames till Swell complete

            self->env_state++;
            recurse = TRUE;
        }
    }else if(self->env_state > ENV_SUSTAIN)//release
    {
        if (env_end_gain <= 0)
        {
            note_dead = TRUE;
            chunk = floor(env_gain/env_slope);//don't process past note death
        }
    }
    else//in sustain
    {
        fmod_g = self->fmod_gain;
        amod_g = self->amod_gain;
        env_slopef = 0;
    }

    for(i=0;i<self->nharm_chng;i++) //cell generations
    {
        // I think I should just handle the cell lifetimes outside of the note and play chunks.
        for(j=frame;j<harm_chng_frame[i];j++ )
        {
            fmod_coeff = 1 + fmod_g*(self->fmod_func(self->fmod_phase);
            self->fmod_phase += self->fmod_step;
            amod_coeff = 1 + amod_g*(self->fmod_func(self->amod_phase));
            self->amod_phase += self->amod_step;
            for(k=0;k<self->nharmonics;k++)//harmonics
            {
                if(harmonics&(1<<k))//if cell is alive
                {

                    env_gain += env_slope;
                    buffer[k] += (env_gain*amod_coeff)*(self->base_func(self->phase[k]));
                    self->phase[k] += fmod_coeff*self->step[k];

                }
            }
            //now the root
        }

    }
}
