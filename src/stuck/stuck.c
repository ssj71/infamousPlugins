//Spencer Jackson
//stuck.c
#include<lv2.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"rms_calc.h"
#include"stuck.h"

//#define CV_PORTS

enum states
{
    INACTIVE = 0,
    LOADING,
    MATCHING,
    LOADING_XFADE,
    XFADE_ONLY,
    PLAYING,
    RELEASING,
    QUICK_RELEASING
};

typedef struct _STUCK
{
    uint16_t indx;//current write point in buffer
    uint16_t indx2;//working/read point in buffer
    uint16_t bufsize;//size of buffer
    float wavesize;//size of waveform
    uint16_t acorr_size;//size of autocorrelation
    uint16_t xfade_size;
    uint16_t wave_min;//int16_test allowed wavesize
    uint16_t wave_max;//int32_test allowed wavesize
    uint8_t state;
    double sample_freq;

    float *buf;
    float gain;
    float env;//envelope gain to normalize compression to
    float thresh;
    float savescore;
    float prevscore[2];
    float minscore[5];
    uint8_t save; //flag to show the next 2 scores should be saved

    RMS_CALC rms_calc;

    float *input_p;
    float *output_p;
    float *trigger_p;
    float *stick_it_p;
    float *drone_gain_p;
    float *release_p;
    float *dbg_p;
} STUCK;

float findminx(float arr[])
{
	//return subsample index of minima
	float m2 = arr[3]-arr[1];
	float a,b,c;
	if(m2>0)
	{
		//minima is before sample
		a = 1.5*(-arr[0] + 3*arr[1] - 3*arr[2] + arr[3]);
		b = 2*arr[0] - 5*arr[1] + 4*arr[2] - arr[3];
		c = .5*(-arr[0] + arr[2]);

        if(!a) return 1 + c/b;
		return 1-(-b+sqrt(b*b-4*a*c))/(2*a);//its possible that this is wrong but I think b-.. will be out of domain t E[0,1]
	}
	else if(m2<0)
	{
		//minima is after sample
		a = 1.5*(-arr[1] + 3*arr[2] - 3*arr[3] + arr[4]);
		b = 2*arr[1] - 5*arr[2] + 4*arr[3] - arr[4];
		c = .5*(-arr[1] + arr[3]);

        if(!a) return -c/b;
		return (-b+sqrt(b*b-4*a*c))/(2*a);//its possible that this is wrong but I think b-.. will be out of domain t E[0,1]
	}
	else return 0;
}

