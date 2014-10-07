//Spencer Jackson
//ewham.c
#include<lv2.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

#define EWHAM_URI "http://infamousplugins.sourceforge.net/plugs.html#ewham"

#define PI 3.1415926535897932384626433832795

typedef struct _EWHAM
{
    unsigned short w;//write pointer
    unsigned short bufsize;
    unsigned short fragsize;
    double sample_freq;
    
    float *buf;
    float *xfade;

    float *input_p;
    float *output_l_p;
    float *output_r_p;
    float *drygain_p;
    float *drypan_p;
}EWHAM;

float wooshy(WOOSHER *woosh,float* buf, unsigned short w)
{
    
}

void run_ewham(LV2_Handle handle, uint32_t nframes)
{
    EWHAM* plug = (EWHAM*)handle;
    uint32_t i,j,k,t,chunk=0;
    double slope = 0;
return;
}

LV2_Handle init_ewham(const LV2_Descriptor *descriptor,double sample_freq, const char *bundle_path,const LV2_Feature * const* host_features)
{
    EWHAM* plug = malloc(sizeof(EWHAM));

    unsigned short tmp;
    plug->sample_freq = sample_freq; 
    tmp = 0x2000;//14 bits
    if(sample_freq<100000)//88.1 or 96.1kHz
        tmp = tmp>>1;//13 bits
    if(sample_freq<50000)//44.1 or 48kHz
        tmp = tmp>>1;//12 bits
    plug->bufsize = tmp;
    plug->buf = (float*)malloc((tmp+3)*sizeof(float));
    tmp = tmp>>4;
    plug->fragsize = tmp;
    plug->xfade = (float*)malloc((tmp)*sizeof(float));
    for(i=0;i<tmp;i++)
        plug->xfade[i] = .5*(1-cos(PI*i/(double)tmp));//raised cosine

    return plug;
}

void connect_ewham_ports(LV2_Handle handle, uint32_t port, void *data)
{
    EWHAM* plug = (EWHAM*)handle;
    switch(port)
    {
    case IN:         plug->input_p = (float*)data;break;
    case OUT:       plug->output_p = (float*)data;break;
    case OUTR:       plug->output_r_p = (float*)data;break;
    case DRYGAIN:    plug->drygain_p = (float*)data;break;
    case DRYPAN:     plug->drypan_p = (float*)data;break;
    case WOOSH0:     plug->woosh[0]->woosh_p = (float*)data;break;
    case GAIN0:      plug->woosh[0]->gain_p = (float*)data;break;
    case PAN0:       plug->woosh[0]->pan_p = (float*)data;break;
    case WOOSH1:     plug->woosh[1]->woosh_p = (float*)data;break;
    case GAIN1:      plug->woosh[1]->gain_p = (float*)data;break;
    case PAN1:       plug->woosh[1]->pan_p = (float*)data;break;
    case WOOSH2:     plug->woosh[2]->woosh_p = (float*)data;break;
    case GAIN2:      plug->woosh[2]->gain_p = (float*)data;break;
    case PAN2:       plug->woosh[2]->pan_p = (float*)data;break;
    case WOOSH3:     plug->woosh[3]->woosh_p = (float*)data;break;
    case GAIN3:      plug->woosh[3]->gain_p = (float*)data;break;
    case PAN4:       plug->woosh[3]->pan_p = (float*)data;break;
    default:         puts("UNKNOWN PORT YO!!");
    }
}

void cleanup_ewham(LV2_Handle handle)
{
    EWHAM* plug = (EWHAM*)handle;
    free(plug->buf);
    free(plug->xfade);
    free(plug);
}

static const LV2_Descriptor ewham_descriptor={
    EWHAM_URI,
    init_ewham,
    connect_ewham_ports,
    0,//activate
    run_ewham,
    0,//deactivate
    cleanup_ewham,
    0//extension
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index)
{
    switch (index) {
    case 0:
        return &ewham_descriptor;
    default:
        return 0;
    }
}


// -----------------------------------------------------------------------
//
//  Copyright (C) 2009-2014 Spencer Jackson <ssjackson71@gmail.com>
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

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "retuner.h"
#include "fftw3.h"


typedef struct
{
	double			_fr;
	unsigned int	_hl;
	unsigned int	_np;	
	float			Table[1];
} Resampler_table;

