// -----------------------------------------------------------------------
//
//  Copyright (C) 2009-2011 Fons Adriaensen <fons@linuxaudio.org>
//    
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
// -----------------------------------------------------------------------


#ifndef __RETUNER_H
#define __RETUNER_H


#include <fftw3.h>
#include <zita-resampler/resampler.h>
#include "lfo.h"

typedef struct
{
    int           active;
    float          gain;
    float          pan;
    float          ratio;
    float          rindex1, rindex2;
    float          delay;//latency in fragments
    bool           xfade;
    float		   corroffs;

    float          g, gainstep;
    float          p, panstep;
} Shifter;

class Retuner
{
public:

    Retuner (int fsamp, int nshift = 1);
    ~Retuner (void);

    int process (int nfram, float *inp, float *out);
    int process (int nfram, float *inp, float *outl, float *outr);

    void set_refpitch (float v)
    {
        _refpitch = v;
    }

    void set_notebias (float v)
    {
        _notebias = v / 13.0f;
    }

    void set_corrfilt (float v)
    {
        _corrfilt = (4 * _frsize) / (v * _fsamp);
    }

    void set_corrgain (float v)
    {
        _corrgain = v;
    }

    void set_corroffs (float v, int i=0)
    {
        _shift[i].corroffs = v;
        //_corroffs = v;
    }

    void set_notemask (int k)
    {
        _notemask = k;
    }
   
    int get_noteset (void)
    {
        int k;

        k = _notebits;
        _notebits = 0;
        return k;
    }

    float get_error (void)
    {
        return 12.0f * _error;
    }

    //ssj
    unsigned long get_latency (void)
    {
        return 1.5 * _frsize;
    }

    void plug->tuner->set_lfo_shape(float f)
    {
        _lfoshape = f;//0 rand, 1 sine
    }

    void set_active(int a, int i)
    {
        if (_shift[i].active == 1 && a == 0)
            _shift[i].active = -1;
        if (_shift[i].active >= 0)
            _shift[i].active = a;
    }

    void set_gain(float g, int i)
    {
        if (_shift[i].active == 1)
            _shift[i].gain = g;
    }

    void set_pan(float p, int i)
    {
        _shift[i].pan = p;
    }
    
    void set_delay(float ms, int i)
    {
        _shift[i].delay = ms * _fsamp / (1000 * _frsize);//delay in fragments
    }

    void plug->tuner->set_offs_lfo_amount(float g, int i)
    {
        _lfo[i].gain = g;
    }

    void plug->tuner->set_offs_lfo_freq(float f, int i)
    {
        _lfo[i].freq = f;
    }

    void plug->tuner->set_delay_lfo_amount(float g, int i)
    {
        _lfo[i+_nshift].gain = g;
    }

    void plug->tuner->set_delay_lfo_freq(float f, int i)
    {
        _lfo[i+_nshift].freq = f;
    }

private:

    void  findcycle (void);
    void  finderror (void);
    float cubic (float *v, float a);

    int              _fsamp;
    int              _ifmin;
    int              _ifmax;
    bool             _upsamp;
    int              _fftlen;
    int              _ipsize;
    int              _frsize;
    int              _ipindex;
    int              _frindex;
    int              _frcount;
    float            _refpitch;
    float            _notebias;
    float            _corrfilt; 
    float            _corrgain;
    //float            _corroffs;//
    int              _notemask;
    int              _notebits;
    int              _lastnote;
    int              _count;
    float            _cycle;
    float            _error;
    //float            _ratio;//
    //float            _phase;//ssj not used
    //bool             _xfade;//
    //float            _rindex1;//
    //float            _rindex2;//
    float           *_ipbuff;
    float           *_xffunc;
    float           *_fftTwind;
    float           *_fftWcorr;
    float           *_fftTdata;
    fftwf_complex   *_fftFdata;
    fftwf_plan       _fwdplan;
    fftwf_plan       _invplan;
    Resampler        _resampler;
    Shifter*         _shift;
    Lfo*             _lfo;
    int              _nshift;
    float            _lfoshape;
};


#endif