void run_stuck(LV2_Handle handle, uint32_t nframes)
{
    STUCK* plug = (STUCK*)handle;
    uint32_t i,j,k,t,chunk=0;
    double slope = 0;
    double interp;

    memcpy(plug->output_p,plug->input_p,nframes*sizeof(float));
    //for(i=0;i<nframes;i++) plug->output_p[i] = 0;

    interp = nframes>64?nframes:64;

    if(plug->state == INACTIVE)
    {
        //decide if triggered
#ifdef CV_PORTS
        if(*plug->stick_it_p >= 1 || plug->trigger_p[nframes-1] >= 1)
#else
        if(*plug->stick_it_p >= 1)
#endif
        {
            plug->state = LOADING;
            plug->env = plug->rms_calc.rms;
        }
        else
        {
            rms_block_fill(&plug->rms_calc, plug->input_p,nframes);
            return;
        }
    }
    else if(plug->state < LOADING_XFADE)
    {
        //decide if need to abort
#ifdef CV_PORTS
        if(*plug->stick_it_p < 1 && plug->trigger_p[nframes-1] < 1)
#else
        if(*plug->stick_it_p < 1)
#endif
        {
            //reinit
            plug->indx = 0;
            plug->indx2 = plug->wave_min;
            plug->state = INACTIVE;
            plug->gain = 0;
            plug->wavesize = plug->wave_max;
            plug->minscore[2] = 1;
            //warning, could minima be in first 2 such that prevscore is invalid?
            rms_block_fill(&plug->rms_calc, plug->input_p,nframes);
            return;
        }
    }
    else if(plug->state < RELEASING)
    {
        //decide if released
#ifdef CV_PORTS
        if(*plug->stick_it_p < 1 && plug->trigger_p[nframes-1] < 1)
#else
        if(*plug->stick_it_p < 1)
#endif
        {
            plug->state = RELEASING;
        }
    }
    else if(plug->state == RELEASING)
    {
        //decide if new trigger has been sent before release is complete
#ifdef CV_PORTS
        if(*plug->stick_it_p >= 1 || plug->trigger_p[nframes-1] >= 1)
#else
        if(*plug->stick_it_p >= 1)
#endif
        {
            plug->state = QUICK_RELEASING;
        }
        else
        {
            rms_block_fill(&plug->rms_calc, plug->input_p,nframes);
        }
    }

    for(i=0; i<nframes;)
    {
        chunk = nframes - i;
        if(plug->state == LOADING)//load enough frames to start calculating the autocorrelation
        {
            //decide if reaching minimum length in this period
            if(plug->indx+chunk >= plug->wave_min+plug->acorr_size)
            {
                chunk = plug->wave_min + plug->acorr_size - plug->indx;
                plug->state = MATCHING;
            }
            //load buffer with compressed signal
            for(j=0; j<chunk; j++)
            {
                plug->buf[plug->indx++] = plug->input_p[i]*plug->env/rms_shift(&plug->rms_calc,plug->input_p[i]);
                i++;
            }
            if(plug->indx >= plug->wave_min+plug->acorr_size)
            {
				float tmp,score;
                for(k=plug->indx2; k<plug->indx2+plug->acorr_size && score<=plug->minscore[2]; k++)
                {
                    tmp = plug->buf[k] - plug->buf[t++];//jsyk this isn't the strict definition of an autocorrelation, a variation on the principle
                    score += tmp*tmp;
                }
                plug->prevscore[0] = score;
                plug->indx2++;

                for(k=plug->indx2; k<plug->indx2+plug->acorr_size && score<=plug->minscore[2]; k++)
                {
                    tmp = plug->buf[k] - plug->buf[t++];//jsyk this isn't the strict definition of an autocorrelation, a variation on the principle
                    score += tmp*tmp;
                }
                plug->prevscore[1] = score;
                plug->indx2++;
            }
        }
        else if(plug->state == MATCHING)//find autocorrelation
        {
            if(plug->indx2+chunk >= plug->wave_max)
            {
                chunk = plug->wave_max - plug->indx2;
                plug->state = PLAYING;
            }
            // calculate autocorrelation of sample in buffer, save the minimum
            float tmp,score;
            for(j=0; j<chunk; j++)
            {
                score = 0;
                t=0;

                for(k=plug->indx2; k<plug->indx2+plug->acorr_size && score<=plug->minscore[2]; k++)
                {
                    tmp = plug->buf[k] - plug->buf[t++];//jsyk this isn't the strict definition of an autocorrelation, a variation on the principle
                    score += tmp*tmp;
                }
                plug->indx2++;

                plug->buf[plug->indx++] = plug->input_p[i]*plug->env/rms_shift(&plug->rms_calc,plug->input_p[i]);
                i++;

                //save place if score is lower than last minimum
                if(score<=plug->minscore[2])
                {
                    plug->wavesize = plug->indx2 -1;//subtract 1 because we incremented already
                    plug->minscore[2] = score;
                    plug->minscore[1] = plug->prevscore[1];
                    plug->minscore[0] = plug->prevscore[0];
                    plug->save = 2;
                }
                else if(plug->save == 2)
                {
                	plug->minscore[3] = score;
                	plug->save--;
                }
                else if(plug->save == 1)
                	plug->minscore[4] = score;
                else plug->save = 0;
                //rotate prevscore
                plug->prevscore[0] = plug->prevscore[1];
                plug->prevscore[1] = score;
            }
            if(plug->indx2>=plug->wave_max)
            {
                plug->indx2 = 0;//reset indx2
                //find subsample peak
                plug->wavesize += findminx(plug->minscore);
				//TODO: must calculate subsample offset so that the crossfade theoretically doesn't change the samples at all
                //its possible that with the more accurate wavesize only 1 wave will be required
                //so all xfading can be done here then skip straight to playing
                //it would be nice too if this played in phase
                //xfade in beginning of sample
                for(k=0; k<plug->xfade_size; k++)
                    plug->buf[k] *= k/plug->xfade_size;
            }
        }
        //CURRENTLY WE ARE NOT USING THIS STEP. WE'LL SEE IF IT WORKS WITHOUT LAYERING 2 FULL CYCLES
        else if(plug->state == LOADING_XFADE)//xfade end of buffer with start (loop it) over an entire wave and fade in drone
        {
            slope = (*plug->drone_gain_p-plug->gain)/interp;
            //decide if xfade ends in this period
            if(plug->indx2+chunk >= plug->wavesize)
                //if(plug->indx2+chunk >= 10)
            {
                chunk = plug->wavesize - plug->indx2;
                //chunk = 10 - plug->indx2;
                plug->state = PLAYING;
            }
            //decide if going to overflow
            if(plug->indx+chunk >= plug->bufsize)
            {
                chunk = plug->bufsize - plug->indx;
                plug->state = XFADE_ONLY;
            }
            //load buffer with xfade
            for(j=0; j<chunk; j++)
            {
                plug->buf[plug->indx2] = .5*plug->buf[plug->indx2+plug->wavesize] + .5*plug->buf[plug->indx2];
                //still loading end of buffer
                plug->buf[plug->indx++] = plug->input_p[i]*plug->env/rms_shift(&plug->rms_calc,plug->input_p[i]);
                plug->output_p[i++] += plug->gain*plug->buf[plug->indx2++];
                plug->gain += slope;
            }
            //xfade out end
            if(plug->indx2>=plug->wavesize)
            {
                for(k=0; k<plug->xfade_size; k++)
                    plug->buf[k] += .5*(1-k/plug->xfade_size)*plug->buf[plug->indx2];
            }
        }
        else if(plug->state == XFADE_ONLY)//xfade after enough samples are in buffer
        {
            slope = (*plug->drone_gain_p-plug->gain)/interp;
            //decide if xfade ends in this period
            if(plug->indx2+chunk >= plug->wavesize)
            {
                chunk = plug->wavesize - plug->indx2;
                plug->state = PLAYING;
            }
            //xfade buffer
            for(j=0; j<chunk; j++)
            {
                plug->buf[plug->indx2] = .5*plug->buf[plug->indx2+plug->wavesize] + .5*plug->buf[plug->indx2];
                plug->output_p[i++] += plug->gain*plug->buf[plug->indx2++];
                plug->gain += slope;
            }
            //xfade out end
            if(plug->indx2>=plug->wavesize)
            {
				//TODO: must calculate subsample offset so that the crossfade theoretically doesn't change the samples at all
                for(k=0; k<plug->xfade_size; k++)
                    plug->buf[k] += .5*(1-k/plug->xfade_size)*plug->buf[plug->indx2];
            }
            plug->indx2 = plug->indx2<plug->wavesize?plug->indx2:0;
        }
        else if(plug->state == PLAYING)//just loop buffer and track gain changes
        {
            slope = (*plug->drone_gain_p-plug->gain)/interp;
            for(j=0; j<chunk; j++)
            {
                plug->output_p[i++] += plug->gain*plug->buf[plug->indx2++];
                plug->gain += slope;
                plug->indx2 = plug->indx2<plug->wavesize?plug->indx2:0;
            }
        }
        else if(plug->state == RELEASING)
        {
            slope = -*plug->drone_gain_p/(*plug->release_p*plug->sample_freq);
            //decide if released in this period
            if(plug->gain + chunk*slope < slope)
            {
                chunk = -plug->gain/slope;
                plug->state = INACTIVE;
            }
            for(j=0; j<chunk; j++)
            {
                plug->output_p[i++] += plug->gain*plug->buf[plug->indx2++];
                plug->gain += slope;
                plug->indx2 = plug->indx2<plug->wavesize?plug->indx2:0;
            }
            if(plug->gain <= -slope)
            {
                plug->indx = 0;
                plug->indx2 = plug->wave_min;
                plug->state = INACTIVE;
                plug->gain = 0;
                plug->wavesize = plug->wave_max;
                plug->minscore[2] = 1;
                return;
            }
        }
        else if(plug->state == QUICK_RELEASING)
        {
            slope = -*plug->drone_gain_p/(double)plug->wave_min;
            //decide if released in this period
            if(plug->gain + chunk*slope < slope)
            {
                chunk = -plug->gain/slope;
                plug->state = LOADING;
            }
            for(j=0; j<chunk; j++)
            {
                plug->output_p[i++] += plug->gain*plug->buf[plug->indx2++];
                plug->gain += slope;
                plug->indx2 = plug->indx2<plug->wavesize?plug->indx2:0;
            }
            rms_block_fill(&plug->rms_calc, plug->input_p,chunk);
            if(plug->gain <= -slope)
            {
                plug->indx = 0;
                plug->indx2 = plug->wave_min;
                plug->state = LOADING;
                plug->wavesize = plug->wave_max;
                plug->score = 1;
                plug->env = plug->rms_calc.rms;
            }
        }
    }
    return;
}

