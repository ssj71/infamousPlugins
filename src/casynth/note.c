//Spencer Jackson
//note.c

#include<note.h>
#include<math.h>


//private function prototypes
uint16_t torus_of_life(uint8_t rule, uint16_t cells, uint8_t ncells);


void init_note(NOTE *self, WAVESOURCE* waves, double sample_rate, uint8_t value, uint8_t* nharmonics, float* harmonic_length, float* amod_gain, float* fmod_gain)
{
    uint8_t i;
    double step;
    self->value = value;
    self->velocity = .8;
    self->pitchbend = 0;
    self->start_frame = 0;
    self->release_frame = 0;
    self->sus = 0;
    self->gain = 1;

    //currently hardcoding in function, may use optimised or selectable versions later
    self->base_wave = FUNC_SIN;
    self->base_func = waves->wave_func[FUNC_SIN];

    self->nharmonics = nharmonics;
    self->harm_length = harmonic_length;
    step = (waves->func_domain)*(440/sample_rate)*powf(2,(float)(value-69)/12);//leave this using more accurate pow since during init
    for(i=0; i<MAX_N_HARMONICS; i++)
    {
        self->phase[i] = 0;
        self->step[i] = (i+1)*step;
        init_hysteresis(&(self->hyst[i]));
    }
    self->phase[MAX_N_HARMONICS] = 0;//maxth harmonic is root
    self->step[MAX_N_HARMONICS] = step;
    init_hysteresis(&(self->hyst[MAX_N_HARMONICS]));

    self->env_gain = 0;
    self->note_dead = true;
    for(i=0; i<6; i++)
    {
        self->envelope[i] = 1;
    }

    self->fmod_gain = fmod_gain;//start this at 0
    self->fmod_phase = 0;
    self->fmod_step = 0;
    init_hysteresis(&(self->fhyst));

    self->amod_gain = amod_gain;//start this at 0
    self->amod_phase = 0;
    self->amod_step = 0;
    init_hysteresis(&(self->ahyst));
}

void start_note(NOTE*           self,
                WAVESOURCE* waves,
                uint8_t   velocity,
                uint32_t        start_frame,
                float           harmonic_gain[],
                uint16_t  harmonics,
                float           width,
                float           envelope[])
{
    uint8_t i;
    self->velocity = (float)velocity/127;//currently linear which is lame
    self->start_frame = start_frame;
    self->release_frame = 0;
    self->sus = 0;

    //harmonics
    self->nframes_since_harm_change = 0;
    self->cells = harmonics;
    for(i=0; i<MAX_N_HARMONICS; i++)
    {
        self->harm_gain[i] = self->velocity*harmonic_gain[i];
        self->harmonic[i] = harmonics&(1<<i);
        self->fwidth[i] = myPow2(width*white(waves,0,0));
    }
    //and the root
    i = MAX_N_HARMONICS;
    self->harm_gain[i] = self->velocity*harmonic_gain[i];
    //self->phase[i] = 0;

    //envelope
    //self->env_gain = 0;
    self->env_state = ENV_ATTACK;
    self->note_dead = false;
    for(i=0; i<6; i++)
        self->envelope[i] = envelope[i];

    //modulations
    self->amod_phase = 0;
    self->fmod_phase = 0;
}

void play_note(NOTE *self,
               WAVESOURCE* waves,
               uint32_t nframes,
               float buffer[],
               double pitchbend,
               float gain,
               uint16_t rule,
               uint8_t base_wave,
               uint8_t fmod_wave,
               double fmod_step,
               uint8_t amod_wave,
               double amod_step)

