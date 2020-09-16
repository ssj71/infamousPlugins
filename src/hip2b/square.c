//Spencer Jackson
//square.c
#include<lv2.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<hip2b.h>


#define UP      1
#define DOWN    -1
#define NHARMONICS 128
#define HALF    64
#define HALFPLUS 65
#define PI 3.1415926535897932384626433832795
#define DC_CUTOFF 10*2*PI //rad/s
#define PRACTICALLYZERO .001
#define TIMEOUT 5

#define CIRCULATE(val) val=val<NHARMONICS?val:0


typedef struct _SQUARE
{
    int8_t step;
    int8_t state;
    int8_t outstate;
    int8_t nextstate;
    uint8_t pos;
    float table[HALFPLUS];//one quarter of a square wave

    float circularbuf[NHARMONICS];
    uint8_t w,r,c;//read, write & check pointers
    uint8_t headway;//distance to next transition
    uint8_t skip;
    float dcprevin;
    float dcprevout;
    float gain;

    float *input_p;
    float *output_p;
    float *latency_p;
    float *up_p;
    float *down_p;
    float *octave_p;
    float *ingain_p;
    float *wetdry_p;
    float *outgain_p;
} SQUARE;

//starting again.
//just look 1 transition ahead, keep track of space to next trans.
//circular buffer holds input*gain
//index c (check) is always the transition or the lookahead limit
void run_square(LV2_Handle handle, uint32_t nframes)
{
    SQUARE* plug = (SQUARE*)handle;
    float temp;
    uint32_t i;
    uint8_t j, w, r, c;
    uint8_t nskip = 1<<-(int)*plug->octave_p;
    float gstep = *plug->outgain_p - plug->gain;
    gstep /= nframes>64?nframes:64;
    if(gstep<1e-15 && gstep>-1e-15)//avoid denormals
    {
        gstep = 0;
        plug->gain = *plug->output_p;
    }


    w = plug->w;
    r = plug->r;
    c = plug->c;
    for(i=0; i<nframes; i++)
    {
        //fill buffer
        plug->circularbuf[w++] = *plug->ingain_p*plug->input_p[i];
        CIRCULATE(w);

        //at this point, headway is known, pos is prev. value, step is current
        //1 write buffer, 2 update pos 3. update headway 4. write out
        //change position
        if(plug->headway == 0)
        {
            //on the transition point, search for next one
            plug->pos = 0;//(uint8_t)plug->headway;
            if(plug->skip++>=nskip)
            {
                plug->skip = 1;
                plug->outstate = (!plug->outstate)*plug->nextstate - plug->outstate;
                //this implements the following table (necessary for octaves)
                //    \out
                // next\ _dn_|_0__|_up_
                //   dn | up | dn | dn
                //   up | up | up | dn
            }
            plug->state = plug->nextstate;
            //update headway
            for(j=0; j<=HALF; j++)
            {
                if(plug->state != DOWN && plug->circularbuf[c] <= *plug->down_p)
                {
                    c++;
                    CIRCULATE(c);
                    plug->nextstate = DOWN;
                    break;
                }
                else if (plug->state != UP && plug->circularbuf[c] >= *plug->up_p)
                {
                    c++;
                    CIRCULATE(c);
                    plug->nextstate = UP;
                    break;
                }
                else
                {
                    c++;
                    CIRCULATE(c);
                }
            }
            plug->headway = j;
            plug->step = 1;//start moving up the table
        }
        else if(plug->headway < plug->pos)
        {
            //need to start decrementing
            plug->pos = (uint8_t)plug->headway;
            //update headway
            plug->headway--;
        }
        else if(plug->headway > HALF)
        {
            //increment to end of table and stay, check for headway change
            plug->pos += plug->step;
            if(plug->pos == HALF)
            {
                plug->step = 0;
            }
            //update headway
            if(plug->state != DOWN
                    && plug->circularbuf[c] <= *plug->down_p
                    && plug->nextstate != DOWN)
            {
                plug->headway = HALF;
                plug->nextstate = DOWN;
            }
            else if (plug->state != UP
                     && plug->circularbuf[c] >= *plug->up_p
                     && plug->nextstate != UP)
            {
                plug->headway = HALF;
                plug->nextstate = UP;
            }
            c++;
            CIRCULATE(c);

        }
        else
        {
            //know headway, increment pos, dec. headway
            if(plug->pos == plug->headway)
                plug->step = 0;
            plug->pos += plug->step;
            //update headway
            plug->headway--;
        }

        //dc removal (hpf)
        temp = .999*plug->dcprevout + plug->outstate*plug->table[plug->pos] - plug->dcprevin;
        plug->dcprevin = plug->outstate*plug->table[plug->pos];
        plug->dcprevout = temp;

        //write out the frame
        plug->output_p[i] = (1-*plug->wetdry_p)*plug->circularbuf[r++] + *plug->wetdry_p*temp;
        CIRCULATE(r);
        plug->gain += gstep;
        plug->output_p[i] *= plug->gain;
    }
    *plug->latency_p = HALF;
    plug->w = w;
    plug->r = r;
    plug->c = c;

    //this way for dc offset reset
    if(plug->dcprevout < PRACTICALLYZERO && plug->dcprevout > -PRACTICALLYZERO  && plug->headway > HALF)
    {
        plug->pos = 0;
        plug->state = 0;
        plug->dcprevout = 0;
        plug->dcprevin = 0;
    }
}