LV2_Handle init_stuck(const LV2_Descriptor *descriptor,double sample_freq, const char *bundle_path,const LV2_Feature * const* host_features)
{
    STUCK* plug = malloc(sizeof(STUCK));

    uint16_t tmp;
    plug->sample_freq = sample_freq;
    tmp = 0x8000;//15 bits
    if(sample_freq<100000)//88.1 or 96.1kHz
        tmp = tmp>>1;//14 bits
    if(sample_freq<50000)//44.1 or 48kHz
        tmp = tmp>>1;//13 bits //8192
    plug->buf = (float*)malloc(tmp*sizeof(float));
    plug->bufsize = tmp;
    plug->acorr_size = tmp>>3;//1024
    plug->xfade_size = tmp>>7;//64
    plug->wave_max = (tmp - plug->xfade_size)>>1;//4064, or half the buffer + a crossfade
    plug->wave_min = tmp>>6;//128
    plug->wavesize = plug->wave_max;
    plug->indx = 0;
    plug->indx2 = plug->wave_min;
    plug->state = INACTIVE;
    plug->gain = 0;
    plug->minscore[2] = 1;
    plug->env = 0;

    rms_init(&plug->rms_calc,tmp>>3);

    return plug;
}

void connect_stuck_ports(LV2_Handle handle, uint32_t port, void *data)
{
    STUCK* plug = (STUCK*)handle;
    switch(port)
    {
    case IN:
        plug->input_p = (float*)data;
        break;
    case OUT:
        plug->output_p = (float*)data;
        break;
    case TRIGGER:
        plug->trigger_p = (float*)data;
        break;
    case STICKIT:
        plug->stick_it_p = (float*)data;
        break;
    case DRONEGAIN:
        plug->drone_gain_p = (float*)data;
        break;
    case RELEASE:
        plug->release_p = (float*)data;
        break;
    case DBG:
        plug->dbg_p = (float*)data;
        break;
    default:
        puts("UNKNOWN PORT YO!!");
    }
}

void cleanup_stuck(LV2_Handle handle)
{
    STUCK* plug = (STUCK*)handle;
    rms_deinit(&plug->rms_calc);
    free(plug->buf);
    free(plug);
}

static const LV2_Descriptor stuck_descriptor=
{
    STUCK_URI,
    init_stuck,
    connect_stuck_ports,
    0,//activate
    run_stuck,
    0,//deactivate
    cleanup_stuck,
    0//extension
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index)
    {
    case 0:
        return &stuck_descriptor;
    default:
        return 0;
    }
}
