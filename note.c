//Spencer Jackson
//note.c

#include<note.h>
#include<math.h>

//private function prototypes
void playnote(NOTE *self, uint32_t nframes, float buffer[] );

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
    self->nenv_chng = 0;

    self->play = &playnote;
}

void set_envelope(NOTE *self, float adsr)
{
    self->envelope[nharm_chng] = slope;
    self->l_env[nharmchng++] = frame_no;
}

void set_harmonics(NOTE *self, unsigned short harmonics, uint32_t frame_no)
{
    self->harmonics[nharm_chng] = harmonics;
    self->harm_chng_frame[nharm_chng++] = frame_no;
}


void playnote(NOTE *self, uint32_t nframes, float buffer[])
{
    unsigned char i,j,k;
    uint32_t frame = 0;
    uint32_t chunk[MAX_N_CELL_CHANGES + 3];
    unsigned short harmonics = self->harmonics[0];
    uint32_t *harm_chng_frame = self->harm_chng_frame;
    harm_chng_frame[self->nharm_chng++] = nframes;


    for(i=0;i<self->nharm_chng;i++) //cell generations
    {

        for(j=0;j<nharmonics;j++)//harmonics
        {
            if(harmonics&(1<<j))//if cell is alive
            {
                for(k=frame;k<harm_chng_frame[i];k++ )
                    buffer[k] += self->base_func(phase);
            }
        }
        //now the root

    }
}