LV2_Handle init_square(const LV2_Descriptor *descriptor,double sample_rate, const char *bundle_path,const LV2_Feature * const* host_features)
{
    SQUARE* plug = malloc(sizeof(SQUARE));

    uint8_t i,j;
    int8_t k;
    double s = PI/NHARMONICS;

    for(i=0; i<=HALF; i++)
    {
        plug->table[i] = 0;
    }
    k=1;
    for(i=1; i<NHARMONICS; i+=2) //harmonics
    {
        for(j=0; j<=HALF; j++) //samples
        {
            plug->table[HALF-j] += (k/(float)i)*sin(PI/2 + (float)i*j*s);
        }
        k = -k;
    }

    plug->step = 0;
    plug->state = 0;
    plug->outstate = 0;
    plug->nextstate = 0;
    plug->pos = 0;
    plug->headway = HALF + 1;
    plug->skip = 1;

    plug->w = HALF;
    plug->r = 0;
    plug->c = HALF;

    for(i=0; i<NHARMONICS; i++)
    {
        plug->circularbuf[i] = 0;
    }

    plug->dcprevin = 0;
    plug->dcprevout = 0;
    plug->gain = 1;

    return plug;
}

void connect_square_ports(LV2_Handle handle, uint32_t port, void *data)
{
    SQUARE* plug = (SQUARE*)handle;
    switch(port)
    {
    case IN:
        plug->input_p = (float*)data;
        break;
    case OUT:
        plug->output_p = (float*)data;
        break;
    case LATENCY:
        plug->latency_p = (float*)data;
        break;
    case UPP:
        plug->up_p = (float*)data;
        break;
    case DOWNN:
        plug->down_p = (float*)data;
        break;
    case OCTAVE:
        plug->octave_p = (float*)data;
        break;
    case INGAIN:
        plug->ingain_p = (float*)data;
        break;
    case WETDRY:
        plug->wetdry_p = (float*)data;
        break;
    case OUTGAIN:
        plug->outgain_p = (float*)data;
        break;
    default:
        puts("UNKNOWN PORT YO!!");
    }
}

void cleanup_square(LV2_Handle handle)
{
    SQUARE* plug = (SQUARE*)handle;
    free(plug);
}

static const LV2_Descriptor hip2b_descriptor=
{
    HIP2B_URI,
    init_square,
    connect_square_ports,
    0,//activate
    run_square,
    0,//deactivate
    cleanup_square,
    0//extension
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index)
    {
    case 0:
        return &hip2b_descriptor;
    default:
        return 0;
    }
}