typedef struct
{
	float *			Buff;
	Resampler_table *	Table;
	unsigned int	InMax;
	unsigned int	Index;
	unsigned int	NRead;
	unsigned int	NZero;
	unsigned int	Phase;
	unsigned int	Pstep;
} Resampler;

typedef struct
{
	float *			Ipbuff;
	float *			Xffunc;
	float *			FftTwind;
	float *			FftWcorr;
	float *			FftTdata;
	fftwf_complex *	FftFdata;
	fftwf_plan		Fwdplan;
	fftwf_plan		Invplan;
	Resampler		Resampler;
	int				Fsamp;
	int				Ifmin, Ifmax;
	int				Fftlen;
	int				Ipsize;
	int				Frsize;
	int				Ipindex;
	int				Frindex;
	int				Frcount;

	int				Notemask;
	float			Refpitch;
	float			Notebias;
	float			Corrfilt; 
	float			Corrgain;
	float			Corroffs;

	int				Lastnote;
	int				Count;
	float			Cycle;
	float			Error;
	float			Ratio;
	float			Rindex1, Rindex2;
	unsigned short	Notebits;
	unsigned char	Xfade, Upsamp, Format;
} Retuner;

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif





static double sinc(double x)
{
	x = fabs(x);
	if (x < 1e-6) return 1.0;
	x *= M_PI;
	return sin(x) / x;
}





static double wind(double x)
{
	x = fabs(x);
	if (x >= 1.0) return 0.0f;
	x *= M_PI;
	return 0.384 + 0.500 * cos(x) + 0.116 * cos(2 * x);
}





static Resampler_table * resamplerTableCreate(double fr, unsigned int hl, unsigned int np)
{
	register Resampler_table * table;

	if ((table = (Resampler_table *)malloc(sizeof(Resampler_table) - sizeof(float) + (sizeof(float) * hl * (np + 1)))))
	{
		unsigned int  i, j;
		double        t;
		float         *p;

		table->_fr = fr;
		table->_hl = hl;
		table->_np = np;
		p = &table->Table[0];
		for (j = 0; j <= np; j++)
		{
			t = (double) j / (double) np;
			for (i = 0; i < hl; i++)
			{
				p[hl - i - 1] = (float)(fr * sinc(t * fr) * wind(t / hl));
				t += 1;
			}
			p += hl;
		}
	}
	
	return table;
}





static void resamplerTableDestroy(Resampler_table * table)
{
	if (table) free(table);
}





static void resamplerClear(register Resampler * resamp)
{
	resamplerTableDestroy(resamp->Table);
	resamp->Table = 0;

	if (resamp->Buff) free(resamp->Buff);
	resamp->Buff = 0;
}





static unsigned int gcd(unsigned int a, unsigned int b)
{
	if (a == 0) return b;
	if (b == 0) return a;
	while (1)
	{
		if (a > b)
		{
			a = a % b;
			if (a == 0) return b;
			if (a == 1) return 1;
		}
		else
		{
			b = b % a;
			if (b == 0) return a;
			if (b == 1) return 1;
		}
	}    
	return 1; 
}


static int resamplerSetup(register Resampler * resamp, unsigned int fs_inp, unsigned int fs_out, unsigned int nchan, unsigned int hlen)
{
	unsigned int       g, h, k, n, s;
	double             r, frel;

	if (hlen >= 8 && hlen <= 96)
	{
		r = (double) fs_out / (double) fs_inp;
		g = gcd(fs_out, fs_inp);
		n = fs_out / g;
		s = fs_inp / g;

		k = 0;
		if ((16 * r >= 1) && (n <= 1000))
		{
			h = hlen;
			k = 250;
			frel = 1.0 - (2.6 / hlen);
			if (r < 1) 
			{
				frel *= r;
				h = (unsigned int)(ceil(h / r));
				k = (unsigned int)(ceil(k / r));
			}
			resamp->Table = resamplerTableCreate(frel, h, n);
			resamp->Buff = (float *)malloc(sizeof(float) * nchan * (2 * h - 1 + k));
		}

		if (resamp->Table && resamp->Buff)
		{
			resamp->NRead = 2 * resamp->Table->_hl;
			resamp->InMax = k;
			resamp->Pstep = s;
			return 0;
		}
	}

	resamplerClear(resamp);
	return 1;
}





