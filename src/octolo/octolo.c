//Spencer Jackson
//octolo.c
#include<lv2.h>
#include<lv2/lv2plug.in/ns/ext/urid/urid.h>
#include<lv2/lv2plug.in/ns/ext/atom/util.h>
#include<lv2/lv2plug.in/ns/ext/time/time.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"octolo.h"

//OCTOLO - octaver and tremolo had a baby and this is it

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif



// SEQUENCES
// read right bit to left (seq>>step)
// sync
//  1111 1111 1111 1111 0xFFFF
//  1111 1111 1111 1111 0xFFFF
//  1111 1111 1111 1111 0xFFFF
// 
// alt1     
//  0101 0101 0101 0101 0x5555
//  1010 1010 1010 1010 0xAAAA
//  0101 0101 0101 0101 0x5555
//
// alt2     
//  1010 1010 1010 1010 0xAAAA
//  1010 1010 1010 1010 0xAAAA
//  0101 0101 0101 0101 0x5555
//
// step
//  1000 1000 1000 1000 0x8888
//  0101 0101 0101 0101 0x5555
//  0010 0010 0010 0010 0x2222
//
// cycle up
//  0100 1001 0010 0100 0x4924
//  0010 0100 1001 0010 0x2492
//  1001 0010 0100 1001 0x9249
// 
// cycle dn
//  1001 0010 0100 1001 0x9249
//  0010 0100 1001 0010 0x2492
//  0100 1001 0010 0100 0x4924

//pcycles
// PAN SEQUENCES
// center
//  1111 1111 1111 1111 0xFFFF
//  1111 1111 1111 1111 0xFFFF
//
// alt
//  0101 0101 0101 0101 0x5555
//  1010 1010 1010 1010 0xAAAA
//
// alt2
//  0011 0011 0011 0011 0x3333
//  1100 1100 1100 1100 0xCCCC
//
// alt3
//  0111 0001 1100 0111 0x71C7
//  1000 1110 0011 1000 0x8E38
//
// alt4
//  0000 1111 0000 1111 0x0F0F
//  1111 0000 1111 0000 0xF0F0
//
// step
//  0111 0111 0111 0111 0x7777
//  1101 1101 1101 1101 0xDDDD
//
// cycle l2r
//  1011 0110 1101 1011 0xB6DB
//  0110 1101 1011 0110 0x6DB6
//
// cycle r2l
//  0110 1101 1011 0110 0x6DB6
//  1011 0110 1101 1011 0xB6DB

enum oct {
    UP = 0,
    MID = 1,
    DOWN = 2,
    DRY = 3
};

typedef struct _OCTOLO
{
    uint16_t w; //current write point in buffer
    float r[3]; //read points in buffer (up and dn oct)
    float *buf;
    uint8_t stereo;
    uint8_t seq; //current sequence
    uint8_t step; //current point in sequence
    uint8_t stepofs; //step offset for pan
    uint8_t pseq; //pan sequence currently in use
    float phase;
    float ofs[3]; //phase offset to allow overlap
    float sample_freq;
    float period; //frames per trem cycle
    float tempo;
    float slope;
    float gain[4];
    float gainr[4];

    LV2_Atom_Sequence* atom_in_p; 
    float *input_p;
    float *output_p;
    float *outputr_p;
    float *enable_p;
    float *length_p;
    float *dry_p;
    float *md_p;
    float *dn_p;
    float *up_p;
    float *shape_p;
    float *slope_p;
    float *seq_p;
    float *overlap_p;
    float *panseq_p;
    float *width_p;
    float *panoffset_p;

    struct _URI
    {
        LV2_URID atom_blank;
        LV2_URID atom_object;
        LV2_URID atom_long;
        LV2_URID atom_float;
        LV2_URID time_position;
        LV2_URID time_barbeat;
        LV2_URID time_bpm;
        LV2_URID time_speed;
        LV2_URID time_frame;
        LV2_URID time_fps;
        
    } URI;
} OCTOLO;

//x E [-pi,pi]
//s E (0,pi/2) -> (triangle,square) _/--\_
float myslope(float x,float s,float sl,float sh)
{
    if(x < -sh || x > sh)
        return 0;
    else if(x < -sl)
        return s*(x + sh);//slope up
    else if(x < sl)
        return 1;
    else
        return -s*(x - sh);//slope down
}

