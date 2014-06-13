//Spencer Jackson
//square.c
#include<lv2.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

#define STUCK_URI "http://infamousplugins.sourceforge.net/plugs.html#stuck"
#define PI 3.1415926535897932384626433832795

enum states
{
    INACTIVE = 0, 
    LOADING,
    CALC_THRESH,
    MATCHING,
    MINIMIZING,
    LOADING_XFADE, 
    PLAYING,
    RELEASING,
    QUICK_RELEASING
};

typedef struct _STUCK
{
    unsigned short indx;//current place of buffer
    unsigned short indx2;
    unsigned short bufsize;//size of buffer 
    unsigned short wavesize;//size of waveform
    unsigned short xfade_size;//size of crossfade 
    unsigned short fade_size;//size of fade in/out
    unsigned char state;
    double sample_freq;
    
    float *buf;
    float gain; 
    float thresh;
    float score;

    float *input_p;
    float *output_p;
    float *trigger_p;
    float *stick_it_p;
    float *drone_gain_p;
    float *release_p;
    float *dbg_p;
}STUCK;

enum stuck_ports
{
    IN =0,
    OUT,
    TRIGGER,
    STICKIT,
    DRONEGAIN,
    RELEASE,
    DBG
};

void run_stuck(LV2_Handle handle, uint32_t nframes)
{
    STUCK* plug = (STUCK*)handle;
    uint32_t i,j,k,t,chunk=0;
    double slope = 0;

    memcpy(plug->output_p,plug->input_p,nframes*sizeof(float)); 
    
    if(plug->state == INACTIVE)
    {//decide if triggered
        if(*plug->stick_it_p >= 1 || plug->trigger_p[nframes-1] >= 1)
        {
	    plug->state = LOADING;
	    plug->indx = 0;
            plug->gain = 0;
	}
        else return;
    }
    else if(plug->state < LOADING_XFADE)
    {//decide if need to abort
        if(*plug->stick_it_p < 1 && plug->trigger_p[nframes-1] < 1)
        {
	    plug->indx = 0;
            plug->indx2 = plug->xfade_size;
	    plug->state = INACTIVE; 
	    plug->gain = 0; 
	    plug->wavesize = plug->bufsize;
	    return; 
	} 
    }
    else if(plug->state < RELEASING) 
    {//decide if released 
        if(*plug->stick_it_p < 1 && plug->trigger_p[nframes-1] < 1)
        {
	    plug->state = RELEASING; 
	} 
    }
    else if(plug->state == RELEASING)
    {//decide if new trigger has been sent before release is complete
        if(*plug->stick_it_p >= 1 || plug->trigger_p[nframes-1] >= 1)
	{
            plug->state = QUICK_RELEASING; 
	{
    }

    for(i=0;i<nframes;)
    {    
        chunk = nframes - i;
        if(plug->state == LOADING)//load enough frames to start calculating the autocorrelation
	{   
	    //decide if reaching minimum length in this period
            if(plug->indx+chunk >= plug->xfade_size*2)
	    {
	        chunk = plug->xfade_size*2 - plug->indx;
		plug->state = CALC_THRESH;
	    }
	    //load buffer
	    for(j=0;j<chunk;j++)
	    {
	        plug->buf[plug->indx++] = plug->input_p[i++]; 
	    } 
	}
	else if(plug->state == CALC_THRESH)//find autocorrelation of 1 frame away as threshold
	{ 
	    float tmp;
	    //plug->buf[plug->indx++] = plug->input_p[i++]; 
	    plug->score = 0;
	    t = 1;
    	    for(k=0;k<plug->xfade_size;k++)
	    {
	        tmp = plug->buf[t++] - plug->buf[k];
	        plug->score += tmp*tmp;
	    }
	    plug->thresh = .2*plug->score*plug->xfade_size;//scale threshold based on result
	    plug->state = MATCHING;
	}
	else if(plug->state == MATCHING)//find autocorrelation thats in the ballpark
	{
	    //decide if reaching maximum length in this period
            if(plug->indx+chunk >= plug->bufsize)
	    {
	        chunk = plug->bufsize - plug->indx;
		plug->state = LOADING_XFADE;
	    }
	    //find good correlated piece 
	    float tmp;
	    for(j=0;j<chunk;j++)
	    { 
		plug->score = 0;
		t=0;
		for(k=plug->indx2;k<plug->xfade_size;k++)
		{
		    tmp = plug->input_p[k] - plug->buf[t++];
		    score += tmp*tmp;
		}
		plug->indx2++;

		if(plug->score<plug->thresh)
		{
		    j=chunk;
		    plug->state = MINIMIZING;
		}
		else
		{ 
	            t=0;
		    score = 0;
		}
		plug->buf[plug->indx++] = plug->input_p[i++]; 
	    }
            plug->indx = plug->indx<plug->bufsize?plug->index:0; 
	}
	else if(plug->state == MINIMIZING)//find next local minimum, assume thats the fundamental period or some multiple of it
	{
            if(plug->indx+chunk >= plug->bufsize)
	    {
	        chunk = plug->bufsize - plug->indx;
		plug->state = LOADING_XFADE;
	    }
	    //find good correlated piece 
	    float tmp,score;
	    for(j=0;j<chunk;j++)
	    { 
		score = 0;
		t=0;
		for(k=plug->indx2;k<plug->xfade_size;k++)
		{
		    tmp = plug->input_p[k] - plug->buf[t++];
		    score += tmp*tmp;
		}
		plug->indx2++;

                plug->buf[plug->indx++] = plug->input_p[i++]; 
		if(score>plug->score)
		{
		    j=chunk;
		    plug->state = LOADING_XFADE;
		    plug->indx = 0;
		    plug->indx2 -= 2;//subtract 1 because we incremented already and 1 because the minimum was previous calculation
		    plug->wavsize = plug->indx2;
		}
		else
		{ 
	            t=0;
		    plug->score = score;
		    score = 0;
		}
	    }
            plug->indx = plug->indx<plug->bufsize?plug->index:0; 
	}
	else if(plug->state == LOADING_XFADE)//xfade end of buffer with start (loop it) and fade in drone
	{
	    slope = (*plug->drone_gain_p-plug->gain)/(double)nframes;
	    //decide if xfade ends in this period
            if(plug->indx+chunk >= plug->xfade_size)
	    {
	        chunk = plug->xfade_size - plug->indx;
		plug->state = PLAYING;
	    }
	    //load buffer with xfade
	    double phi = 0;
	    for(j=0;j<chunk;j++)
	    {
	        //phi = .5*(1-cos(PI*plug->indx/(double)(plug->xfade_size)));//raised cosine
		phi = plug->indx/(double)plug->xfade_size;//linear
	        plug->buf[plug->indx] = (1.0-phi)*plug->buf[plug->indx2++] + phi*plug->buf[plug->indx];
		plug->output_p[i++] += plug->gain*plug->buf[plug->indx++];
		plug->gain += slope; 
	    }
            plug->indx = plug->indx<plug->wavesize?plug->index:0; 
        }
        else if(plug->state == PLAYING)
	{
	    slope = (*plug->drone_gain_p-plug->gain)/(double)nframes;
	    for(j=0;j<chunk;j++)
	    { 
		plug->output_p[i++] += plug->gain*plug->buf[plug->indx++];
		plug->gain += slope;
                plug->indx = plug->indx<plug->wavesize?plug->index:0; 
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
		plug->output_p[i++] += plug->gain*plug->buf[plug->indx++];
		plug->gain += slope; 
                plug->indx = plug->indx<plug->wavesize?plug->index:0; 
	    }
	    if(plug->gain <= -slope)
	    {
	        plug->indx = 0;
                plug->indx2 = plug->xfade_size;
		plug->state = INACTIVE; 
		plug->gain = 0; 
		plug->wavesize = plug->bufsize;
		return;
	    }
        }
	else if(plug->state == QUICK_RELEASING)
	{
	    slope = -*plug->drone_gain_p/(double)plug->xfade_size;
	    //decide if released in this period
	    if(plug->gain + chunk*slope < slope)
	    {
	        chunk = -plug->gain/slope; 
		plug->state = LOADING; 
	    }
	    for(j=0;j<chunk;j++)
	    { 
		plug->output_p[i++] += plug->gain*plug->buf[plug->indx++];
		plug->gain += slope;
		plug->indx &= plug->bufmask;
		i = i>plug->wavesize?0:i;
	    }
	    if(plug->gain <= -slope)
	    {
	        plug->indx = 0;
                plug->indx2 = plug->xfade_size;
		plug->state = LOADING; 
		plug->wavesize = plug->bufsize;
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
    tmp = 0x4000;//16384;15 bits
    if(sample_freq<100000)//88.1 or 96.1kHz
        tmp = tmp>>1;//14 bits
    if(sample_freq<50000)//44.1 or 48kHz
        tmp = tmp>>1;//13 bits
    plug->buf = malloc(tmp*sizeof(float));
    plug->bufsize = tmp;
    plug->wavesize = tmp;
    plug->xfade_size = tmp>>4; 
    plug->indx = 0;
    plug->indx2 = plug->xfade_size;
    plug->state = INACTIVE;
    plug->gain = 0;

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
