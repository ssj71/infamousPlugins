//Spencer Jackson
//note.c

#include<note.h>
#include<math.h>


//private function prototypes
unsigned short torus_of_life(unsigned char rule, unsigned short cells, unsigned char ncells);



void init_note(NOTE *self, double sample_rate, unsigned char value, float* nharmonics, float* harmonic_length, float* amod_gain, float* fmod_gain)
{
    unsigned char i;
    double step;
    self->value = value;
    self->velocity = .8;
    self->pitchbend = 0;
    self->start_frame = 0;
    self->release_frame = 0;
    self->sus = 0;

    //currently hardcoding in function, may use optimised or selectable versions later
    self->base_wave = FUNC_SIN;
    self->base_func = &sin;
    self->base_func_min = -PI;
    self->base_func_max = PI;

    self->nharmonics = nharmonics;
    self->harm_length = harmonic_length;
    step = (self->base_func_max - self->base_func_min)*440/sample_rate*pow(2,(value-69)/12);
    for(i=0;i<MAX_N_HARMONICS;i++)
    {
        self->phase[i] = 0;
        self->step[i] = (i+1)*step;

    }
    self->phase[MAX_N_HARMONICS] = 0;//maxth harmonic is root

    self->env_gain = 0;
    self->note_dead = true;
    for(i=0;i<6;i++)
    {
        self->envelope[i] = 1;
    }

    self->fmod_func = &sin;
    self->fmod_gain = fmod_gain;//start this at 0
    self->fmod_phase = 0;
    self->fmod_step = 0;

    self->amod_func = &sin;
    self->amod_gain = amod_gain;//start this at 0
    self->amod_phase = 0;
    self->amod_step = 0;
}

void start_note(NOTE*           self,
                unsigned char   velocity,
                uint32_t        start_frame,
                float           harmonic_gain[],
                unsigned short  harmonics,
                float           envelope[],
                unsigned char   base_wave,
                unsigned char   amod_wave,
                unsigned char   fmod_wave)
{
    unsigned char i;
    self->velocity = (float)velocity/127;//currently linear which is lame
    self->start_frame = start_frame;
    self->release_frame = 0;
    self->sus = 0;

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
              float buffer[],
              double pitchbend,
              unsigned short rule,
              double amod_step,
              double fmod_step)
{
    unsigned char i,j;
    float fmod_coeff = 1;
    float amod_coeff = 1;
    uint32_t chunk;
    uint32_t start_frame = self->start_frame;
    uint32_t release_frame = self->release_frame;
    float env_slope;
    bool newcells = false;
    float env_end_gain;

    //need to make sure chunks aren't overlapping!
    //go through all the chunks in this period
    for(chunk = nframes - start_frame; start_frame<nframes; chunk = nframes - start_frame)
    {
        //divide into chunk for release
        if(release_frame)
        {
            chunk = release_frame - start_frame;
        }

        //divide into chunks for cell lifetimes
        if(self->nframes_since_harm_change + chunk > *self->harm_length)
        {
            chunk = *self->harm_length - self->nframes_since_harm_change;
            newcells = true;
        }

        //divide into chunks for envelope
        env_slope = self->envelope[self->env_state];
        env_end_gain = self->env_gain + env_slope*chunk;
        if (self->env_state<ENV_SUSTAIN)
        {
            if(self->env_state != ENV_SWELL)
            {
                if(env_end_gain > 1.0)
                {
                    //do no. frames till Attack complete
                    chunk = floor((1-self->env_gain)/env_slope);
                    self->env_state++;
                    newcells = false;//cancel the new cells, we aren't going to get there in this chunk
                }
                else if(env_end_gain <= self->envelope[ENV_BREAK])
                {
                    //do no. frames till Decay complete
                    chunk = floor((self->envelope[ENV_BREAK] - self->env_gain)/env_slope);
                    self->env_state+=2;//skip B
                    newcells = false;
                }
            }
            else if(env_end_gain >= self->envelope[ENV_SUSTAIN])
            {
                //do no. frames till Swell complete
                chunk = floor((self->envelope[ENV_SUSTAIN] - self->env_gain)/env_slope);
                self->env_state++;
                newcells = false;
            }
        }else if(self->env_state > ENV_SUSTAIN)//release
        {
            if (env_end_gain <= 0)
            {
                chunk = floor(self->env_gain/env_slope);//don't process past note death
                self->note_dead = true;
                newcells = false;
            }
        }
        else//in sustain
        {
            env_slope = 0;
        }

        //now handle the current chunk
        for(i=start_frame;i<chunk+start_frame;i++ )
        {
            //modulation
            if(self->env_state == ENV_SUSTAIN)
            {
                fmod_coeff = pow(2,(*self->fmod_gain)*(self->fmod_func(self->fmod_phase)));
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
            self->env_gain += env_slope;

            //harmonics
            for(j=0;j<*self->nharmonics;j++)
            {
                if(self->harmonics&(1<<j))//if cell is alive
                {

                    buffer[i] += (self->env_gain*amod_coeff*self->harm_gain[j])*(self->base_func(self->phase[j]));
                    self->phase[j] += pitchbend*fmod_coeff*self->step[j];
                    if(self->phase[j] >= self->base_func_max)
                    {
                        self->phase[j] -= self->base_func_max - self->base_func_min;
                    }
                }
            }
            //now the root
            j = MAX_N_HARMONICS;
            buffer[i] += (self->env_gain*amod_coeff*self->harm_gain[j])*(self->base_func(self->phase[j]));
            self->phase[j] += pitchbend*fmod_coeff*self->step[j];
            if(self->phase[j] >= self->base_func_max)
            {
                self->phase[j] -= self->base_func_max - self->base_func_min;
            }
        }
        self->nframes_since_harm_change += chunk;

        if(newcells)
        {
            //calculate next state
            self->harmonics = torus_of_life(rule,self->harmonics,MAX_N_HARMONICS);
            for(i=0;i<MAX_N_HARMONICS;i++)//harmonics
            {
                if( !(self->harmonics&(1<<i)) )//if cell is !alive
                    self->phase[i] = 0;
            }
            self->nframes_since_harm_change = 0;
        }
        start_frame += chunk;
        if( start_frame == release_frame )
        {
            self->env_state = ENV_RELEASE;
            release_frame = 0;
        }
    }
}

void end_note(NOTE *self, uint32_t release_frame)
{
    self->release_frame = release_frame;
}


unsigned short torus_of_life(unsigned char rule, unsigned short cells, unsigned char ncells)
{
    unsigned short temp;
    unsigned char index;
    ncells--;
    temp=0;
    for(index=0;index<=ncells;index++)
    {
        //the idea is to shift the rule mask (w/rollover) according to the 3
        //bits in the neighborhood at $index, mask that bit in the rule to
        //then determine the next cell state and OR it into a temp value
        //       |cell state-----------------------------------------------|
        //               | rule mask ---------------------------------|
        //                   |neighborhood ---------------------------|
        temp |= ((rule & 1<<((cells>>index|cells<<(ncells-index+1) )&7) )>0)<<index;
    }
    cells=temp<<1|temp>>ncells;
    return cells;
}