void run_octolo(LV2_Handle handle, uint32_t nframes)
{
    OCTOLO* plug = (OCTOLO*)handle;
    float* in, *out, *buf;
    float phase,dphase,ofs[3],gain[4];
    float tmp,gainstep,slope,sl,sh;
    float rdn;
    uint16_t rup, rmd;
    uint16_t i,w, evchunk;
    int32_t chunk;
    uint8_t j,seq,step,ofsf;
    LV2_Atom* tempoatom;
    const LV2_Atom_Object* obj;
    LV2_Atom_Event* ev;

    const uint16_t cycles[3][6] = 
    {    //sync  alt1    alt2    step    cyclup cycldn
        {0xffff, 0x5555, 0xaaaa, 0x8888, 0x4924, 0x9249},
        {0xffff, 0xaaaa, 0xaaaa, 0x5555, 0x2492, 0x2492},
        {0xffff, 0x5555, 0x5555, 0x2222, 0x9249, 0x4924},
    };

    in = plug->input_p;
    out = plug->output_p;
    buf = plug->buf;
    w = plug->w;
    step = plug->step;
    phase = plug->phase;
    seq = plug->seq;//(uint8_t)*plug->seq_p;
    slope = plug->slope;
    sl = (M_PI-1/slope)/2;
    sh = (M_PI+1/slope)/2;
    ofsf = 0;
    if(plug->ofs[0] || plug->ofs[1] || plug->ofs[2] || *plug->overlap_p)
        ofsf = 1;
    tmp  = 0;
    for(j=0;j<3;j++)
    {
        ofs[j] = plug->ofs[j];
        gain[j] = plug->gain[j];
        tmp += gain[j];
    }
    gain[DRY] = plug->gain[DRY];

    //get atom events started
    ev = lv2_atom_sequence_begin(&(plug->atom_in_p)->body);

    if( (!tmp && gain[DRY] == 1.0 ) && !*plug->enable_p)
    {//shortcut, effect disabled
        //copy input
        memcpy(out,in,sizeof(float)*nframes);
        //get new tempos 
        while(!lv2_atom_sequence_is_end(&(plug->atom_in_p)->body,(plug->atom_in_p)->atom.size, ev))
        {
            ev = lv2_atom_sequence_next(ev);
            if(ev->body.type == plug->URI.atom_object || ev->body.type == plug->URI.atom_blank)
            {
                obj = (const LV2_Atom_Object*)&ev->body;
                if(obj->body.otype == plug->URI.time_barbeat)
                {
                    lv2_atom_object_get(obj,plug->URI.time_bpm,&tempoatom);
                    if(tempoatom && tempoatom->type == plug->URI.atom_float)
                    {
                        plug->tempo = ((LV2_Atom_Float*)tempoatom)->body;
                    }
                }
            }
        }
        //all done!
        return; 
    }

    rup = plug->r[UP];
    rmd = plug->r[MID];
    rdn = plug->r[DOWN];
    if(*plug->enable_p)
        gainstep = *plug->dry_p - plug->gain[DRY];
    else
        gainstep = 1.0 - plug->gain[DRY];
    gainstep /= nframes>64?nframes:64;

    dphase = 2*M_PI/plug->period; //delta phase per frame

    //max period is 1.4 sec = .67
    for(i=0;i<nframes;i++)
    {
        evchunk = nframes - i;
        tmp = 0;//use this as exit flag
        while(!lv2_atom_sequence_is_end(&(plug->atom_in_p)->body,(plug->atom_in_p)->atom.size, ev) && !tmp)
        {
            ev = lv2_atom_sequence_next(ev);
            if(ev)
            {
                if(ev->body.type == plug->URI.atom_object || ev->body.type == plug->URI.atom_blank)
                {
                    obj = (const LV2_Atom_Object*)&(ev->body);
                    if(obj->body.otype == plug->URI.time_barbeat)
                    {
                        lv2_atom_object_get(obj,plug->URI.time_bpm,&tempoatom);
                        if(tempoatom && tempoatom->type == plug->URI.atom_float)
                        {
                            tmp = ((LV2_Atom_Float*)tempoatom)->body;
                            if(tmp != plug->tempo)
                            {
                                evchunk = ev->time.frames-i; 
                                plug->tempo = tmp;
                            }
                            else
                                tmp = 0;
                        }
                    }
                }
            }
        }

        while(evchunk)
        {
            chunk = -phase/dphase;
            if(evchunk < chunk)
                chunk = evchunk;
            if(ofsf && chunk > 0)
            {
                //process current place to 0
                evchunk -= chunk;
                for( ; chunk; chunk--)
                { 
                    //this isn't a great AA filter, but hopefuly good enough, and yeah, a ZOH....
                    buf[w++] = in[i];
                    out[i] =  gain[DRY ]*buf[rmd];
                    out[i] += gain[UP  ]*myslope(phase+ofs[UP  ],slope,sl,sh)*( buf[rup] + buf[rup+1] );
                    out[i] += gain[MID ]*myslope(phase+ofs[MID ],slope,sl,sh)*buf[rmd];
                    out[i] += gain[DOWN]*myslope(phase+ofs[DOWN],slope,sl,sh)*buf[(uint16_t)rdn];
                    rup += 2;
                    rmd += 1;
                    rdn = rdn>0xFFFF?0:rdn+.5;
                    gain[DRY] += gainstep;
                    phase += dphase;
                    i++;
                }
                if(phase+dphase > 0)
                {//transition to next state
                    if(*plug->overlap_p)
                    {
                        step++;
                        step %= 12;
                    }
                    //TODO: this is all wrong, slope sl sh
                    slope = 1/(M_PI*(1.001-*plug->slope_p));
                    sl = (M_PI-1/slope)/2;
                    sh = (M_PI+1/slope)/2;
                    for(j=0;j<3;j++)
                    {//voices
                        if(ofs[j]) 
                        {//we can only transition if we are at the end of a cycle (or off)
                            if(((cycles[j][seq])>>step)&0x0001)
                            {//turn on
                                ofs[j] = -M_PI;
                                switch(j)
                                {
                                case UP:
                                    rup = w-1-ceil(plug->period);
                                    gain[UP] = .5**plug->up_p**plug->enable_p;//.5 is for the AA filter
                                    dphase = 2*M_PI/plug->period;
                                    break;
                                case MID:
                                    rmd = w-1;
                                    gain[MID] = *plug->md_p**plug->enable_p;
                                    break;
                                case DOWN:
                                    rdn = w-1;
                                    gain[DOWN] = *plug->dn_p**plug->enable_p;
                                    break;
                                }
                            }
                            else
                            {//turn off
                                ofs[j] = 0;
                                gain[j] = 0;
                                if(j==UP)
                                    dphase = 2*M_PI/plug->period; 
                            }
                        }//if voice is offset
                    }//for voices
                }//if done with half cycle
            }//if processing half cycles

            //process current place to pi
            chunk = (M_PI-phase)/dphase;
            if(evchunk < chunk)
                chunk = evchunk;
            evchunk -= chunk;
            for( ; chunk; chunk--)
            { 
                //this isn't a great AA filter, but hopefuly good enough, and yeah, a ZOH....
                buf[w++] = in[i];
                out[i] =  gain[DRY ]*buf[rmd];
                out[i] += gain[UP  ]*myslope(phase+ofs[UP  ],slope,sl,sh)*( buf[rup] + buf[rup+1] );
                out[i] += gain[MID ]*myslope(phase+ofs[MID ],slope,sl,sh)*buf[rmd];
                out[i] += gain[DOWN]*myslope(phase+ofs[DOWN],slope,sl,sh)*buf[(uint16_t)rdn];
                rup += 2;
                rmd += 1;
                rdn = rdn>0xFFFF?0:rdn+.5;
                gain[DRY] += gainstep;
                phase += dphase;
                i++;
            }

            if(phase+dphase >= M_PI)
            {
                phase -= 2*M_PI;
                step++;
                step %= 12;
                seq = (uint8_t)*plug->seq_p;
                slope = 1/(M_PI*(1.001-*plug->slope_p));
                sl = (M_PI-1/slope)/2;
                sh = (M_PI+1/slope)/2;
                for(j=0;j<3;j++)
                {//go through voices
                    if(!ofs[j])
                    {//can only transition at end of cycle
                        if(((cycles[j][seq])>>step)&0x0001)
                        {//turn on
                            ofs[j] = 0;
                            switch(j)
                            {
                            case UP:
                                rup = w-1-ceil(plug->period);
                                gain[UP] = .5**plug->up_p**plug->enable_p;//.5 is for the AA filter
                                dphase = 2*M_PI/plug->period;
                                break;
                            case MID:
                                rmd = w-1;
                                gain[MID] = *plug->md_p**plug->enable_p;
                                break;
                            case DOWN:
                                rdn = w-1;
                                gain[DOWN] = *plug->dn_p**plug->enable_p;
                                break;
                            }
                        }
                        else
                        {//turn off
                            ofs[j] = *plug->overlap_p*M_PI;
                            gain[j] = 0;
                            if(j==UP)
                                dphase = 2*M_PI/plug->period; 
                        }
                    }//if not offset
                    else
                    {//gotta wrap the offset
                        ofs[j] = M_PI;
                    }
                }//for voices
            }//if done with cycle
        }//while evchunk
        //now we've processed up until that last atom, we can apply the new speed
        plug->period = 60*plug->sample_freq**plug->length_p/plug->tempo;
        if(*plug->overlap_p)
            plug->period *= 2;
        //disallow too slow of trem
        while(plug->period >= 0x10000)
            plug->period *= .5;
        tmp = 2*M_PI/plug->period;
        if(tmp > dphase) //if phase is growing
            dphase = tmp; //apply it
        //otherwise we'll wait until UP is at a safe place 
    }//for i

    //keep state stuff for next time;
    plug->step = step;
    plug->seq = seq;
    plug->phase = phase;
    for(j=0;j<3;j++)
    {
        plug->ofs[j] = ofs[j];
        plug->gain[j] = gain[j];
    }
    plug->gain[DRY] = gain[DRY];
    plug->r[UP]  = rup;
    plug->r[MID] = rmd;
    plug->r[DOWN]= rdn;
    plug->w = w; 
    plug->slope = slope;

    return;
}

