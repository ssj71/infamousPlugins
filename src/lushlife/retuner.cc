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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "retuner.h"

#define DENORMAL 1.42e-45


Retuner::Retuner (int fsamp, int nshift) :
    _fsamp (fsamp),
    _refpitch (440.0f),
    _notebias (0.0f),
    _corrfilt (1.0f),
    _corrgain (1.0f),
    //_corroffs (0.0f),
    _notemask (0xFFF)
{
    int   i, h;
    float t, x, y;

    _ds = 10;
    if (_fsamp < 64000)
    {
        // At 44.1 and 48 kHz resample to double rate.
        _upsamp = true;
        _ipsize = 4096;
        _fftlen = 2048;
        _frsize = 128;
        _resampler.setup (1, 2, 1, 32); // 32 is medium quality.
        // Prefeed some input samples to remove delay.
        _resampler.inp_count = _resampler.filtlen () - 1;
        _resampler.inp_data = 0;
        _resampler.out_count = 0;
        _resampler.out_data = 0;
        _resampler.process ();
    }
    else if (_fsamp < 128000)
    {
        // 88.2 or 96 kHz.
        _upsamp = false;
        _ipsize = 4096;
        _fftlen = 4096;
        _frsize = 256;
    }
    else
    {
        // 192 kHz, double time domain buffers sizes.
        _upsamp = false;
        _ipsize = 8192;
        _fftlen = 8192;
        _frsize = 512;
        _ds ++;
    }
    
    _ipsize *= 8; //ssj add buffer space to allow delays

    // Accepted correlation peak range, corresponding to 60..1200 Hz.
    _ifmin = _fsamp / 1200;
    _ifmax = _fsamp / 60;

    // Various buffers
    _ipbuff = new float[_ipsize + 3];  // Resampled or filtered input
    _xffunc = new float[_frsize];      // Crossfade function
    _fftTwind = (float *) fftwf_malloc (_fftlen * sizeof (float)); // Window function 
    _fftWcorr = (float *) fftwf_malloc (_fftlen * sizeof (float)); // Autocorrelation of window 
    _fftTdata = (float *) fftwf_malloc (_fftlen * sizeof (float)); // Time domain data for FFT
    _fftFdata = (fftwf_complex *) fftwf_malloc ((_fftlen / 2 + 1) * sizeof (fftwf_complex));

    // FFTW3 plans
    _fwdplan = fftwf_plan_dft_r2c_1d (_fftlen, _fftTdata, _fftFdata, FFTW_ESTIMATE);
    _invplan = fftwf_plan_dft_c2r_1d (_fftlen, _fftFdata, _fftTdata, FFTW_ESTIMATE);

    // Clear input buffer.
    memset (_ipbuff, 0, (_ipsize + 1) * sizeof (float));

    // Create crossfade function, half of raised cosine.
    for (i = 0; i < _frsize; i++)
    {
        _xffunc [i] = 0.5 * (1 - cosf (M_PI * i / _frsize));
    }

    // Create window, raised cosine.
    for (i = 0; i < _fftlen; i++)
    {
        _fftTwind [i] = 0.5 * (1 - cosf (2 * M_PI * i / _fftlen));
    }

    // Compute window autocorrelation and normalise it.
    fftwf_execute_dft_r2c (_fwdplan, _fftTwind, _fftFdata);    
    h = _fftlen / 2;
    for (i = 0; i < h; i++)
    {
        x = _fftFdata [i][0];
        y = _fftFdata [i][1];
        _fftFdata [i][0] = x * x + y * y;
        _fftFdata [i][1] = 0;
    }
    _fftFdata [h][0] = 0;
    _fftFdata [h][1] = 0;
    fftwf_execute_dft_c2r (_invplan, _fftFdata, _fftWcorr);    
    t = _fftWcorr [0];
    for (i = 0; i < _fftlen; i++)
    {
        _fftWcorr [i] /= t;
    }

    // Initialise all counters and other state.
    _notebits = 0;
    _lastnote = -1;
    _count = 0;
    //_cycle = _frsize;
    _error = 0.0f;
    //_ratio = 1.0f;
    //_xfade = false;
    _ipindex = 0;
    _frindex = 0;
    _frcount = 0;
    //_rindex1 = _ipsize / 2;
    //_rindex2 = 0;

    //ssj initialize cycles
    for(i = 0; i < 32; i++)
        _cycle[i] = _frsize;

    //ssj initialize shifts
    _shift = new Shifter[nshift];
    _nshift = nshift;
    _lfoshape = .5;
    for (i = 0; i < nshift; i++)
    {
        _shift[i].active = 0;
        _shift[i].g = 1.0f;
        _shift[i].gain = 1.0f;
        _shift[i].gainstep = 0.0f;
        _shift[i].p = 0.5;
        _shift[i].pan = 0.5;
        _shift[i].panstep = 0.0f;
        _shift[i].ratio = 1.0f;
        _shift[i].rindex1 =  _ipsize / 2;
        _shift[i].rindex2 = 0;
        _shift[i].d = 0;
        _shift[i].delay = 0;
        _shift[i].xfade = false; 
        _shift[i].corroffs = 0.0f; 

        _shift[i].clfo = new Lfo(_fsamp,4*_frsize);
        _shift[i].dlfo = new Lfo(_fsamp,4*_frsize);
        _shift[i].clfo->gain = 0;
        _shift[i].clfo->freq = 1;
        _shift[i].dlfo->gain = 0;
        _shift[i].dlfo->freq = 1;

    }
    _shift[0].active = 1;
}