static void * tuner_get_input(register Retuner * tune, register void * inputs, register float *v)
{
	register unsigned long	offset;
	register float			value;

	switch (tune->Format & TUNERTYPE_BITSMASK)
	{
		case TUNERTYPE_8BIT:
		{
			value = (float)*((char *)inputs);
			offset = sizeof(char);
			break;
		}
		case TUNERTYPE_16BIT:
		{
			value = (float)*((short *)inputs);
			offset = sizeof(short);
			break;
		}
		case TUNERTYPE_32BIT:
		{
			value = (float)*((int32_t *)inputs);
			offset = sizeof(int32_t);
			break;
		}
		case TUNERTYPE_FLOAT:
		{
			value = (float)*((float *)inputs);
			offset = sizeof(float);
			break;
		}
#ifdef REV_DBL_SUPPORT
		case TUNERTYPE_DOUBLE:
		{
			value = (float)*((double *)inputs);
			offset = sizeof(double);
		}
#endif
	}

	*v = value;
	if (!(tune->Format & TUNERTYPE_MONOOUTPUT)) offset <<= 1;
	inputs = (char *)inputs + offset;
	return inputs;
}





static void * resamplerProcess(register Resampler * resamp, void * input, unsigned int inFrames, float * output, unsigned int outFrames, Retuner * tune)
{
	unsigned int   hl, ph, np, dp, in, nr, nz, n;
	float          *p1, *p2;

//	if (!resamp->Table) return;

	hl = resamp->Table->_hl;
	np = resamp->Table->_np;
	dp = resamp->Pstep;
	in = resamp->Index;
	nr = resamp->NRead;
	ph = resamp->Phase;
	nz = resamp->NZero;
	n = (2 * hl - nr);
	p1 = resamp->Buff + in;
	p2 = p1 + n;

	while (outFrames)
	{
		if (nr)
		{
			if (!inFrames) break;

			if (input)
			{
				input = tuner_get_input(tune, input, p2);
				nz = 0;
			}
			else
			{
				*p2 = 0;
				if (nz < 2 * hl) nz++;
			}
			nr--;
			p2++;
			inFrames--;
		}
		else
		{
			if (output)
			{
				if (nz < 2 * hl)
				{
					float *			c1;
					float *			c2;
					float *			q1;
					float *			q2;
					float			s;
					unsigned int	i;

					c1 = &resamp->Table->Table[hl * ph];
					c2 = &resamp->Table->Table[hl * (np - ph)];

					q1 = p1;
					q2 = p2;
					s = 1e-20f;
					for (i = 0; i < hl; i++)
					{
						q2--;
						s += *q1 * c1[i] + *q2 * c2[i];
						q1++;
					}

					*output++ = s - 1e-20f;
				}
				else
					*output++ = 0;
			}

			outFrames--;

			ph += dp;
			if (ph >= np)
			{
				nr = ph / np;
				ph -= nr * np;
				in += nr;
				p1 += nr;
				if (in >= resamp->InMax)
				{
					n = (2 * hl - nr);
					memcpy(resamp->Buff, p1, n * sizeof(float));
					in = 0;
					p1 = resamp->Buff;
					p2 = p1 + n;
				}
			}
		}
	}

	resamp->Index = in;
	resamp->NRead = nr;
	resamp->Phase = ph;
	resamp->NZero = nz;

	return input;
}





/*

enum { XS = 173, YS = 17, XM = 0, YM = 0, Y1 = 7, Y2 = 10 };

void tmeter::update_meter()
{
    float v0, v1;
    int k0, k1;

    v0 = v1 = RetunerGetError(tune);

    k0 = (int)(floor(86.0 + 80.0 * v0 + 0.5));
    k1 = (int)(floor(86.0 + 80.0 * v1 + 0.5));
    if (k0 < 4) k0 = 4;
    if (k0 > 168) k0 = 168;
    if (k1 < 4) k1 = 4;
    if (k1 > 168) k1 = 168;
    XSetFunction(Display, MainGc, GXcopy);
    XPutImage(Display, MeterWin, MainGc, _imag0, _k0 - 2, 0, XM + _k0 - 2, YM, 5 + _k1 - _k0, Y1); 
    _k0 = k0;
    _k1 = k1;
    XPutImage(Display, MeterWin, MainGc, _imag1, k0 - 2, 0, XM + k0 - 2, YM, 5 + k1 - k0, Y1); 
}

*/


