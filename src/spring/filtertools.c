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

//this recursive function stores the values in tmp until all calculations
//are complete and then writes them into g[]
//naturally this requires g[] to be of sufficient size
void _cip(float* f, uint8_t nf, float* g, uint8_t ng, uint8_t t)
{
	float tmp = 0;
	uint16_t tau;
	uint8_t ubound, lbound;
	lbound = ((1+(long)t-ng)<=0)?0:(t-ng+1);
	ubound = (t<(nf-1))?t:(nf-1);
	for(tau=lbound;tau<=ubound;tau++)
	{
		tmp += f[tau]*g[t-tau];
		//printf("%i %i;",tau, t-tau);
	}
	//printf("\n");
	if(t<ng+nf-1)
	{
		_cip(f,nf,g,ng,t+1);
	}
	g[t] = tmp;
}

//in this version the result will be stored into g[];
void convolve_in_place(float* f, uint8_t nf, float* g, uint8_t ng)
{
	_cip(f,nf,g,ng,0);
}


float magnitude(float* f, uint8_t nf, float Ts, float freq_hz)
{
	uint8_t i;
	float re, im, retmp, imtmp, ang;
	//z^-1 = e^(-jwT);
	//mag =  ||f[0] + f[1]e^(-jwT) + f[1]e^(-jw2T) +... f[n-1]e^(-jw(n-1)T)||
	re = f[0];
	im = 0;
	ang = 2*PI*freq_hz*Ts;
	for(i=1;i<nf;i++)
	{
		polar2cart(f[i], ang*i, &retmp, &imtmp);
		re += retmp;
		im += imtmp;
	}
	cart2polar(re,im,&retmp,&imtmp);
	return retmp;
}

void zpuf2filter(float* rezeros, float*imzeros,  uint8_t nzeros, float* repoles, float* impoles,  uint8_t npoles, float unityfreq, float Ts,  float* filternum, float* filterden)
{
	//gameplan is to convert zeros and poles to z plane, create residuals, convolve the polynomial coefficients, then set the gain to unity at the specified frequency
	uint8_t i,n;
	float a,b,c;
	float poly[3];
	float re, im;

	n=1;
	filternum[0] = 1;//start with a 1 so that polynomial starts building
	//might need to worry about prewarp someday w' = 2/T *tan(wT/2)
	for(i=0;i<nzeros;i++)
	{
		s2z(rezeros[i],imzeros[i],Ts,&re,&im);
		if(imzeros[i])
		{//complex, adds pair
			poly[0] = 1;
			poly[1] = -2*re;
			poly[2] = re*re + im*im;
			
			convolve_in_place(poly,3,filternum,n);
			n+=3;
		}
		else
		{//real, single zero
			poly[0] = 1;
			poly[1] = -re;
			
			convolve_in_place(poly,2,filternum,n);
			n+=2;
		}
	}

	n=1;
	filterden[0] = 1;//start with a 1 so that polynomial starts building
	//might need to worry about prewarp someday w' = 2/T *tan(wT/2)
	for(i=0;i<npoles;i++)
	{
		s2z(repoles[i],impoles[i],Ts,&re,&im);
		if(impoles[i])
		{//complex, adds pair
			poly[0] = 1;
			poly[1] = -2*re;
			poly[2] = re*re + im*im;
			
			convolve_in_place(poly,3,filterden,n);
			n+=3;
		}
		else
		{//real, single zero
			poly[0] = 1;
			poly[1] = -re;
			
			convolve_in_place(poly,2,filterden,n);
			n+=2;
		}
	}


}

//for testing
void main()
{
	float a[] = {1,1,1,1,1,1,1,1};
	float b[20];
	float c[20];
	uint8_t i;
	for(i=0;i<7;i++)
	{
		b[i] = 1;
	}
	for(;i<20;i++);
	{	
		b[i] = 0;
	}
	convolve_in_place(a,8,b,7);
	
}
