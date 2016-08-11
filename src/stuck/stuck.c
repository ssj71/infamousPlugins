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
//#define TEST
#define NO_COMP
#define LINEAR_FADE
#define NO_FADE
#define LAYER
//#define SHOW_BUF
#define AUTOCORR

#ifdef AUTOCORR
#define START_SCORE 0
#else //least squared error
#define START_SCORE 200
#endif

enum states
{
    INACTIVE = 0,
    LOADING,
    MATCHING,
    LOADING_XFADE,
    XFADE_ONLY,
    PLAYING,
    RELEASING,
    QUICK_RELEASING,
	DEBUGGING,
};

typedef struct _STUCK
{
    uint16_t indx;//current write point in buffer
    uint16_t indx2;//working/read point in buffer
    uint16_t bufsize;//size of buffer
    uint16_t wavesize;//size of waveform
    uint16_t acorr_size;//size of autocorrelation
    uint16_t xfade_size;
    uint16_t wave_min;//int16_test allowed wavesize
    uint16_t wave_max;//int32_test allowed wavesize
    uint8_t state;
    uint8_t dbg;//used for whatever, delete it
    double sample_freq;

    float *buf;
    float gain;
    float env;//envelope gain to normalize compression to
    float score;

    RMS_CALC rms_calc;

    float *input_p;
    float *output_p;
    float *trigger_p;
    float *stick_it_p;
    float *drone_gain_p;
    float *release_p;
    float *dbg_p;
    float *output2_p;

    float *xf_func;
} STUCK;

void run_stuck(LV2_Handle handle, uint32_t nframes)
{
    STUCK* plug = (STUCK*)handle;
    uint32_t i,j,k,t,chunk=0;
    double slope = 0;
    double interp;

#ifdef TEST
    *plug->dbg_p = plug->wavesize;
    if(plug->input_p != plug->output_p)
		for(i=0;i<nframes;i++)
			plug->output_p[i] = 0;
    if(plug->input_p != plug->output2_p)
		for(i=0;i<nframes;i++)
			plug->output2_p[i] = 0;
#else
    memcpy(plug->output_p,plug->input_p,nframes*sizeof(float));
#endif

    interp = nframes>64?nframes:64;

    //Evaluate port values and see if it requires any state changes
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
            plug->score = START_SCORE;
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
#ifdef TEST
    else if(plug->state == DEBUGGING)//just loop buffer and track gain changes
    {
        if(*plug->stick_it_p < 1)
        {
            plug->indx = 0;
            plug->indx2 = plug->wave_min;
            plug->state = INACTIVE;
            plug->gain = 0;
            plug->wavesize = plug->wave_max;
            plug->score = START_SCORE;
            rms_block_fill(&plug->rms_calc, plug->input_p,nframes);
            return;
        }
    }
#endif

    //now run the state machine
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
#ifdef NO_COMP
                plug->buf[plug->indx++] = plug->input_p[i];//no compression
#else
                plug->buf[plug->indx++] = plug->input_p[i]*plug->env/rms_shift(&plug->rms_calc,plug->input_p[i]);
#endif
#ifdef TEST
				plug->output_p[i] = plug->output2_p[i] = 0;
#endif
                i++;
            }
        }
        else if(plug->state == MATCHING)//find autocorrelation
        {
            if(plug->indx2+chunk >= plug->wave_max)
            {
                chunk = plug->wave_max - plug->indx2;
                plug->state = LOADING_XFADE;
#ifdef NO_FADE
                plug->state = PLAYING;
#endif
#ifdef TEST
                plug->state = DEBUGGING;
#endif
            }
            // calculate autocorrelation of sample in buffer, save the minimum
            float tmp,score;
            for(j=0; j<chunk; j++)
            {
#ifdef NO_COMP
                plug->buf[plug->indx++] = plug->input_p[i];//no compression
#else
                plug->buf[plug->indx++] = plug->input_p[i]*plug->env/rms_shift(&plug->rms_calc,plug->input_p[i]);
#endif
#ifdef TEST
				plug->output_p[i] = plug->output2_p[i] = 0;
#endif
                i++;

                score = 0;
                t=0;
                for(k=plug->indx2; k<plug->indx2+plug->acorr_size && score<=plug->score; k++)
                {
#ifdef AUTOCORR
                    score += plug->buf[k]*plug->buf[t++];
#else
                    tmp = plug->buf[k] - plug->buf[t++];//jsyk this isn't the strict definition of an autocorrelation, a variation on the principle
                    score += tmp*tmp;
#endif
                }
                plug->indx2++;

#ifdef AUTOCORR
                //save place if score is higher than last highest
                if(score>=plug->score)
#else
                //save place if score is lower than last minimum
                if(score<=plug->score)
#endif
                {
                    plug->wavesize = plug->indx2 -1;//subtract 1 because we incremented already
                    plug->score = score;
                }
            }
            if(plug->indx2>=plug->wave_max)
            {
                plug->indx2 = 0;//reset indx2
#ifndef NO_FADE
                //xfade in beginning of sample, these will be halved in the next state
                for(k=0; k<plug->xfade_size; k++)
#ifdef LINEAR_FADE
                    plug->buf[k] *= k/plug->xfade_size;
#else
                    plug->buf[k] *= plug->xf_func[k];
#endif
#endif
            }
        }