// 12 note buttons c to b (low 12 bits of tune->Notemask)
// tune (tune->Refpitch) = 400 to 480, def 440
// bias (tune->Notebias) = 0 to 1, def 0.5
// filter (tune->Corrfilt) = 0.50 to 0.02, def 0.10 
// corr (tune->Corrgain) = 0 to 1, def 1. 
// offset (tune->Corroffs) = -2 to 2, def 0


void RetunerSetPitch(TUNERHANDLE tune, float v)
{
	((Retuner *)tune)->Refpitch = v;
}

void RetunerSetNoteBias(TUNERHANDLE tune, float v)
{
	((Retuner *)tune)->Notebias = v / 13.0f;
}

void RetunerSetFilter(TUNERHANDLE tune, float v)
{
	((Retuner *)tune)->Corrfilt = (4 * ((Retuner *)tune)->Frsize) / (v * ((Retuner *)tune)->Fsamp);
}

void RetunerSetGain(TUNERHANDLE tune, float v)
{
	((Retuner *)tune)->Corrgain = v;
}

void RetunerSetOffset(TUNERHANDLE tune, float v)
{
	((Retuner *)tune)->Corroffs = v;
}

void RetunerSetNoteMask(TUNERHANDLE tune, unsigned int k)
{
	((Retuner *)tune)->Notemask = k;
}




unsigned int RetunerGetNoteset(TUNERHANDLE tune)
{
	register unsigned int k;

	k = ((Retuner *)tune)->Notebits;
	((Retuner *)tune)->Notebits = 0;
	return k;
}





float RetunerGetError(TUNERHANDLE tune)
{
	return 12.0f * ((Retuner *)tune)->Error;
}





#define RETUNEFLAG_UPSAMPLE		0x80


void RetunerFree(TUNERHANDLE handle)
{
	register Retuner * tune;

	if ((tune = handle))
	{
		resamplerClear(&tune->Resampler);
		if (tune->Ipbuff) free(tune->Ipbuff);
		if (tune->Xffunc) free(tune->Xffunc);
		fftwf_free(tune->FftTwind);
		fftwf_free(tune->FftWcorr);
		fftwf_free(tune->FftTdata);
		fftwf_free(tune->FftFdata);
		fftwf_destroy_plan(tune->Fwdplan);
		fftwf_destroy_plan(tune->Invplan);
		free(tune);
	}
}





