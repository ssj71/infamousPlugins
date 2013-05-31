//Spencer Jackson
//note.c

#include<note.h>
#include<math.h>


NOTE *init_note(NOTE *self, unsigned char value, unsigned char velocity, unsigned char nharmonics)
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
    }
    phase[nharmonics] = 0;//0th harmonic is root

    //currently hardcoding in function, may use optimised or selectable versions later
    self->base_func = &sin;
    self->base_func_min = -PI;
    self->base_func_max = PI;

    self->env_gain = 0;
    self->nenv_chng = 0;
}

void set_envelope(NOTE *self, float slope, uint32_t frame_no)
{
    self->envelope[nharm_chng] = slope;
    self->l_env[nharmchng++] = frame_no;
}

void set_harmonics(NOTE *self, unsigned short harmonics, uint32_t frame_no)
{
    self->harmonics[nharm_chng] = harmonics;
    self->harm_chng_frame[nharm_chng++] = frame_no;
}