#ifndef TEST
        else if(plug->state == LOADING_XFADE)//xfade end of buffer with start (loop it) over an entire wave and fade in drone
        {
            slope = (*plug->drone_gain_p-plug->gain)/interp;
            //decide if xfade ends in this period
            if(plug->indx2+chunk >= plug->wavesize)
            {
            	//this means it has already played through the loop once and finished the xfade (layering really)
                chunk = plug->wavesize - plug->indx2;
                plug->state = PLAYING;
            }
            //decide if going to overflow
            if(plug->indx+chunk >= plug->bufsize)
            {
            	//this means we've already filled the buffer, but haven't finished the xfade
                chunk = plug->bufsize - plug->indx;
                plug->state = XFADE_ONLY;
            }
            //load buffer with xfade
            for(j=0; j<chunk; j++)
            {
                //still loading end of buffer
#ifdef NO_COMP
                plug->buf[plug->indx++] = plug->input_p[i];//no compression
#else
                plug->buf[plug->indx++] = plug->input_p[i]*plug->env/rms_shift(&plug->rms_calc,plug->input_p[i]);
#endif

#ifdef LAYER
            	//layer 2 full cycles on top of each other
                plug->buf[plug->indx2] = .5*plug->buf[plug->indx2+plug->wavesize] + .5*plug->buf[plug->indx2];
#endif

                //but now also playing back start of buffer
                plug->output_p[i++] += plug->gain*plug->buf[plug->indx2++];
                plug->gain += slope;

            }
            //xfade out end if we're there else we'll do it in the next state
            if(plug->indx2>=plug->wavesize)//TODO: this must actually be ==
            {
#ifndef NO_FADE
                for(k=0; k<plug->xfade_size; k++)
#ifdef LAYER
#ifdef LINEAR_FADE
                    plug->buf[k] += .5*(1-k/plug->xfade_size)*plug->buf[plug->indx2+plug->wavesize+k];
#else // constant power
                    plug->buf[k] += .5*(1-plug->xf_func[k])*plug->buf[plug->indx2+plug->wavesize+k];
#endif
#else //no layer, use next cycle rather than the 3rd
#ifdef LINEAR_FADE
                    plug->buf[k] += (1-k/plug->xfade_size)*plug->buf[plug->indx2+k];
#else // constant power
                    plug->buf[k] += (1-plug->xf_func[k])*plug->buf[plug->indx2+k];
#endif//linear_fade
#endif//layer
#endif//no_fade
                plug->indx2 = 0;
            }
        }
        else if(plug->state == XFADE_ONLY)//xfade after buffer is full, in practice we never get here, but we might change our smoothing strategy again
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
#ifdef LAYER
            	//continue layering the 2 cycles
                plug->buf[plug->indx2] = .5*plug->buf[plug->indx2+plug->wavesize] + .5*plug->buf[plug->indx2];