TUNERHANDLE RetunerAlloc(int fsamp, unsigned char format)
{
	register Retuner * tune;
	int   i, h;
	float t, x, y;

	if ((tune = (Retuner *)malloc(sizeof(Retuner))))
	{
		memset(tune, 0, sizeof(Retuner));

		tune->Fsamp = fsamp;
		tune->Format = format;
		tune->Refpitch = 440.0f;
		tune->Corrfilt = tune->Corrgain = 1.0f;
//		tune->Corroffs = tune->Notebias = 0.0f;
		tune->Notemask = 0xFFF;

		if (fsamp < 64000)
		{
			// At 44.1 and 48 kHz resample to double rate
			//tune->Upsamp = 1;
			//tune->Ipsize = 4096;
			tune->Upsamp = 0;//ssj
			tune->Ipsize = 2048;
			tune->Fftlen = 2048;
			tune->Frsize = 128;
			//if (resamplerSetup(&tune->Resampler, 1, 2, 1, 32)) goto fail; // 32 is medium quality

			// Prefeed some input samples to remove delay
//			resamplerProcess(&tune->Resampler, 0, tune->Resampler.Table->_hl * 2 - 1, 0, 0, tune);
		}
		else if (fsamp < 128000)
		{
			// 88.2 or 96 kHz.
//			tune->Upsamp = false;
			tune->Ipsize = tune->Fftlen = 4096;
			tune->Frsize = 256;
		}
		else
		{
			// 192 kHz, double time domain buffers sizes
//			tune->Upsamp = false;
			tune->Ipsize = tune->Fftlen = 8192;
			tune->Frsize = 512;
		}

		// Accepted correlation peak range, corresponding to 60..1200 Hz
		tune->Ifmin = fsamp / 1200;
		tune->Ifmax = fsamp / 60;

		// Alloc various buffers
		tune->Ipbuff = (float *)malloc(sizeof(float) * (tune->Ipsize + 3));			// Resampled or filtered input
		tune->Xffunc = (float *)malloc(sizeof(float) * tune->Frsize);				// Crossfade function
		tune->FftTwind = (float *)fftwf_malloc(tune->Fftlen * sizeof (float));		// Window function 
		tune->FftWcorr = (float *)fftwf_malloc(tune->Fftlen * sizeof (float));		// Autocorrelation of window 
		tune->FftTdata = (float *)fftwf_malloc(tune->Fftlen * sizeof (float));		// Time domain data for FFT
		tune->FftFdata = (fftwf_complex *) fftwf_malloc((tune->Fftlen / 2 + 1) * sizeof (fftwf_complex));

		if (!tune->Ipbuff || !tune->Xffunc || !tune->FftTwind || !tune->FftWcorr || !tune->FftTdata || !tune->FftFdata)
		{
fail:		RetunerFree(tune);
			tune = 0;
		}
		else
		{
			// FFTW3 plans
			tune->Fwdplan = fftwf_plan_dft_r2c_1d(tune->Fftlen, tune->FftTdata, tune->FftFdata, FFTW_ESTIMATE);
			tune->Invplan = fftwf_plan_dft_c2r_1d(tune->Fftlen, tune->FftFdata, tune->FftTdata, FFTW_ESTIMATE);

			// Clear input buffer.
			memset(tune->Ipbuff, 0, (tune->Ipsize + 1) * sizeof(float));

			// Create crossfade function, half of raised cosine.
			for (i = 0; i < tune->Frsize; i++) tune->Xffunc[i] = 0.5 * (1 - cos((M_PI * i / tune->Frsize)));

			// Create window, raised cosine.
			for (i = 0; i < tune->Fftlen; i++) tune->FftTwind[i] = 0.5 * (1 - cos((2 * M_PI * i / tune->Fftlen)));

			// Compute window autocorrelation and normalise it.
			fftwf_execute_dft_r2c(tune->Fwdplan, tune->FftTwind, tune->FftFdata);    
			h = tune->Fftlen / 2;
			for (i = 0; i < h; i++)
			{
				x = tune->FftFdata[i][0];
				y = tune->FftFdata[i][1];
				tune->FftFdata[i][0] = x * x + y * y;
				tune->FftFdata[i][1] = 0;
			}
			tune->FftFdata[h][0] = 0;
			tune->FftFdata[h][1] = 0;
			fftwf_execute_dft_c2r(tune->Invplan, tune->FftFdata, tune->FftWcorr);    
			t = tune->FftWcorr[0];
			for (i = 0; i < tune->Fftlen; i++) tune->FftWcorr[i] /= t;

			// Initialise all counters and other state
			tune->Lastnote = -1;
			tune->Cycle = tune->Frsize;
			tune->Ratio = 1.0f;
			tune->Rindex1 = tune->Ipsize / 2;
		}
	}

	return tune;
}





static void * store_output(register Retuner * tune, register void * outputs, register float v)
{
	register unsigned long	offset;

	switch (tune->Format & TUNERTYPE_BITSMASK)
	{
		case TUNERTYPE_8BIT:
		{
			*((char *)outputs) = (char)v;
			offset = sizeof(char);
			break;
		}
		case TUNERTYPE_16BIT:
		{
			*((short *)outputs) = (short)v;
			offset = sizeof(short);
			break;
		}
		case TUNERTYPE_32BIT:
		{
			*((int32_t *)outputs) = (int32_t)v;
			offset = sizeof(int32_t);
			break;
		}
		case TUNERTYPE_FLOAT:
		{
			*((float *)outputs) = (float)v;
			offset = sizeof(float);
			break;
		}
#ifdef REV_DBL_SUPPORT
		case TUNERTYPE_DOUBLE:
		{
			*((double *)outputs) = (double)v;
			offset = sizeof(double);
		}
#endif
	}

	if (!(tune->Format & TUNERTYPE_MONOOUTPUT)) offset <<= 1;
	outputs = (char *)outputs + offset;
	return outputs;
}





