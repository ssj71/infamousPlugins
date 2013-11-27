#include<stdint.h>
#include<math.h>
#include<stdio.h>


void cart2polar(float re, float im, float* mag, float* ang)
{
	*mag = sqrt(re*re + im*im);
	*ang = atan2(re,im);
}

void polar2cart(float mag, float ang, float* re, float* im)
{
	*re = mag*cos(ang);
	*im = mag*sin(ang);
}

void s2z(float res, float ims, float Ts, float* rez, float* imz)
{
	//optimizations be hanged, lets just allocate one for everything
	float magnum,angnum,magden,angden,magz,angz;
	float renum = 1 + Ts/2*res;
	float imnum = Ts/2*ims;
	float reden = 1 - Ts/2*res;
	float imden = -imnum;
	cart2polar(renum,imnum,&magnum,&angnum);
	cart2polar(reden,imden,&magden,&angden);
	magz = magnum/magden;
	angz = angnum - angden;
	polar2cart(magz,angz,rez,imz);
}

void convolve(float* f, uint8_t nf, float* g, uint8_t ng, float* h)
{
	//good ol' fasioned convolution by the definition
	uint16_t t, tau;
	uint8_t ubound, lbound;
	for(t=0;t<ng+nf-1;t++)
	{
		h[t] = 0;
		lbound = (((long)t-ng+1)<0)?0:(t-ng+1);
		ubound = (t<(nf-1))?t:(nf-1);
		for(tau=lbound;tau<ubound;tau++)
		{
			h[t] += f[tau]*g[t-tau-1];
			printf("%i %i;",tau, t-tau-1);
		}
		printf("\n");
	}
}

void zpuf2filter(float* zeros, uint8_t nzeros, float* poles, uint8_t npoles, float unityfreq, float* Ts,  float* filternum, float* filterden)
{
	//gameplan is to convert zeros and poles to z plane, create residuals, convolve the polynomial coefficients, then set the gain to unity at the specified frequency
	uint8_t i;
	for(i=0;i<nzeros;i++)
	{
		//s2z()
	}
}

//for testing
void main()
{
	float a[] = {0,0,0,0};
	float b[] = {0,0,0};
	float c[6];
	convolve(a,4,b,3,c);
	
}
