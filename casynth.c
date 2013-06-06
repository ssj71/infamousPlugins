//Spencer Jackson
//casynth.c
#include<casynth.h>
#include<constants.h>

LV2_Handle init_casynth(const LV2_Descriptor *descriptor,double s_rate, const char *path,const LV2_Feature * const* features);
{
    self->nactive = 0;

    if(self->harmonic_mode == HARMONIC_MODE_SINC)
        self->harm_gain[i] = self->velocity/(MAX_N_HARMONICS +1);//(nharmonics+1);
    else if(self->harmonic_mode == HARMONIC_MODE_SAW)
        self->harm_gain[i] = self->velocity*.29/(i+2);//.29 makes it so gain=1 if all harmonics play
    else if(self->harmonic_mode == HARMONIC_MODE_SQR)
        self->harm_gain[i] = self->velocity*(i%2!=0)*.48/(i+2);//odd harmonics
    else if(self->harmonic_mode == HARMONIC_MODE_TRI)
        self->harm_gain[i] = self->velocity*.83/((i+2)*(i+2));
}
