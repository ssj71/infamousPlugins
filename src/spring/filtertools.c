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
		lbound = ((1+(long)t-ng)<=0)?0:(t-ng+1);
		ubound = (t<(nf-1))?t:(nf-1);
		//printf("%i %i %i, ",t,lbound,ubound);
		for(tau=lbound;tau<=ubound;tau++)
		{
			h[t] += f[tau]*g[t-tau];
			//printf("%i %i;",tau, t-tau);
		}
		//printf("\n");
	}
}

void zpuf2filter(float* rezeros, float*imzeros,  uint8_t nzeros, float* repoles, float* impoles,  uint8_t npoles, float unityfreq, float Ts,  float* filternum, float* filterden)
{
	//gameplan is to convert zeros and poles to z plane, create residuals, convolve the polynomial coefficients, then set the gain to unity at the specified frequency
	uint8_t i;
	float a,b,c;
	float poly[3];
	float re, im;
	for(i=0;i<nzeros;i++)
	{
		s2z(rezeros[i],imzeros[i],Ts,&re,&im);
		if(imzeros[i])
		{//complex, adds pair
			poly[0] = 1;
			poly[1] = -2*re;
			poly[2] = re*re + im*im;
		}
		else
		{//real, single zero
			poly[0] = 0;
			poly[1] = 1;
			poly[2] = -re;
		}
	}
}

//for testing
void main()
{
	float a[] = {1,1,1,1,1,1,1,1};
	float b[] = {1,1,1,1,1,1,1};
	float c[20];
	convolve(a,8,b,7,c);
	
}