static void findcycle(register Retuner * tune)
{
	int    d, h, i, j, k;
	float  f, m, t, x, y, z;

	d = tune->Upsamp ? 2 : 1;
	h = tune->Fftlen / 2;
	j = tune->Ipindex;
	k = tune->Ipsize - 1;
	for (i = 0; i < tune->Fftlen; i++)
	{
		tune->FftTdata[i] = tune->FftTwind[i] * tune->Ipbuff[j & k];
		j += d;
	}
	fftwf_execute_dft_r2c(tune->Fwdplan, tune->FftTdata, tune->FftFdata);    
	f = tune->Fsamp / (tune->Fftlen * 2.5e3f);
	for (i = 0; i < h; i++)
	{
		x = tune->FftFdata[i][0];
		y = tune->FftFdata[i][1];
		m = i * f;
		tune->FftFdata[i][0] = (x * x + y * y) / (1 + m * m);
		tune->FftFdata[i][1] = 0;
    }
	tune->FftFdata[h][0] = 0;
	tune->FftFdata[h][1] = 0;
	fftwf_execute_dft_c2r(tune->Invplan, tune->FftFdata, tune->FftTdata);    
	t = tune->FftTdata[0] + 0.1f;
	for (i = 0; i < h; i++) tune->FftTdata[i] /= (t * tune->FftWcorr[i]);
	x = tune->FftTdata[0];
	for (i = 4; i < tune->Ifmax; i += 4)
	{
		y = tune->FftTdata[i];
		if (y > x) break;
		x = y;
	}
	i -= 4;
	tune->Cycle = 0;
	if (i < tune->Ifmax)
	{
		if (i < tune->Ifmin) i = tune->Ifmin;
		x = tune->FftTdata[--i];
		y = tune->FftTdata[++i];
		m = j = 0;
		while (i <= tune->Ifmax)
		{
			t = y * tune->FftWcorr[i];
			z = tune->FftTdata[++i];
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
			x = tune->FftTdata[j - 1];
			y = tune->FftTdata[j];
			z = tune->FftTdata[j + 1];
			tune->Cycle = j + 0.5f * (x - z) / (z - 2 * y + x - 1e-9f);
		}
	}
}

static void finderror(register Retuner * tune)
{
	int    i, m, im;
	float  a, am, d, dm, f;

	if (!tune->Notemask)
	{
		tune->Error = 0;
		tune->Lastnote = -1;
	}
	else
	{
		//	f = log2f(tune->Fsamp / (tune->Cycle * tune->Refpitch));
		f = log((tune->Fsamp / (tune->Cycle * tune->Refpitch)))/log(2);

		dm = 0;
		am = 1;
		im = -1;
		for (i = 0, m = 1; i < 12; i++, m <<= 1)
		{
			if (tune->Notemask & m)
			{
				d = f - (i - 9) / 12.0f;
				d -= (float)floor((d + 0.5f));
				a = (float)fabs(d);
				if (i == tune->Lastnote) a -= tune->Notebias;
				if (a < am)
				{
					am = a;
					dm = d;
					im = i;
				}
			}
		}

		if (tune->Lastnote == im)
			tune->Error += tune->Corrfilt * (dm - tune->Error);
		else
		{
			tune->Error = dm;
			tune->Lastnote = im;
		}

		// For display only.
		tune->Notebits |= 1 << im;
	}
}


static float cubic(float * v, float a)
{
	register float	b, c;

	b = 1 - a;
	c = a * b;
	return (1.0f + 1.5f * c) * (v[1] * b + v[2] * a)
	    - 0.5f * c * (v[0] * b + v[1] + v[2] + v[3] * a);
}


// Pitch shifting is done by resampling the input at the
// required ratio, and eventually jumping forward or back
// by one or more pitch period(s). Processing is done in
// fragments of 'tune->Frsize' frames, and the decision to jump
// forward or back is taken at the start of each fragment.
// If a jump happens we crossfade over one fragment size. 
// Every 4 fragments a new pitch estimate is made. Since
// tune->Fftsize = 16 * tune->Frsize, the estimation window moves
// by 1/4 of the FFT length.