#endif
                plug->output_p[i++] += plug->gain*plug->buf[plug->indx2++];
                plug->gain += slope;
            }
            //xfade out end
            if(plug->indx2>=plug->wavesize)//TODO: this must acutally be ==
            {
#ifndef NO_FADE
                for(k=0; k<plug->xfade_size; k++)
#ifdef LAYER
#ifdef LINEAR_FADE
                    plug->buf[k] += .5*(1-k/plug->xfade_size)*plug->buf[plug->indx2+plug->wavesize+k];
#else // constant power
                    plug->buf[k] += .5*(1-plug->xf_func[k])*plug->buf[plug->indx2+plug->wavesize+k];
#endif
#else //no layer, use next cycle rather than the 3rd
#ifdef LINEAR_FADE
                    plug->buf[k] += (1-k/plug->xfade_size)*plug->buf[plug->indx2+k];
#else // constant power
                    plug->buf[k] += (1-plug->xf_func[k])*plug->buf[plug->indx2+k];
#endif//linear_fade
#endif//layer
#endif//no_fade
                plug->indx2 = 0;
            }
        }
#endif
#ifdef TEST
        else if(plug->state == DEBUGGING)//just loop buffer and track gain changes
        {
        	if(plug->indx2<plug->wavesize)
        	{
				if(plug->indx2+chunk>=plug->wavesize)
					chunk = plug->wavesize-plug->indx2;
				for(j=0; j<chunk; j++)
				{
					plug->output_p[i] = plug->buf[plug->indx2++];
					plug->output2_p[i++] = 0;
				}
        	}
        	else if(plug->indx2 < 2*plug->wavesize && plug->indx2 < plug->bufsize)
        	{
				if(plug->indx2+chunk>=2*plug->wavesize)
					chunk = 2*plug->wavesize-plug->indx2;
				for(j=0; j<chunk; j++)
				{
					plug->output_p[i] = 0;
					plug->output2_p[i++] = plug->buf[plug->indx2++];
				}
        	}
        	else
				for(j=0; j<chunk; j++)
				{
					plug->output_p[i] = plug->output2_p[i] = 0;
					i++;
				}

        }
#endif
        else if(plug->state == PLAYING)//just loop buffer and track gain changes
        {
            slope = (*plug->drone_gain_p-plug->gain)/interp;
#ifdef SHOW_BUF
            for(j=0; j<chunk; j++)
            {
            if(plug->dbg&1)//TODO: remove this line
                plug->output_p[i++] += plug->gain*plug->buf[plug->indx2++];
            else //rm
            {
            plug->output_p[i++] = 0;//rm
            plug->indx2++;//rm
            }
                plug->gain += slope;
                //plug->indx2 = plug->indx2<plug->wavesize?plug->indx2:0;
                if(plug->dbg&2 && plug->indx2>=plug->wavesize)//rm and uncomment above
                {
                	plug->indx2 = 0;
                	plug->dbg++;
                }
                else if(plug->indx2>=plug->bufsize)
                {
                	plug->indx2 = 0;
                	plug->dbg++;
                }
            }
#else
            for(j=0; j<chunk; j++)
            {
                plug->output_p[i++] += plug->gain*plug->buf[plug->indx2++];
                plug->gain += slope;
                plug->indx2 = plug->indx2<plug->wavesize?plug->indx2:0;
            }
#endif
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
                plug->score = START_SCORE;
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
                plug->score = START_SCORE;
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
    uint8_t i;
    plug->sample_freq = sample_freq;
    tmp = 0x8000;//15 bits
    if(sample_freq<100000)//88.1 or 96.1kHz
        tmp = tmp>>1;//14 bits
    if(sample_freq<50000)//44.1 or 48kHz
        tmp = tmp>>1;//13 bits //8192
    plug->buf = (float*)malloc(tmp*sizeof(float));
    plug->bufsize = tmp;
    plug->acorr_size = tmp>>3;//1024 if you mess with this, keep in mind it may need change in the default score value
    plug->xfade_size = tmp>>6;//128
    plug->wave_max = (tmp - plug->xfade_size)>>1;//4064
    plug->wave_min = tmp>>6;//128
    plug->wavesize = plug->wave_max;
    plug->indx = 0;
    plug->indx2 = plug->wave_min;
    plug->state = INACTIVE;
    plug->gain = 0;
    plug->score = START_SCORE;
    plug->env = 0;
    plug->dbg = 0;

    //half rasied cosine for equal power xfade
    plug->xf_func = (float*)malloc(plug->xfade_size*sizeof(float));
	for (i = 0; i < plug->xfade_size; i++) plug->xf_func[i] = 0.5 * (1 - cos((M_PI * i / plug->xfade_size)));

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
    case OUT2:
        plug->output2_p = (float*)data;
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
    free(plug->xf_func);
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
