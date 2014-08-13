//Spencer Jackson
//stuck.c
#include<lv2.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"rms_calc.h"
#include"stuck.h"

#define STUCK_URI "http://infamousplugins.sourceforge.net/plugs.html#stuck"
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
    unsigned short indx;//current write point in buffer
    unsigned short indx2;//working/read point in buffer
    unsigned short bufsize;//size of buffer 
    unsigned short wavesize;//size of waveform
    unsigned short acorr_size;//size of autocorrelation 
    unsigned short xfade_min;//shortest allowed wavesize
    unsigned short xfade_max;//longest allowed wavesize
    unsigned char state;
    double sample_freq;
    
    float *buf;
    float gain; 
    float env;//envelope gain to normalize compression to
    float thresh;
    float score;

    RMS_CALC rms_calc;

    float *input_p;
    float *output_p;
    float *trigger_p;
    float *stick_it_p;
    float *drone_gain_p;
    float *release_p;
    float *dbg_p;
}STUCK;

void run_stuck(LV2_Handle handle, uint32_t nframes)
{
    STUCK* plug = (STUCK*)handle;
    uint32_t i,j,k,t,chunk=0;
    double slope = 0;

    memcpy(plug->output_p,plug->input_p,nframes*sizeof(float)); 
    //for(i=0;i<nframes;i++) plug->output_p[i] = 0;	
    
    
    if(plug->state == INACTIVE)
    {//decide if triggered 
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
    {//decide if need to abort
#ifdef CV_PORTS
        if(*plug->stick_it_p < 1 && plug->trigger_p[nframes-1] < 1) 
#else
        if(*plug->stick_it_p < 1)
#endif
        {
	    //reinit
	    plug->indx = 0;
            plug->indx2 = plug->xfade_min;
	    plug->state = INACTIVE; 
	    plug->gain = 0; 
	    plug->wavesize = plug->xfade_max;
	    plug->score = 1;
            rms_block_fill(&plug->rms_calc, plug->input_p,nframes);
	    return; 
	} 
    }
    else if(plug->state < RELEASING) 
    {//decide if released 
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
    {//decide if new trigger has been sent before release is complete
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

    for(i=0;i<nframes;)
    {    
        chunk = nframes - i;
        if(plug->state == LOADING)//load enough frames to start calculating the autocorrelation
	{   
	    //decide if reaching minimum length in this period
            if(plug->indx+chunk >= plug->xfade_min+plug->acorr_size)
	    {
	        chunk = plug->xfade_min + plug->acorr_size - plug->indx;
		plug->state = MATCHING;
	    }
	    //load buffer with compressed signal
	    for(j=0;j<chunk;j++)
	    {
	        plug->buf[plug->indx++] = plug->input_p[i]*plug->env/rms_shift(&plug->rms_calc,plug->input_p[i]); 
		i++;
	    } 
	}
	else if(plug->state == MATCHING)//find autocorrelation
	{
            if(plug->indx2+chunk >= plug->xfade_max)
	    {
	        chunk = plug->xfade_max - plug->indx2;
		plug->state = LOADING_XFADE;
	    }
	    // calculate autocorrelation of sample in buffer, save the minimum
	    float tmp,score;
	    for(j=0;j<chunk;j++)
	    { 
		score = 0;
		t=0;
		
		for(k=plug->indx2;k<plug->indx2+plug->acorr_size && score<=plug->score;k++)
		{
		    tmp = plug->buf[k] - plug->buf[t++];//jsyk this isn't the strict definition of an autocorrelation, a variation on the principle
		    score += tmp*tmp;
		}
		plug->indx2++;

	        plug->buf[plug->indx++] = plug->input_p[i]*plug->env/rms_shift(&plug->rms_calc,plug->input_p[i]); 
		i++;

		//save place if score is lower than last minimum
		if(score<=plug->score)
		{
		    plug->wavesize = plug->indx2 -1;//subtract 1 because we incremented already
		    plug->score = score;
		}
	    }
            if(plug->indx2>=plug->xfade_max)
	    { 
		plug->indx2 = 0;//reset indx2
	    }
	}
	else if(plug->state == LOADING_XFADE)//xfade end of buffer with start (loop it) over an entire wave and fade in drone
	{
	    slope = (*plug->drone_gain_p-plug->gain)/(double)nframes;
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
	    for(j=0;j<chunk;j++)
	    {
	        plug->buf[plug->indx2] = .5*plug->buf[plug->indx2+plug->wavesize] + .5*plug->buf[plug->indx2];
		//still loading end of buffer
		plug->buf[plug->indx++] = plug->input_p[i]*plug->env/rms_shift(&plug->rms_calc,plug->input_p[i]); 
		plug->output_p[i++] += plug->gain*plug->buf[plug->indx2++];
		plug->gain += slope; 
	    }
        }
	else if(plug->state == XFADE_ONLY)//xfade after buffer is full
	{
	    slope = (*plug->drone_gain_p-plug->gain)/(double)nframes;
	    //decide if xfade ends in this period
            if(plug->indx2+chunk >= plug->wavesize)
	    {
	        chunk = plug->wavesize - plug->indx2;
		plug->state = PLAYING;
	    }
	    //xfade buffer
	    for(j=0;j<chunk;j++)
	    {
	        plug->buf[plug->indx2] = .5*plug->buf[plug->indx2+plug->wavesize] + .5*plug->buf[plug->indx2];
		plug->output_p[i++] += plug->gain*plug->buf[plug->indx2++];
		plug->gain += slope; 
	    }
            plug->indx2 = plug->indx2<plug->wavesize?plug->indx2:0; 
        }
        else if(plug->state == PLAYING)//just loop buffer and track gain changes
	{
	    slope = (*plug->drone_gain_p-plug->gain)/(double)nframes;
	    for(j=0;j<chunk;j++)
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
	    for(j=0;j<chunk;j++)
	    { 
		plug->output_p[i++] += plug->gain*plug->buf[plug->indx2++];
		plug->gain += slope; 
                plug->indx2 = plug->indx2<plug->wavesize?plug->indx2:0; 
	    }
	    if(plug->gain <= -slope)
	    {
	        plug->indx = 0;
                plug->indx2 = plug->xfade_min;
		plug->state = INACTIVE; 
		plug->gain = 0; 
		plug->wavesize = plug->xfade_max;
		plug->score = 1;
		return;
	    }
        }
	else if(plug->state == QUICK_RELEASING)
	{
	    slope = -*plug->drone_gain_p/(double)plug->xfade_min;
	    //decide if released in this period
	    if(plug->gain + chunk*slope < slope)
	    {
	        chunk = -plug->gain/slope; 
		plug->state = LOADING; 
	    }
	    for(j=0;j<chunk;j++)
	    { 
		plug->output_p[i++] += plug->gain*plug->buf[plug->indx2++];
		plug->gain += slope;
                plug->indx2 = plug->indx2<plug->wavesize?plug->indx2:0; 
	    } 
            rms_block_fill(&plug->rms_calc, plug->input_p,chunk);
	    if(plug->gain <= -slope)
	    {
	        plug->indx = 0;
                plug->indx2 = plug->xfade_min;
		plug->state = LOADING; 
		plug->wavesize = plug->xfade_max;
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

    unsigned short tmp;
    plug->sample_freq = sample_freq; 
    tmp = 0x8000;//15 bits
    if(sample_freq<100000)//88.1 or 96.1kHz
        tmp = tmp>>1;//14 bits
    if(sample_freq<50000)//44.1 or 48kHz
        tmp = tmp>>1;//13 bits
    plug->buf = (float*)malloc(tmp*sizeof(float));
    plug->bufsize = tmp;
    plug->acorr_size = tmp>>3; 
    plug->xfade_max = tmp>>1;
    plug->xfade_min = tmp>>6;
    plug->wavesize = plug->xfade_max;
    plug->indx = 0;
    plug->indx2 = plug->xfade_min;
    plug->state = INACTIVE;
    plug->gain = 0;
    plug->score = 1;
    plug->env = 0;

    rms_init(&plug->rms_calc,tmp>>3);

    return plug;
}

void connect_stuck_ports(LV2_Handle handle, uint32_t port, void *data)
{
    STUCK* plug = (STUCK*)handle;
    switch(port)
    {
    case IN:         plug->input_p = (float*)data;break;
    case OUT:        plug->output_p = (float*)data;break;
    case TRIGGER:    plug->trigger_p = (float*)data;break;
    case STICKIT:    plug->stick_it_p = (float*)data;break;
    case DRONEGAIN:  plug->drone_gain_p = (float*)data;break;
    case RELEASE:    plug->release_p = (float*)data;break; 
    case DBG:        plug->dbg_p = (float*)data;break; 
    default:         puts("UNKNOWN PORT YO!!");
    }
}

void cleanup_stuck(LV2_Handle handle)
{
    STUCK* plug = (STUCK*)handle;
    rms_deinit(&plug->rms_calc);
    free(plug->buf);
    free(plug);
}

static const LV2_Descriptor stuck_descriptor={
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
    switch (index) {
    case 0:
        return &stuck_descriptor;
    default:
        return 0;
    }
}