void RetunerProcess(TUNERHANDLE handle, void * inp, void * out, unsigned int nfram)
{
	register Retuner *	tune;
	int					fi;
	float				r1, r2;

	if ((tune = handle))
	{
		fi = tune->Frindex;  // Write index in current fragment.
		r1 = tune->Rindex1;  // Read index for current input frame.
		r2 = tune->Rindex2;  // Second read index while crossfading. 

		// No assumptions are made about fragments being aligned
		// with process() calls, so we may be in the middle of
		// a fragment here

		while (nfram)
		{
			int		k;
			float	ph, dp, dr;

			// Don't go past the end of the current fragment
			k = tune->Frsize - fi;
			if (nfram < k) k = nfram;
			nfram -= k;

			// At 44.1 and 48 kHz upsample by 2
			if (tune->Upsamp)
			{
				inp = resamplerProcess(&tune->Resampler, inp, k, tune->Ipbuff + tune->Ipindex, k * 2, tune);
				tune->Ipindex += 2 * k;
			}

			// At higher sample rates apply lowpass filter
			else
			{
				int		i;

				// Not implemented yet, just copy
				for (i=0; i < k; i++)
				{
					inp = tuner_get_input(tune, inp, &tune->Ipbuff[tune->Ipindex]);
					++tune->Ipindex;
				}
			}

			// Extra samples for interpolation
			tune->Ipbuff[tune->Ipsize + 0] = tune->Ipbuff[0];
			tune->Ipbuff[tune->Ipsize + 1] = tune->Ipbuff[1];
			tune->Ipbuff[tune->Ipsize + 2] = tune->Ipbuff[2];
			if (tune->Ipindex >= tune->Ipsize) tune->Ipindex = 0;

			// Process available samples
			dr = tune->Ratio;
			if (tune->Upsamp) dr *= 2;
			if (tune->Xfade)
			{
				// Interpolate and crossfade
				while (k--)
				{
					int		i;
					float	u1, u2, v;

					i = (int)r1;
					u1 = cubic(tune->Ipbuff + i, r1 - i);
					i = (int)r2;
					u2 = cubic(tune->Ipbuff + i, r2 - i);
					v = tune->Xffunc[fi++];

					out = store_output(tune, out, (1 - v) * u1 + v * u2);

					r1 += dr;
					if (r1 >= tune->Ipsize) r1 -= tune->Ipsize;
					r2 += dr;
					if (r2 >= tune->Ipsize) r2 -= tune->Ipsize;
				}
			}
			else
			{
				// Interpolation only.
				fi += k;
				while (k--)
				{
					int		i;

					i = (int)r1;
					out = store_output(tune, out, cubic(tune->Ipbuff + i, r1 - i));
					r1 += dr;
					if (r1 >= tune->Ipsize) r1 -= tune->Ipsize;
				}
			}

			// If at end of fragment check for jump
			if (fi == tune->Frsize) 
			{
				fi = 0;

				// Estimate the pitch every 4th fragment
				if (++tune->Frcount == 4)
				{
					tune->Frcount = 0;
					findcycle(tune);
					if (tune->Cycle)
					{
						// If the pitch estimate succeeds, find the
						// nearest note and required resampling ratio
						tune->Count = 0;
						//finderror(tune);
					}

					else if (++tune->Count > 5)
					{
						// If the pitch estimate fails, the current
						// ratio is kept for 5 fragments. After that
						// the signal is considered unvoiced and the
						// pitch error is reset
						tune->Count = 5;
						tune->Cycle = tune->Frsize;
						//tune->Error = 0;
					}

					else if (tune->Count == 2)
					{
						// Bias is removed after two unvoiced fragments
						tune->Lastnote = -1;
					}
                
					//tune->Ratio = pow(2.0, (tune->Corroffs / 12.0f - tune->Error * tune->Corrgain));
					tune->Ratio = pow(2.0, (tune->Corroffs / 12.0f ));
				}

				// If the previous fragment was crossfading,
				// the end of the new fragment that was faded
				// in becomes the current read position
				if (tune->Xfade) r1 = r2;

				// A jump must correspond to an integer number
				// of pitch periods, and to avoid reading outside
				// the circular input buffer limits it must be at
				// least one fragment size
				dr = tune->Cycle * (int)ceil((double)(tune->Frsize / tune->Cycle));
				dp = dr / tune->Frsize;
				ph = r1 - tune->Ipindex;
				if (ph < 0) ph += tune->Ipsize;
				if (tune->Upsamp)
				{
					ph /= 2;
					dr *= 2;
				}
				ph = ph / tune->Frsize + 2 * tune->Ratio - 10;
				if (ph > 0.5f)
				{
					// Jump back by 'dr' frames and crossfade.
					tune->Xfade = 1;
					r2 = r1 - dr;
					if (r2 < 0) r2 += tune->Ipsize;
				}
				else if (ph + dp < 0.5f)
				{
					// Jump forward by 'dr' frames and crossfade.
					tune->Xfade = 1;
					r2 = r1 + dr;
					if (r2 >= tune->Ipsize) r2 -= tune->Ipsize;
				}
				else
					tune->Xfade = 0;
			}
		}

		// Save local state
		tune->Frindex = fi;
		tune->Rindex1 = r1;
		tune->Rindex2 = r2;
	}
}