//get an approximate sin/cos pan
//input pan E[-1,1]
void pan_law(float pan, float *l, float *r)
{
    float ysin,ycos;
    ysin = -pan - pan*pan;
    ycos = ysin - pan;
    *l = 0.225*(ysin*(ysin>0?ysin:-ysin) - ysin) + ysin;
    *r = 0.225*(ycos*(ycos>0?ycos:-ycos) - ycos) + ycos;
}

//Lets wait and see what people think would be best
// sequenced hard pans
// adjustable, per-voice pans
//
// sequences allow everything and more
// just add width control and sequence offset
//
void run_stereoctolo(LV2_Handle handle, uint32_t nframes)
{
    OCTOLO* plug = (OCTOLO*)handle;
    float* in, *outl,*outr, *buf;
    float phase,dphase,ofs[3],mono[5],gainl[4],gainr[3];
    float tmp,gainstep,slope,sl,sh;
    float rdn;
    uint16_t rup, rmd;
    uint16_t i,w, evchunk;
    int32_t chunk;
    uint8_t j,seq,step,ofsf,pseq,stepofs;
    LV2_Atom* tempoatom;
    const LV2_Atom_Object* obj;
    LV2_Atom_Event* ev;

    const uint16_t cycles[3][6] = 
    {    //sync  alt1    alt2    step    cyclup cycldn
        {0xffff, 0x5555, 0xaaaa, 0x8888, 0x4924, 0x9249},
        {0xffff, 0xaaaa, 0xaaaa, 0x5555, 0x2492, 0x2492},
        {0xffff, 0x5555, 0x5555, 0x2222, 0x9249, 0x4924},
    };
    const int8_t pcycles[8][16] =
    {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //sync
        {-1, 1,-1, 1,-1, 1,-1, 1,-1, 1,-1, 1,-1, 1,-1, 1}, //alt
        {-1,-1, 1, 1,-1,-1, 1, 1,-1,-1, 1, 1,-1,-1, 1, 1}, //alt2
        {-1,-1,-1, 1, 1, 1,-1,-1,-1, 1, 1, 1,-1,-1,-1, 1}, //alt3
        {-1,-1,-1,-1, 1, 1, 1, 1,-1,-1,-1,-1, 1, 1, 1, 1}, //alt4
        {-1, 0, 1, 0,-1, 0, 1, 0,-1, 0, 1, 0,-1, 0, 1, 0}, //step
        {-1, 0, 1,-1, 0, 1,-1, 0, 1,-1, 0, 1,-1, 0, 1,-1}, //cyclelr
        { 1, 0,-1, 1, 0,-1, 1, 0,-1, 1, 0,-1, 1, 0,-1, 1}, //cyclerl
    };

    in = plug->input_p;
    outl = plug->output_p;
    outr = plug->outputr_p;
    buf = plug->buf;
    w = plug->w;
    step = plug->step;
    stepofs = plug->stepofs;
    pseq = plug->pseq;
    phase = plug->phase;
    seq = plug->seq;//(uint8_t)*plug->seq_p;
    slope = plug->slope;
    ofsf = 0;
    if(plug->ofs[0] || plug->ofs[1] || plug->ofs[2] || *plug->overlap_p)
        ofsf = 1;
    tmp  = 0;
    for(j=0;j<3;j++)
    {//grab last state
        ofs[j] = plug->ofs[j];
        gainl[j] = plug->gain[j];
        gainr[j] = plug->gainr[j];
        tmp += gainl[j]+gainr[j];
    }
    gainl[DRY] = plug->gain[DRY];

    //get atom events started
    ev = lv2_atom_sequence_begin(&(plug->atom_in_p)->body);

    if( (!tmp && gainl[DRY] == 1.0 ) && !*plug->enable_p)
    {//shortcut, effect disabled
        //copy input
        memcpy(outl,in,sizeof(float)*nframes);
        memcpy(outr,in,sizeof(float)*nframes);
        //get new tempos 
        while(!lv2_atom_sequence_is_end(&(plug->atom_in_p)->body,(plug->atom_in_p)->atom.size, ev))
        {
            ev = lv2_atom_sequence_next(ev);
            if(ev->body.type == plug->URI.atom_object || ev->body.type == plug->URI.atom_blank)
            {
                obj = (const LV2_Atom_Object*)&ev->body;
                if(obj->body.otype == plug->URI.time_barbeat)
                {
                    lv2_atom_object_get(obj,plug->URI.time_bpm,&tempoatom);
                    if(tempoatom && tempoatom->type == plug->URI.atom_float)
                    {//since we're disabled, we can just apply the tempo immediately
                        plug->tempo = ((LV2_Atom_Float*)tempoatom)->body;
                    }
                }
            }
        }
        //all done!
        return; 
    }

    rup = plug->r[UP];
    rmd = plug->r[MID];
    rdn = plug->r[DOWN];
    if(*plug->enable_p)
        gainstep = *plug->dry_p - plug->gain[DRY];
    else
        gainstep = 1.0 - plug->gain[DRY];
    gainstep /= nframes>64?nframes:64;

    dphase = 2*M_PI/plug->period;

    //max period is 1.4 sec = .67
    for(i=0;i<nframes;i++)
    {
        evchunk = nframes - i;
        tmp = 0;//use this as exit flag
        while(!lv2_atom_sequence_is_end(&(plug->atom_in_p)->body,(plug->atom_in_p)->atom.size, ev) && !tmp)
        {
            ev = lv2_atom_sequence_next(ev);
            if(ev)
            {
                if(ev->body.type == plug->URI.atom_object || ev->body.type == plug->URI.atom_blank)
                {
                    obj = (const LV2_Atom_Object*)&(ev->body);
                    if(obj->body.otype == plug->URI.time_barbeat)
                    {
                        lv2_atom_object_get(obj,plug->URI.time_bpm,&tempoatom);
                        if(tempoatom && tempoatom->type == plug->URI.atom_float)
                        {
                            tmp = ((LV2_Atom_Float*)tempoatom)->body;
                            if(tmp != plug->tempo)
                            {
                                evchunk = ev->time.frames-i; 
                                plug->tempo = tmp;
                            }
                            else
                                tmp = 0;
                        }
                    }
                }
            }
        }

        while(evchunk)
        {
            chunk = -phase/dphase;
            if(evchunk < chunk)
                chunk = evchunk;
            if(ofsf && chunk > 0)
            {
                //process current place to 0
                evchunk -= chunk;
                for( ; chunk; chunk--)
                { 
                    //this isn't a great AA filter, but hopefuly good enough, and yeah, a ZOH....
                    buf[w++] = in[i];
                    mono[UP]  = myslope(phase+ofs[UP  ],slope,sl,sh)*( buf[rup] + buf[rup+1] );
                    mono[MID] = myslope(phase+ofs[MID ],slope,sl,sh)*buf[rmd];
                    mono[DOWN]= myslope(phase+ofs[DOWN],slope,sl,sh)*buf[(uint16_t)rdn];
                    outl[i] = outr[i] = gainl[DRY]*buf[rmd];
                    for(j=0;j<3;j++)
                    {
                        outl[i] += gainl[j]*mono[j];
                        outr[i] += gainr[j]*mono[j];
                    }
                    rup += 2;
                    rmd += 1;
                    rdn = rdn>0xFFFF?0:rdn+.5;
                    gainl[DRY] += gainstep;
                    phase += dphase;
                    i++;
                }
                if(phase+dphase > 0)
                {//transition to next state
                    if(*plug->overlap_p)
                    {
                        step++;
                        step %= 12;
                    }
                    slope = 1/(M_PI*(1.001-*plug->slope_p));
                    sl = (M_PI-1/slope)/2;
                    sh = (M_PI+1/slope)/2;
                    for(j=0;j<3;j++)
                    {//voices
                        if(ofs[j]) 
                        {//we can only transition if we are at the end of a cycle (or off)
                            if(((cycles[j][seq])>>step)&0x0001)
                            {//turn on
                                ofs[j] = -M_PI;
                                pan_law(*plug->width_p*pcycles[pseq][step+stepofs],&gainl[j],&gainr[j]);
                                switch(j)
                                {
                                case UP:
                                    rup = w-1-ceil(plug->period);
                                    gainl[UP] *= .5**plug->up_p**plug->enable_p;//.5 is for the AA filter
                                    gainr[UP] *= .5**plug->up_p**plug->enable_p;//.5 is for the AA filter
                                    dphase = 2*M_PI/plug->period;
                                    break;
                                case MID:
                                    rmd = w-1;
                                    gainl[MID] *= *plug->md_p**plug->enable_p;
                                    gainr[MID] *= *plug->md_p**plug->enable_p;
                                    break;
                                case DOWN:
                                    rdn = w-1;
                                    gainl[DOWN] *= *plug->dn_p**plug->enable_p;
                                    gainr[DOWN] *= *plug->dn_p**plug->enable_p;
                                    break;
                                }
                            }
                            else
                            {//turn off
                                ofs[j] = 0;
                                gainl[j] = 0;
                                gainr[j] = 0;
                                if(j==UP)
                                    dphase = 2*M_PI/plug->period; 
                            }
                        }//if voice is offset
                    }//for voices
                }//if done with half cycle
            }//if processing half cycles

            //process current place to pi
            chunk = (M_PI-phase)/dphase;
            if(evchunk < chunk)
                chunk = evchunk;
            evchunk -= chunk;
            for( ; chunk; chunk--)
            { 
                //this isn't a great AA filter, but hopefuly good enough, and yeah, a ZOH....
                buf[w++] = in[i];
                mono[UP]  = myslope(phase+ofs[UP  ],slope,sl,sh)*( buf[rup] + buf[rup+1] );
                mono[MID] = myslope(phase+ofs[MID ],slope,sl,sh)*buf[rmd];
                mono[DOWN]= myslope(phase+ofs[DOWN],slope,sl,sh)*buf[(uint16_t)rdn];
                outl[i] = outr[i] = gainl[DRY]*buf[rmd];
                for(j=0;j<3;j++)
                {
                    outl[i] += gainl[j]*mono[j];
                    outr[i] += gainr[j]*mono[j];
                }
                rup += 2;
                rmd += 1;
                rdn = rdn>0xFFFF?0:rdn+.5;
                gainl[DRY] += gainstep;
                phase += dphase;
                i++;
            }

            if(phase+dphase >= M_PI)
            {
                //we're safe to update everything
                phase -= 2*M_PI;
                step++;
                step %= 12;
                seq = (uint8_t)*plug->seq_p;
                stepofs = (uint8_t)*plug->panoffset_p;
                pseq = (uint8_t)*plug->panseq_p;
                slope = 1/(M_PI*(1.001-*plug->slope_p));
                sl = (M_PI-1/slope)/2;
                sh = (M_PI+1/slope)/2;
                for(j=0;j<3;j++)
                {//go through voices
                    if(!ofs[j])
                    {//can only transition at end of cycle
                        if(((cycles[j][seq])>>step)&0x0001)
                        {//turn on
                            ofs[j] = 0;
                            pan_law(*plug->width_p*pcycles[pseq][step+stepofs],&gainl[j],&gainr[j]);
                            switch(j)
                            {
                            case UP:
                                rup = w-1-ceil(plug->period);
                                gainl[UP] *= .5**plug->up_p**plug->enable_p;//.5 is for the AA filter
                                gainr[UP] *= .5**plug->up_p**plug->enable_p;//.5 is for the AA filter
                                dphase = 2*M_PI/plug->period;
                                break;
                            case MID:
                                rmd = w-1;
                                gainl[MID] *= *plug->md_p**plug->enable_p;
                                gainr[MID] *= *plug->md_p**plug->enable_p;
                                break;
                            case DOWN:
                                rdn = w-1;
                                gainl[DOWN] *= *plug->dn_p**plug->enable_p;
                                gainr[DOWN] *= *plug->dn_p**plug->enable_p;
                                break;
                            }
                        }
                        else
                        {//turn off
                            ofs[j] = *plug->overlap_p*M_PI;
                            gainl[j] = 0;
                            gainr[j] = 0;
                            if(j==UP)
                                dphase = 2*M_PI/plug->period; 
                        }
                    }//if not offset
                    else
                    {//gotta wrap the offset
                        ofs[j] = M_PI;
                    }
                }//for voices
            }//if done with cycle
        }//while evchunk
        //now we've processed up until that last atom, we can apply the new speed
        plug->period = 60*plug->sample_freq**plug->length_p/plug->tempo;
        if(*plug->overlap_p)
            plug->period *= 2;
        //disallow too slow of trem
        while(plug->period >= 0x10000)
            plug->period *= .5;
        tmp = 2*M_PI/plug->period;
        if(tmp > dphase)
            dphase = tmp; 
        //otherwise we'll wait until UP is at a safe place 
    }//for i

    //keep state stuff for next time;
    plug->step = step;
    plug->stepofs = stepofs;
    plug->seq = seq;
    plug->pseq = pseq;
    plug->phase = phase;
    for(j=0;j<3;j++)
    {
        plug->ofs[j] = ofs[j];
        plug->gain[j] = gainl[j];
    }
    plug->gain[DRY] = gainl[DRY];
    plug->r[UP]  = rup;
    plug->r[MID] = rmd;
    plug->r[DOWN]= rdn;
    plug->w = w; 
    plug->slope = slope;

    return;
}

