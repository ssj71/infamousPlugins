// -----------------------------------------------------------------------
//
//  Copyright (C) 2014-2111 Spencer Jackson <ssjackson71@gmail.com>
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


//  This code is mostly written by Jeff Glatt based on original code from Fons Adriaensen


#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "retuner.h"
#include "fftw3.h"

#ifdef __cplusplus
extern "C" {
#endif

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
    float           Latency;//latency in fragments

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

//set latency in samples
void RetunerSetLatency(TUNERHANDLE tune, unsigned int samp)
{
	((Retuner *)tune)->Latency = samp/((Retuner *)tune)->Frsize;
}

//get latency in samples
unsigned int RetunerGetLatency(TUNERHANDLE tune)
{
   return ((Retuner *)tune)->Latency*((Retuner *)tune)->Frsize;
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
		tune->Corroffs = 0.0f;
		tune->Notemask = 0xFFF;

		if (fsamp < 64000)
		{
			// At 44.1 and 48 kHz resample to double rate
			//tune->Upsamp = 1;
			//tune->Ipsize = 4096;
			tune->Ipsize = 2048;
			tune->Fftlen = 2048;
			tune->Frsize = 128;

			// Prefeed some input samples to remove delay
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
	//		tune->Notebits = 0;
			tune->Lastnote = -1;
	//		tune->Count = 0;
			tune->Cycle = tune->Frsize;
            tune->Latency = 8;
	//		tune->Error = 0.0f;
			tune->Ratio = 1.0f;
	//		tune->Xfade = false;
	//		tune->Ipindex = tune->Frindex = tune->Frcount = 0;
			tune->Rindex1 = tune->Ipsize / 2;
	//		tune->Rindex2 = 0;
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

	d = 1;
	h = tune->Fftlen / 2;
	j = tune->Ipindex;
	k = tune->Ipsize - 1;
	for (i = 0; i < tune->Fftlen; i++)
	{
		tune->FftTdata[i] = tune->FftTwind[i] * tune->Ipbuff[j++ & k];
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


			// At higher sample rates apply lowpass filter
				int		i;

				// Not implemented yet, just copy
				for (i=0; i < k; i++)
				{
					inp = tuner_get_input(tune, inp, &tune->Ipbuff[tune->Ipindex]);
					++tune->Ipindex;
				}

			// Extra samples for interpolation
			tune->Ipbuff[tune->Ipsize + 0] = tune->Ipbuff[0];
			tune->Ipbuff[tune->Ipsize + 1] = tune->Ipbuff[1];
			tune->Ipbuff[tune->Ipsize + 2] = tune->Ipbuff[2];
			if (tune->Ipindex >= tune->Ipsize) tune->Ipindex = 0;

			// Process available samples
			dr = tune->Ratio;
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
						tune->Error = 0;
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
				dr = tune->Cycle * (int)ceil((double)(tune->Frsize / tune->Cycle));//samples per fragment raised to nearest complete cycle
				dp = dr / tune->Frsize;//ratio of fragment to complete cycle (>=1)
				ph = r1 - tune->Ipindex;//how many samples left to read this period
				if (ph < 0) ph += tune->Ipsize;//wrap around buffer end

				ph = ph / tune->Frsize - tune->Latency;//fragments left to read - target (about 8 frags)
				if (ph > 0.5f)
				{
					// Jump back by 'dr' frames and crossfade.
					tune->Xfade = 1;
                    int i = (int)(ph + .5);//round to nearest fragment
					r2 = r1 - i*dr;
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
                    //keep reading from current position
					tune->Xfade = 0;
			}
		}

		// Save local state
		tune->Frindex = fi;
		tune->Rindex1 = r1;
		tune->Rindex2 = r2;
	}
}

#ifdef __cplusplus
}
#endif
