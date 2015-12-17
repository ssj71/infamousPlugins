// -----------------------------------------------------------------------
//
//  Copyright (C) 2009-2011 Fons Adriaensen <fons@linuxaudio.org>
//  Copyright (C) 2015 Spencer Jackson <ssjackson71@gmail.com>
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

//  This code is forked from the amazing code from Fons Adriaensen, modified by spencer

#ifndef __RETUNER_H
#define __RETUNER_H


#include <fftw3.h>
#include <zita-resampler/resampler.h>
#include "lfo.h"

typedef struct
{
    int           active;
    float         gain;
    float         pan;
    float         ratio;
    float         rindex1, rindex2;
    float         d, delay;//latency in fragments
    bool          xfade;
    float		  corroffs;
    Lfo*          clfo;
    Lfo*          dlfo;

    float         g, gainstep;//used for parameter smoothing
    float         p, panstep;
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
        return 8 * _frsize;
    }

    void set_lfo_shape(float f)
    {
        _lfoshape = f;//0 rand, 1 sine
    }

    void sync_lfos(void)
    {
        for(int i=0; i<_nshift; i++)
        {
            _shift[i].clfo->reset();
            _shift[i].dlfo->reset();
        }
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

    void set_offs_lfo_amount(float g, int i)
    {
        _shift[i].clfo->gain = g;
    }

    void set_offs_lfo_freq(float f, int i)
    {
        _shift[i].clfo->freq = f;
    }

    void set_delay_lfo_amount(float g, int i)
    {
        _shift[i].dlfo->gain = g * _fsamp / (1000 * _frsize);
    }

    void set_delay_lfo_freq(float f, int i)
    {
        _shift[i].dlfo->freq = f;
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
    int              _notemask;
    int              _notebits;
    int              _lastnote;
    int              _count;
    float            _cycle[32];
    float            _error;
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
    int              _nshift;
    int              _ds;//downshift amount for cycle idex
    float            _pc;//previous successful cycle val
    float            _lfoshape;
};


#endif