LV2_Handle init_octolo(const LV2_Descriptor *descriptor,double sample_freq, const char *bundle_path,const LV2_Feature * const* host_features)
{
    uint16_t i;

    OCTOLO* plug = malloc(sizeof(OCTOLO));

    //this makes the max period a function of samplerate, but you're dumb if you are using anything but 44100 or 48k
    plug->buf = (float*)calloc(0x10000,sizeof(float));
    for(i=0;i<3;i++)
    {
        plug->r[i] = 0;
        plug->ofs[i] = 0;
        plug->gain[i] = 0;
    }
    plug->gain[DRY] = 0;
    plug->w = 0;
    plug->seq = 0;
    plug->step = 12;
    plug->phase = -M_PI;

    plug->sample_freq = sample_freq;
    plug->period = sample_freq; //default to 1 hz
    plug->tempo = 120;
    plug->slope = 2/M_PI;


    //init buf
    plug->buf[0] = 0;
    for(i=1;i;i++)
        plug->buf[i] = 0;

    //get urid map value for tempo sync
    for (int i = 0; host_features[i]; i++)
    {
        if (strcmp(host_features[i]->URI, LV2_URID__map) == 0)
        {
            LV2_URID_Map *urid_map = (LV2_URID_Map *) host_features[i]->data;
            if (urid_map)
            {
                plug->URI.atom_blank = urid_map->map(urid_map->handle, LV2_ATOM__Blank);
                plug->URI.atom_object = urid_map->map(urid_map->handle, LV2_ATOM__Object);
                plug->URI.atom_long = urid_map->map(urid_map->handle, LV2_ATOM__Long);
                plug->URI.atom_float = urid_map->map(urid_map->handle, LV2_ATOM__Float);
                plug->URI.time_position = urid_map->map(urid_map->handle, LV2_TIME__Position);
                plug->URI.time_barbeat = urid_map->map(urid_map->handle, LV2_TIME__barBeat);
                plug->URI.time_bpm = urid_map->map(urid_map->handle, LV2_TIME__beatsPerMinute);
                plug->URI.time_speed = urid_map->map(urid_map->handle, LV2_TIME__speed);
                plug->URI.time_frame = urid_map->map(urid_map->handle, LV2_TIME__frame);
                plug->URI.time_fps = urid_map->map(urid_map->handle, LV2_TIME__framesPerSecond);
                break;
            }
        }
    }
    return plug;
}