Retuner::~Retuner (void)
{
    delete[] _ipbuff;
    delete[] _xffunc;
    fftwf_free (_fftTwind);
    fftwf_free (_fftWcorr);
    fftwf_free (_fftTdata);
    fftwf_free (_fftFdata);
    fftwf_destroy_plan (_fwdplan);
    fftwf_destroy_plan (_invplan);
    for(int i=0;i<_nshift;i++)
    {
        delete _shift[i].clfo;
        delete _shift[i].dlfo;
    }
    delete[] _shift;
}

int Retuner::process (int nfram, float *inp, float *out)
{
    return process(nfram,inp,out,out);
}

int Retuner::process (int nfram, float *inp, float *outl, float *outr)
{
    int    i, k, k2, fi, fi2, p;
    float  ph, dp, r1, r2, dr, u1, u2, v;


    // Pitch shifting is done by resampling the input at the
    // required ratio, and eventually jumping forward or back
    // by one or more pitch period(s). Processing is done in
    // fragments of '_frsize' frames, and the decision to jump
    // forward or back is taken at the start of each fragment.
    // If a jump happens we crossfade over one fragment size. 
    // Every 4 fragments a new pitch estimate is made. Since
    // _fftsize = 16 * _frsize, the estimation window moves
    // by 1/4 of the FFT length.

    fi = _frindex;  // Write index in current fragment.

    // No assumptions are made about fragments being aligned
    // with process() calls, so we may be in the middle of
    // a fragment here. 

    while (nfram)
    {
        // Don't go past the end of the current fragment.
        k = _frsize - fi;
        if (nfram < k) k = nfram;
        nfram -= k;

        // At 44.1 and 48 kHz upsample by 2.
        if (_upsamp)
        {
            _resampler.inp_count = k;
            _resampler.inp_data = inp;
            _resampler.out_count = 2 * k;
            _resampler.out_data = _ipbuff + _ipindex;
            _resampler.process ();
            _ipindex += 2 * k;
        }
        // At higher sample rates apply lowpass filter.
        else
        {
            // Not implemented yet, just copy.
            memcpy (_ipbuff + _ipindex, inp, k * sizeof (float));
            _ipindex += k;
        }

        // Extra samples for interpolation.
        _ipbuff [_ipsize + 0] = _ipbuff [0];
        _ipbuff [_ipsize + 1] = _ipbuff [1];
        _ipbuff [_ipsize + 2] = _ipbuff [2];
        inp += k;
        if (_ipindex == _ipsize) _ipindex = 0;

        //now initialize output buffer
        for ( i = 0; i < k; i++)
        {
            outl[i] = 0;
            outr[i] = 0;
        } 

        // Process available samples.
        for (int shftdx = 0; shftdx < _nshift; shftdx++)
        {
            if (_shift[shftdx].active)
            {
                float* out1 = outl;
                float* out2 = outr;
                k2 = k;
                fi2 = fi;
                r1 = _shift[shftdx].rindex1;  // Read index for current input frame.
                r2 = _shift[shftdx].rindex2;  // Second read index while crossfading. 
                dr = _shift[shftdx].ratio;
                if (_upsamp) dr *= 2;
                if (_shift[shftdx].xfade)
                {
                    // Interpolate and crossfade.
                    while (k2--)
                    {
                        i = (int) r1;
                        u1 = cubic (_ipbuff + i, r1 - i);
                        i = (int) r2;
                        u2 = cubic (_ipbuff + i, r2 - i);
                        v = _xffunc [fi2++];
                        v = (1 - v) * u1 + v * u2;
                        *out1++ += v * _shift[shftdx].g * (0.5 - 0.5 * _shift[shftdx].p);
                        *out2++ += v * _shift[shftdx].g * (0.5 + 0.5 * _shift[shftdx].p);
                        _shift[shftdx].g += _shift[shftdx].gainstep;
                        _shift[shftdx].p += _shift[shftdx].panstep;
                        r1 += dr;
                        if (r1 >= _ipsize) r1 -= _ipsize;
                        r2 += dr;
                        if (r2 >= _ipsize) r2 -= _ipsize;
                    }
                }
                else
                {
                    // Interpolation only.
                    while (k2--)
                    {
                        i = (int) r1;
                        v =  cubic (_ipbuff + i, r1 - i);
                        *out1++ += v * _shift[shftdx].g * (0.5 - 0.5 * _shift[shftdx].p);
                        *out2++ += v * _shift[shftdx].g * (0.5 + 0.5 * _shift[shftdx].p);
                        _shift[shftdx].g += _shift[shftdx].gainstep;
                        _shift[shftdx].p += _shift[shftdx].panstep;
                        r1 += dr;
                        if (r1 >= _ipsize) r1 -= _ipsize;
                    }
                }
                // Save local state.
                _shift[shftdx].rindex1 = r1;
                _shift[shftdx].rindex2 = r2;
            }
            else
            {
                r1 = _shift[shftdx].rindex1;  // Read index for current input frame.
                r2 = _shift[shftdx].rindex2;  // Second read index while crossfading. 
                r1 += k;
                r2 += k;
                if (r1 >= _ipsize) r1 -= _ipsize;
                if (r2 >= _ipsize) r2 -= _ipsize;
                // Save local state.
                _shift[shftdx].rindex1 = r1;
                _shift[shftdx].rindex2 = r2;
            }
        }
        fi += k;
        outl += k;
        outr += k;
 
        // If at end of fragment check for jump.
        if (fi == _frsize) 
        {
            fi = 0;
            // Estimate the pitch every 4th fragment.
            if (++_frcount == 4)
            {
                _frcount = 0;
                findcycle ();
                p = (_ipindex>>_ds)-0;//estimate corresponds to middle of the fft window
                if (_cycle[p])
                {
                    // If the pitch estimate succeeds, find the
                    // nearest note and required resampling ratio.
                    _count = 0;
                    _pc = _cycle[p];
                    if(_corrgain)//ssj don't bother calculating if just shifting
                    finderror ();
                }
                else if (++_count > 5)
                {
                    // If the pitch estimate fails, the current
                    // ratio is kept for 5 fragments. After that
                    // the signal is considered unvoiced and the
                    // pitch error is reset.
                    _count = 5;
                    _cycle[p] = _frsize;
                    _error = 0;
                }
                else if (_count == 2)
                {
                    // Bias is removed after two unvoiced fragments.
                    _lastnote = -1;
                    _cycle[p] = _cycle[(p-1)&31];
                }
                else
                    _cycle[p] = _cycle[(p-1)&31];
                
                //update ratios
                for (int shftdx = 0; shftdx < _nshift; shftdx++)
                {
                    float a =  _shift[shftdx].corroffs + _shift[shftdx].clfo->out(_lfoshape);
                    if(a>24)a=24;
                    else if(a<-24)a=-24;
                    _shift[shftdx].ratio = powf (2.0f, a/12 - _error * _corrgain);
                    a = _shift[shftdx].dlfo->out(_lfoshape) + _shift[shftdx].delay;
                    if(a>112)
                        a = 112;//clamp so lfo doesn't go over bounds
                    else if(a<0)
                        a = 0; 
                    _shift[shftdx].d = a;
                }
            }

            for (int shftdx = 0; shftdx < _nshift; shftdx++)
            {
                r1 = _shift[shftdx].rindex1;  // Read index for current input frame.
                r2 = _shift[shftdx].rindex2;  // Second read index while crossfading. 
                // If the previous fragment was crossfading,
                // the end of the new fragment that was faded
                // in becomes the current read position.
                if (_shift[shftdx].xfade) r1 = r2;

                // A jump must correspond to an integer number
                // of pitch periods, and to avoid reading outside
                // the circular input buffer limits it must be at
                // least one fragment size.
                p = ((int)(r1+8*_frsize)>>_ds);//use cycle estimate corresponding with where we are, rather than where we want to be. May want to shift to middle of next fragment. Not sure.
                p &= 31;

                dr = _cycle[p] * (int)(ceilf (_frsize / _cycle[p]));//samples per ncycles  >= 1 fragment
                dp = dr / _frsize; //ratio of complete cycle(s) to fragment (>=1)
                ph = r1 - _ipindex; //old samples in buffer that have been read
                if (ph < 0) ph += _ipsize; //wrap around buffer end
                if (_upsamp)
                {
                    ph /= 2;
                    dr *= 2;
                }
                ph = ph / _frsize + 2 * _shift[shftdx].ratio - 122 + _shift[shftdx].d;//error in fragments of how much old buffer is kept. Target is to keep it so that each fragment period ends with around ph = 8*16-6=122 old fragments (so near the front of the buffer). As delay or ratio grows, the target moves backward in the buffer (fewer old fragments kept) and visa versa. Higher ratios will read more samples so need to start with greater latency.
                if (ph > 0.5f)
                {
                    // Jump back by 'dr' frames and crossfade.
                    //dr could actually be several fragments while ph will be number of fragments needed
                    _shift[shftdx].xfade = true;
                    ph = ceil (ph / dp);
                    if(ph<1) ph=1; 
                    r2 = r1 - ph * dr;
                    if (r2 < 0) r2 += _ipsize;
                }
                else if (ph + dp < 0.5f)
                {
                    // Jump forward by 'dr' frames and crossfade.
                    _shift[shftdx].xfade = true;
                    ph = ceil (ph / dp);
                    if(ph>=0)
                        ph=-1; 
                    else if(ph < -32)
                        ph = -32;
                    r2 = r1 - ph * dr; // ph < 0
                    if (r2 >= _ipsize) r2 -= _ipsize;
                }
                else _shift[shftdx].xfade = false;

                //toggle active
                if (_shift[shftdx].active == -1)
                {
                    //fade out this shifter
                    _shift[shftdx].active = -2;
                    _shift[shftdx].gain = 0;
                }
                else if (_shift[shftdx].active == -2)
                {
                    //shifter is faded out, deactivate
                    _shift[shftdx].active = 0;
                    _shift[shftdx].g = 0;
                }
                // recalculate gain/pan stepsize
                dr = (_shift[shftdx].gain - _shift[shftdx].g)/(_frsize);
                if (dr != 0 && (dr < DENORMAL && dr > -DENORMAL))
                {
                    dr = 0;
                    _shift[shftdx].g = _shift[shftdx].gain;
                }
                _shift[shftdx].gainstep = dr;
                dr = (_shift[shftdx].pan - _shift[shftdx].p)/(_frsize);
                if (dr != 0 && (dr < DENORMAL && dr > -DENORMAL))
                {
                    dr = 0;
                    _shift[shftdx].p = _shift[shftdx].pan;
                } 
                _shift[shftdx].panstep = dr;
                // Save local state.
                _shift[shftdx].rindex1 = r1;
                _shift[shftdx].rindex2 = r2;
            }
            
        }
    }

    // Save local state.
    _frindex = fi;

    return 0;
}