{
    uint16_t i;
    uint8_t j;
    float total_gain;
    float fmod_coeff = pitchbend;
    float amod_coeff = 1;
    uint32_t chunk, stop_frame;
    uint32_t start_frame = self->start_frame;
    uint32_t release_frame = self->release_frame;
    float env_slope;
    bool newcells = false;
    float env_end_gain;
    float gainstep = gain - self->gain;
    gainstep /= nframes>64?nframes:64;
    if (gainstep < 1e-15 && gainstep > -1e-15)//avoid denormals
    {
        gainstep = 0;
        self->gain = gain;
    }

    //go through all the chunks in this period
    for(chunk = nframes - start_frame; start_frame<nframes; chunk = nframes - start_frame)
    {
        //divide into chunk for release
        if(release_frame)
        {
            chunk = release_frame - start_frame;
        }

        //divide into chunks for cell lifetimes
        if(self->nframes_since_harm_change + chunk > *(self->harm_length))
        {
            if(*self->harm_length > self->nframes_since_harm_change)
            {
                chunk = *self->harm_length - self->nframes_since_harm_change;
            }
            else//we're overdue, change now (usually because parameter is changing)
            {
                chunk = 0;
            }
            newcells = true;
        }

        //divide into chunks for envelope
        env_slope = self->envelope[self->env_state];
        env_end_gain = self->env_gain + env_slope*chunk;
        if(self->env_state == ENV_ATTACK)
        {
            if(env_end_gain >= 1)
            {
                chunk = (uint32_t)((1-self->env_gain)/env_slope);
                self->env_state++;
                newcells = false;//cancel the new cells, we aren't going to get there in this chunk
            }

        }
        else if(self->env_state == ENV_DECAY)
        {
            if(env_end_gain <= self->envelope[ENV_BREAK])
            {
                chunk = (uint32_t)((self->envelope[ENV_BREAK] - self->env_gain)/env_slope);//removed
                self->env_state+=2;//skip B
                newcells = false;
            }

        }
        else if(self->env_state == ENV_SWELL)
        {
            if(!(env_slope > 0) != !(env_end_gain <= self->envelope[ENV_SUSTAIN]))
            {
                chunk = (uint32_t)((self->envelope[ENV_SUSTAIN] - self->env_gain)/env_slope);
                self->env_state++;
                newcells = false;
            }
        }
        else if(self->env_state == ENV_SUSTAIN)
        {
            env_slope = 0;
        }
        else if(self->env_state == ENV_RELEASE)
        {
            if (env_end_gain <= 0)
            {
                chunk = (uint32_t)(-self->env_gain/env_slope);//don't process past note death
                self->note_dead = true;
                newcells = false;
            }
        }

        //now handle the current chunk
        stop_frame = chunk+start_frame;
        for(i=start_frame; i<stop_frame; i++ )
        {
            //modulation
            fmod_coeff = pitchbend*myPow2( (*self->fmod_gain) * (waves->wave_func[fmod_wave](waves, &(self->fhyst), self->fmod_phase))/12 );
            self->fmod_phase += fmod_step;
            if(self->fmod_phase >= waves->func_max)
            {
                self->fmod_phase -= waves->func_domain;
            }
            amod_coeff = 1 + *self->amod_gain * (waves->wave_func[amod_wave](waves, &(self->ahyst), self->amod_phase));
            self->amod_phase += amod_step;
            if(self->amod_phase >= waves->func_max)
            {
                self->amod_phase -= waves->func_domain;
            }

            self->env_gain += env_slope;
            total_gain = self->gain*self->env_gain*amod_coeff;
            self->gain += gainstep;

            //harmonics
            for(j=0; j<*self->nharmonics; j++) //could unroll this but... it'd get ugly
            {
                if(self->harmonic[j])//if cell is alive
                {
                    buffer[i] += (total_gain*self->harm_gain[j]) * (waves->wave_func[base_wave](waves, &(self->hyst[j]), self->phase[j]));
                    self->phase[j] += self->fwidth[j]*fmod_coeff*self->step[j];
                    if(self->phase[j] >= waves->func_max)
                    {
                        self->phase[j] -= waves->func_domain;
                    }
                }
                else if(self->phase[j] != 0 )
                {
                    buffer[i] += (total_gain*self->harm_gain[j]) * (waves->wave_func[base_wave](waves, &(self->hyst[j]), self->phase[j]));
                    self->phase[j] += self->fwidth[j]*fmod_coeff*self->step[j];
                    if(self->phase[j] >= waves->func_max)
                    {
                        self->phase[j] = 0;
                    }
                }
            }
            //now the root
            j = MAX_N_HARMONICS;
            buffer[i] += (total_gain*self->harm_gain[j]) * (waves->wave_func[base_wave](waves, &(self->hyst[j]), self->phase[j]));
            self->phase[j] += fmod_coeff*self->step[j];
            if(self->phase[j] >= waves->func_max)
            {
                self->phase[j] -= waves->func_domain;
            }
        }
        self->nframes_since_harm_change += chunk;
        start_frame = stop_frame;
        if( (start_frame == release_frame) && (release_frame != 0))
        {
            self->env_state = ENV_RELEASE;
            release_frame = self->release_frame = 0;
        }
        if( self->note_dead )
        {
            for(j=0; j<=*self->nharmonics; j++)
            {
                self->phase[j] = 0;
            }
            self->env_gain = 0;
            return;
        }

        if(newcells)
        {
            //calculate next state
            self->cells = torus_of_life(rule,self->cells,MAX_N_HARMONICS);
            for(j=0; j<MAX_N_HARMONICS; j++) //harmonics
            {
                self->harmonic[j] = self->cells&(1<<j);
            }
            self->nframes_since_harm_change = 0;
            newcells = false;
        }
    }
    self->start_frame = 0;
}

void end_note(NOTE *self, uint32_t release_frame)
{
    if(release_frame == 0)
        release_frame = 1;
    self->release_frame = release_frame;
}


uint16_t torus_of_life(uint8_t rule, uint16_t cells, uint8_t ncells)
{
    uint16_t temp;
    uint8_t index;
    ncells--;
    temp=0;
    for(index=0; index<=ncells; index++)
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