void connect_octolo_ports(LV2_Handle handle, uint32_t port, void *data)
{
    OCTOLO* plug = (OCTOLO*)handle;
    switch(port)
    {
    case ATOM_IN:
        plug->atom_in_p = (LV2_Atom_Sequence*)data;
        break;
    case IN:
        plug->input_p = (float*)data;
        break;
    case OUT:
        plug->output_p = (float*)data;
        break;
    case ENABLE:
        plug->enable_p = (float*)data;
        break;
    case LENGTH:
        plug->length_p = (float*)data;
        break;
    case DRYG:
        plug->dry_p = (float*)data;
        break;
    case WET:
        plug->md_p = (float*)data;
        break;
    case OCTDOWN:
        plug->dn_p = (float*)data;
        break;
    case OCTUP:
        plug->up_p = (float*)data;
        break;
    case SLOPE:
        plug->slope_p = (float*)data;
        break;
    case SEQUENCE:
        plug->seq_p = (float*)data;
        break;
    case OVERLAP:
        plug->overlap_p = (float*)data;
        break;
    default:
        puts("UNKNOWN PORT YO!!");
    }
}

void connect_stereoctolo_ports(LV2_Handle handle, uint32_t port, void *data)
{
    OCTOLO* plug = (OCTOLO*)handle;
    switch(port)
    {
    case SATOM_IN:
        plug->atom_in_p = (LV2_Atom_Sequence*)data;
        break;
    case SIN:
        plug->input_p = (float*)data;
        break;
    case SOUTL:
        plug->output_p = (float*)data;
        break;
    case SOUTR:
        plug->outputr_p = (float*)data;
        break;
    case SENABLE:
        plug->enable_p = (float*)data;
        break;
    case SLENGTH:
        plug->length_p = (float*)data;
        break;
    case SDRYG:
        plug->dry_p = (float*)data;
        break;
    case SWET:
        plug->md_p = (float*)data;
        break;
    case SOCTDOWN:
        plug->dn_p = (float*)data;
        break;
    case SOCTUP:
        plug->up_p = (float*)data;
        break;
    case SSLOPE:
        plug->slope_p = (float*)data;
        break;
    case SSEQUENCE:
        plug->seq_p = (float*)data;
        break;
    case SOVERLAP:
        plug->overlap_p = (float*)data;
        break;
    case SPSEQ:
        plug->panseq_p = (float*)data;
        break;
    case SWIDTH:
        plug->width_p = (float*)data;
        break;
    case SPOFFS:
        plug->panoffset_p = (float*)data;
        break;
    default:
        puts("UNKNOWN PORT YO!!");
    }
}

void cleanup_octolo(LV2_Handle handle)
{
    OCTOLO* plug = (OCTOLO*)handle;
    free(plug->buf);
    free(plug);
}

static const LV2_Descriptor octolo_descriptor=
{
    OCTOLO_URI,
    init_octolo,
    connect_octolo_ports,
    0,//activate
    run_octolo,
    0,//deactivate
    cleanup_octolo,
    0//extension
};

static const LV2_Descriptor stereoctolo_descriptor=
{
    STEREOCTOLO_URI,
    init_octolo,
    connect_stereoctolo_ports,
    0,//activate
    run_octolo,
    0,//deactivate
    cleanup_octolo,
    0//extension
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index)
    {
    case 0:
        return &octolo_descriptor;
    case 1:
        return &stereoctolo_descriptor;
    default:
        return 0;
    }
}