void Retuner::findcycle (void)
{
    int    d, h, i, j, k;
    float  f, m, t, x, y, z;
    int p;  

    d = _upsamp ? 2 : 1;
    h = _fftlen / 2;
    j = _ipindex - d*_fftlen;
    k = _ipsize - 1;
    p = ((_ipindex)>>_ds)-0;//estimate corresponds to middle of fft window
    for (i = 0; i < _fftlen; i++)
    {
        _fftTdata [i] = _fftTwind [i] * _ipbuff [j & k];
        j += d;
    }
    fftwf_execute_dft_r2c (_fwdplan, _fftTdata, _fftFdata);    
    f = _fsamp / (_fftlen * 3e3f);
    for (i = 0; i < h; i++)
    {
        x = _fftFdata [i][0];
        y = _fftFdata [i][1];
        m = i * f;
        _fftFdata [i][0] = (x * x + y * y) / (1 + m * m);
        _fftFdata [i][1] = 0;
    }
    _fftFdata [h][0] = 0;
    _fftFdata [h][1] = 0;
    fftwf_execute_dft_c2r (_invplan, _fftFdata, _fftTdata);    
    t = _fftTdata [0] + 0.1f;
    for (i = 0; i < h; i++) _fftTdata [i] /= (t * _fftWcorr [i]);
    x = _fftTdata [0];
    for (i = 4; i < _ifmax; i += 4)
    {
        y = _fftTdata [i];
        if (y > x) break;
        x = y;
    }
    i -= 4;
    _cycle[p] = 0;
    if (i >= _ifmax) return;
    if (i <  _ifmin) i = _ifmin;
    x = _fftTdata [--i];
    y = _fftTdata [++i];
    m = 0;
    j = 0;
    while (i <= _ifmax)
    {
        t = y * _fftWcorr [i];
        z = _fftTdata [++i];
        if ((t >  m) && (y >= x) && (y >= z) && (y > 0.8f))
        {
            j = i - 1;
            m = t;
        }
        x = y;
        y = z;
    }
    if (j)
    {
        x = _fftTdata [j - 1];
        y = _fftTdata [j];
        z = _fftTdata [j + 1];
        _cycle[p] = j + 0.5f * (x - z) / (z - 2 * y + x - 1e-9f);
    }
}


void Retuner::finderror (void)
{
    int    i, m, im;
    float  a, am, d, dm, f;

    if (!_notemask)
    {
        _error = 0;
        _lastnote = -1;
        return;
    }

    i = (int)_ipindex>>_ds;
    f = log2f (_fsamp / (_cycle[i] * _refpitch));
    dm = 0;
    am = 1;
    im = -1;
    for (i = 0, m = 1; i < 12; i++, m <<= 1)
    {
        if (_notemask & m)
        {
            d = f - (i - 9) / 12.0f;
            d -= floorf (d + 0.5f);
            a = fabsf (d);
            if (i == _lastnote) a -= _notebias;
            if (a < am)
            {
                am = a;
                dm = d;
                im = i;
            }
        }
    }
    
    if (_lastnote == im)
    {
        _error += _corrfilt * (dm - _error);
    }
    else
    {
        _error = dm;
        _lastnote = im;
    }

    // For display only.
    _notebits |= 1 << im;
}


float Retuner::cubic (float *v, float a)
{
    float b, c;

    b = 1 - a;
    c = a * b;
    return (1.0f + 1.5f * c) * (v[1] * b + v[2] * a)
	    - 0.5f * c * (v[0] * b + v[1] + v[2] + v[3] * a);
}
