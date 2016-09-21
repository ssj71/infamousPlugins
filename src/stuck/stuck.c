//Spencer Jackson
//stuck.c
#include<lv2.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"stuck.h"

enum states
{
    INACTIVE = 0,
    LOADING,
    PLAYING,
    RELEASING,
    QUICK_RELEASING
};

//TODO: probably ought to envelope the input sample
typedef struct _STUCK
{
	uint8_t state;
	uint16_t r;//filter output
	uint16_t w;//filter input
	uint16_t time;//length of input sample to fiterbank

	float gain;
    double sample_freq;

    float *buf;

    float *input_p;
    float *output_p;
    float *trigger_p;
    float *stick_it_p;
    float *drone_gain_p;
    float *release_p;
    float *dbg_p;
    float *output2_p;

} STUCK;

//cascaded bank of schroeder all pass filters ripped out of freeverb
inline void filternate(uint16_t in, uint16_t out, float* buf)
{
    buf[out] = 0;

	buf[out] += .0625*(buf[in] + buf[out-1563]);
	buf[out] += -.125*(buf[in-225] + buf[out-1338]);
	buf[out] += -.125*(buf[in-341] + buf[out-1222]);
	buf[out] += -.125*(buf[in-556] + buf[out-1122]);
	buf[out] += -.125*(buf[in-566] + buf[out-1007]);
	buf[out] +=  .25*(buf[in-666] + buf[out-997]);
	buf[out] +=  .25*(buf[in-781] + buf[out-897]);
	buf[out] +=  .25*(buf[in-782] + buf[out-782]);
	buf[out] +=  .25*(buf[in-897] + buf[out-781]);
	buf[out] += -.5*(buf[in-997] + buf[out-666]);
	buf[out] += -.5*(buf[in-1007] + buf[out-566]);
	buf[out] += -.5*(buf[in-1122] + buf[out-556]);
	buf[out] += -.5*(buf[in-1222] + buf[out-341]);
	buf[out] += -.5*(buf[in-1338] + buf[out-225]);
	buf[out] += buf[in-1563];
}

void run_stuck(LV2_Handle handle, uint32_t nframes)
{
    STUCK* plug = (STUCK*)handle;
    uint32_t i,j,chunk=0;
    double slope = 0;
    double interp;

    memcpy(plug->output_p,plug->input_p,nframes*sizeof(float));

    interp = nframes>64?nframes:64;

    //Evaluate port values and see if it requires any state changes
    if(plug->state == INACTIVE)
    {
        //decide if triggered
        if(*plug->stick_it_p >= 1)
        {
            plug->state = LOADING;
            //any on-trigger events here
        }
    }
    else if(plug->state < PLAYING)
    {
        //decide if need to abort
        if(*plug->stick_it_p < 1)
        {
            //reinit
            return;
        }
    }
    else if(plug->state < RELEASING)
    {
        //decide if released
        if(*plug->stick_it_p < 1)
        {
            plug->state = RELEASING;
        }
    }
    else if(plug->state == RELEASING)
    {
        //decide if new trigger has been sent before release is complete
        if(*plug->stick_it_p >= 1)
        {
            plug->state = QUICK_RELEASING;
        }
    }

    //now run the state machine
    for(i=0; i<nframes;)
    {
        chunk = nframes - i;
        if(plug->state == LOADING)//load enough frames to start calculating the autocorrelation
        {
            slope = (*plug->drone_gain_p-plug->gain)/interp;
            //decide if reaching minimum length in this period
            if(plug->w+chunk >= plug->time)
            {
                chunk = plug->time - plug->w;
                plug->state = PLAYING;
            }
            for(j=0; j<chunk; j++)
            {
            	plug->buf[plug->w] = plug->input_p[i];
            	filternate(plug->w++, plug->r, plug->buf);
            	plug->output_p[i++] += plug->gain*plug->r++;
                plug->gain += slope;
            }
        }
        else if(plug->state == PLAYING)//just run the filter and track gain changes
        {
            slope = (*plug->drone_gain_p-plug->gain)/interp;
            for(j=0; j<chunk; j++)
            {
            	filternate(plug->w++, plug->r, plug->buf);
            	plug->output_p[i++] += plug->gain*plug->r++;
                plug->gain += slope;
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
            	filternate(plug->w++, plug->r, plug->buf);
            	plug->output_p[i++] += plug->gain*plug->r++;
                plug->gain += slope;
            }
            if(plug->gain <= -slope)
            {
            	//done, now get ready for next trigger
                plug->state = INACTIVE;
                plug->gain = 0;
				for(j=0;j<(uint16_t)(plug->r-plug->w);j++)
					plug->buf[(uint16_t)(plug->w+j)]  = 0;
                return;
            }
        }
        else if(plug->state == QUICK_RELEASING)
        {
            slope = -*plug->drone_gain_p/64.0;
            //decide if released in this period
            if(plug->gain + chunk*slope < slope)
            {
                chunk = -plug->gain/slope;
                plug->state = LOADING;
            }
            for(j=0; j<chunk; j++)
            {
            	filternate(plug->w++, plug->r, plug->buf);
            	plug->output_p[i++] += plug->gain*plug->r++;
                plug->gain += slope;
            }
            if(plug->gain <= -slope)
            {
            	//done, start next trigger
                plug->state = LOADING;
                plug->gain = 0;
				for(j=0;j<(uint16_t)(plug->r-plug->w);j++)
					plug->buf[(uint16_t)(plug->w+j)]  = 0;
            }
        }
    }
    return;
}

LV2_Handle init_stuck(const LV2_Descriptor *descriptor,double sample_freq, const char *bundle_path,const LV2_Feature * const* host_features)
{
    STUCK* plug = malloc(sizeof(STUCK));

    uint16_t i;
    plug->sample_freq = sample_freq;
    plug->time = .1*sample_freq;//as long as this stays longer than the longest filter tap (currently 1563) then the in and out won't overlap and we'll have 100%FB

    plug->r = plug->time;
    plug->w = 0;
    plug->buf = (float*)malloc(0xffff*sizeof(float));
    plug->state = INACTIVE;
    plug->gain = 0;

    //init buffer
    plug->buf[0] = 0;
    for(i=1;i;i++)
    	plug->buf[i]  = 0;

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
