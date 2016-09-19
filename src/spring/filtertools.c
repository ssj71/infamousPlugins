#include<stdint.h>
#include<math.h>
#include<stdio.h>

#define TEST

#define PI 3.1415926535897932384626433832795

//TODO: maybe this whole library should use doubles at least for filter calculators

void cart2polar(double re, double im, double* mag, double* ang)
{
    *mag = sqrt(re*re + im*im);
    *ang = atan2(im,re);
}

void polar2cart(double mag, double ang, double* re, double* im)
{
    *re = mag*cos(ang);
    *im = mag*sin(ang);
}

//uses pre-warped bilinear transform to map poles/zeros to the z plane
// note that this reqires you to add a zero at (z+1) if no other zeros
//res - real part of s-domain pole or zero
//ims - imaginary part of s-domain pole or zero
//Ts - sample time
//rez - returned real part of z-domain zero (numerator)
//imz - returned imaginary part of z-domain zero
void tustins2z(double res, double ims, double Ts, double* rez, double* imz)
{
    double mag, ang, magd, angd;
    cart2polar(res,ims,&mag,&ang);
    double warp = mag/tan(mag*Ts/2.0); //w0/(tan(w0T/2))
    //(a - warp)/(a + warp);
    cart2polar(res+warp,ims,&mag,&ang);
    cart2polar(res-warp,ims,&magd,&angd);
    polar2cart(mag/magd,ang-angd,rez,imz);
}

//uses matched z transform to map poles/zeros to the z plane
void s2z(double res, double ims, double Ts, double* rez, double* imz)
{
    *rez = exp(res*Ts)*cos(ims*Ts);
    *imz = exp(res*Ts)*sin(ims*Ts);
}

//good ol' fasioned convolution by the definition
//f - signal 1
//nf - length of signal 1
//g - signal 2
//ng - length of signal 2
//h - output buffer, requires sufficient length (nf+ng-1)
void convolve(float* f, uint8_t nf, float* g, uint8_t ng, float* h)
{
    uint16_t t, tau;
    uint8_t ubound, lbound;
    for(t=0; t<ng+nf-1; t++)
    {
        h[t] = 0;
        lbound = ((1+(int32_t)t-ng)<=0)?0:(t-ng+1);
        ubound = (t<(nf-1))?t:(nf-1);
        //printf("%i %i %i, ",t,lbound,ubound);
        for(tau=lbound; tau<=ubound; tau++)
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
    lbound = ((1+(int32_t)t-ng)<=0)?0:(t-ng+1);
    ubound = (t<(nf-1))?t:(nf-1);
    for(tau=lbound; tau<=ubound; tau++)
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
// recursion isn't fast so probably shouldn't use this in RT
void convolve_in_place(float* f, uint8_t nf, float* g, uint8_t ng)
{
    _cip(f,nf,g,ng,0);
}

//return magnitude of digital FIR filter at freq_hz
//f - filter coefficients
//nf - number of filter taps
//Ts - sample time
//freq_hz - frequency (hz) to calculate magnitude at
float magnitude(float* f, uint8_t nf, float Ts, float freq_hz)
{
    uint8_t i;
    float re, im, ang;
    double red, imd;
    //z^-1 = e^(-jwT);
    //mag =  ||f[0] + f[1]e^(-jwT) + f[1]e^(-jw2T) +... f[n-1]e^(-jw(n-1)T)||
    re = f[0];
    im = 0;
    ang = 2*PI*freq_hz*Ts;
    for(i=1; i<nf; i++)
    {
        polar2cart(f[i], ang*i, &red, &imd);
        re += red;
        im += imd;
    }
    cart2polar(re,im,&red,&imd);
    return (float)red;
}

//shift zero (z-domain) for new sampling frequency
//this doesn't account for prewarp (yet)
//re/im zero - zero/pole to shift
//oldTs - sample time filter was designed to
//newTs - new sample time
//re/im - returned shifted zero
//I don't know if this really works or not
void resample_zero(float rezero, float imzero, float oldTs, float newTs, float* re, float* im)
{
    double ang, mag, red,imd;
    cart2polar(rezero,imzero,&mag,&ang);
    ang *= newTs/oldTs;
    polar2cart(mag,ang,&red,&imd);
    *re = red;
    *im = imd;
}

//discrete time (z-plane) zero pole unity-frequency to filter coefficients conversion
//this does not account for prewarp
void dzpuf2filter(float* rezeros, float*imzeros,  uint8_t nzeros, float* repoles, float* impoles,  uint8_t npoles, float unityfreq, float zpTs, float filterTs,  float* filternum, float* filterden)
{
    //this function is the one I'll use, we'll "resample" the zeros/poles in the digital domain
    // I don't think I want to do this (because of prewarp) just design analog and transform
    uint16_t i,nn,nd;
    float a,b,c;
    float poly[3];
    float re, im;

    nn=1;
    filternum[0] = 1;//start with a 1 so that polynomial starts building
    //might need to worry about prewarp someday w' = 2/T *tan(wT/2)
    for(i=0; i<nzeros; i++)
    {
        resample_zero(rezeros[i],imzeros[i],zpTs,filterTs,&re,&im);
        if(imzeros[i])
        {
            //complex, adds pair
            poly[0] = 1;
            poly[1] = -2*re;
            poly[2] = re*re + im*im;

            convolve_in_place(poly,3,filternum,nn);
            nn+=2;
            //printf("zero is %f %fi, poly is %f %f %f \n",rezeros[i],imzeros[i],poly[0],poly[1],poly[2]);
        }
        else
        {
            //real, single zero
            poly[0] = 1;
            poly[1] = -re;

            convolve_in_place(poly,2,filternum,nn);
            nn+=1;
            //printf("zero is %f %fi, poly is %f %f \n",rezeros[i],imzeros[i],poly[0],poly[1]);
        }
    }

    nd=1;
    filterden[0] = 1;//start with a 1 so that polynomial starts building
    //might need to worry about prewarp someday w' = 2/T *tan(wT/2)
    for(i=0; i<npoles; i++)
    {
        resample_zero(repoles[i],impoles[i],zpTs,filterTs,&re,&im);
        if(impoles[i])
        {
            //complex, adds pair
            poly[0] = 1;
            poly[1] = -2*re;
            poly[2] = re*re + im*im;

            convolve_in_place(poly,3,filterden,nd);
            nd+=2;
            //printf("pole is %f %fi, poly is %f %f %f \n",repoles[i],impoles[i],poly[0],poly[1],poly[2]);
        }
        else
        {
            //real, single zero
            poly[0] = 1;
            poly[1] = -re;

            convolve_in_place(poly,2,filterden,nd);
            nd+=1;
            //printf("pole is %f %fi, poly is %f %f\n",repoles[i],impoles[i],poly[0],poly[1]);
        }
    }

    b = magnitude(filternum,nn,filterTs,unityfreq);
    a = magnitude(filterden,nd,filterTs,unityfreq);
    c = a/b;//inverse of magnitude
    //printf("%f %i %i\n",c,nn,nd);
//printf("%f %fz^-1 %fz^-2 %fz^-3 \n-----------------------------------------------\n%f %fz^-1 %fz^-2 %fz^-3\n\n",filternum[0], filternum[1],filternum[2],filternum[3],filterden[0],filterden[1],filterden[2],filterden[3]);

    for(i=0; i<nn; i++)
    {
        filternum[i]*=c;
//printf("%f %fz^-1 %fz^-2 %fz^-3 \n-----------------------------------------------\n%f %fz^-1 %fz^-2 %fz^-3\n\n",filternum[0], filternum[1],filternum[2],filternum[3],filterden[0],filterden[1],filterden[2],filterden[3]);
    }
}

//continuous time or (s-plane) zero pole unity-frequency to filter coefficient conversion
//re/im zeros - arrays of zeros parts (note to only include 1 of each complex pair)
//nzeros - length of zero arrays
//re/im poles - arrays of poles parts (note to only include 1 of each complex pair)
//npoles - length of pole arrays
//unityfreq = frequency (hz) where filter should have gain == 1
//Ts - sample time
//buf - memory buffer for working, must be larger than returned num and den
//filternum - returned numerator coefficients of resulting filter
//filterden - returned denominator coefficients of resulting filter
void czpuf2filter(float* rezeros, float*imzeros,  uint8_t nzeros, float* repoles, float* impoles,  uint8_t npoles, float unityfreq, float Ts,  float* buf, float* filternum, float* filterden)
{
    //gameplan is to convert zeros and poles to z plane, create residuals, convolve the polynomial coefficients, then set the gain to unity at the specified frequency
    uint8_t i,j,nn,nd;
    float a,b,c;
    float poly[3];
    double re, im;

    nn=1;
    filternum[0] = 1;//start with a 1 so that polynomial starts building
    for(i=0; i<nzeros; i++)
    {
        tustins2z(rezeros[i],imzeros[i],Ts,&re,&im); //use bilinear transform
        if(imzeros[i])
        {
            //complex, adds pair
            poly[0] = 1;
            poly[1] = -2*re;
            poly[2] = re*re + im*im;

            convolve(poly,3,filternum,nn,buf);
            for(j=0; j<nn; j++)
                filternum[j] = buf[j];
            nn+=2;
            printf("zero is %f %fi, poly is %f %f %f \n",rezeros[i],imzeros[i],poly[0],poly[1],poly[2]);
        }
        else
        {
            //real, single zero
            poly[0] = 1;
            poly[1] = -re;

            convolve(poly,2,filternum,nn,buf);
            for(j=0; j<nn; j++)
                filternum[j] = buf[j];
            nn+=1;
            printf("zero is %f %fi, poly is %f %f \n",rezeros[i],imzeros[i],poly[0],poly[1]);
        }
    }
    if(!nzeros)
    {
        //bilinear transform always has at least a zero at (z + 1)
        filternum[0] = 1;
        filternum[1] = 1;
        nn = 2;
    }

    nd=1;
    filterden[0] = 1;//start with a 1 so that polynomial starts building
    //might need to worry about prewarp someday w' = 2/T *tan(wT/2)
    for(i=0; i<npoles; i++)
    {
        tustins2z(repoles[i],impoles[i],Ts,&re,&im);
        if(impoles[i])
        {
            //complex, adds pair
            poly[0] = 1;
            poly[1] = -2*re;
            poly[2] = re*re + im*im;

            convolve(poly,3,filterden,nd,buf);
            for(j=0; j<nd; j++)
                filterden[j] = buf[j];
            nd+=2;
            printf("pole is %f %fi, poly is %f %f %f \n",repoles[i],impoles[i],poly[0],poly[1],poly[2]);
        }
        else
        {
            //real, single zero
            poly[0] = 1;
            poly[1] = -re;

            convolve(poly,2,filterden,nd,buf);
            for(j=0; j<nd; j++)
                filterden[j] = buf[j];
            nd+=1;
            printf("pole is %f %fi, poly is %f %f \n",repoles[i],impoles[i],poly[0],poly[1]);
        }
    }
    if(!npoles)
    {
        //bilinear transform always has at least a zero at (z + 1)
        filterden[0] = 1;
        filterden[1] = 1;
        nd = 2;
    }

    // TODO; remove zeros and poles that cancel? will need to return ncoeff

    //adjust magnitude to get correct gain
    b = magnitude(filternum,nn,Ts,unityfreq);
    a = magnitude(filterden,nd,Ts,unityfreq);
    c = a/b;//inverse of magnitude
    for(i=0; i<nn; i++)
    {
        filternum[i]*=c;
    }
}

//apply a digital filter to a buffer
//num - numerator coefficients
//numsize - number of coefficients in numerator
//den - denominator coefficients
//densize - number of coefficients in denominator
//in - array index for input in buf note this assumes buffer is a 2^16 array
//out - array index for output in buf
//buf - array containing input and output samples
void filternate(float* num, uint8_t numsize, float*den, uint8_t densize, uint16_t in, uint16_t out, float* buf)
{
    uint16_t i;
    buf[out] = 0;
    for(i=0; i<numsize; i++)
    {
        buf[out] += (float)num[i]*buf[in-i];
    }
    for(i=1; i<densize; i++)
    {
        buf[out] += (float)den[i]*buf[out-i];
    }
}

//apply a multi-tap digital delay
//taps - gains for the taps
//dels - delay lengths (samples) for taps
//ntaps - number of taps
//in - array index for input in buf note this assumes buffer is a 2^16 array
//out - array index for output in buf
//buf - array containing input and output samples
void delaynate(float* taps, uint16_t* dels, uint8_t ntaps, uint16_t in, uint16_t out, float* buf)
{
    uint16_t i;
    buf[out] = 0;
    for(i=0; i<ntaps; i++)
    {
        buf[out] += (float)taps[i]*buf[in-dels[i]];
    }
}

//using symmetry and sparseness of allpass filter banks this is just a more compact function to apply filters
//taps - gains for the numerator
//dels - delay lengths (samples) for taps
//ntaps - number of taps including 0th
//in - array index for input in buf note this assumes buffer is a 2^16 array
//out - array index for output in buf
//buf - array containing input and output samples
void apbfilternate(float* taps, uint16_t* dels, uint8_t ntaps, uint16_t in, uint16_t out, float* buf)
{
    uint16_t i;
    buf[out] = 0;
    for(i=0; i<ntaps; i++)
    {
        buf[out] += taps[i]*buf[in-dels[i]] + taps[ntaps-i]*buf[out-dels[ntaps-i]];
    }
}


//cascade a Schroeder Allpass Filter onto the previous sparse filter
//gain -
//del - delay length (samples)
//numtaps - numerator in/output array (must be numntaps+1)
//numdels - numerator in/output array (must be numntaps+1)
//numntaps - number of populated taps in the array
//dentaps - denominator in/output array (must be del+1)
//dendels - denominator in/output array (must be del+1)
//denntaps - number of populated taps in the array
void schroder(float gain, uint16_t del, float* taps, float* dels, uint8_t *ntaps)
{
	uint16_t i;
	num[0] = -g;
	/* I'll do it later, just using a matlab script now
	if(*ntaps)
	for(i=1,i<del,i++)
	{
		num[i] = 0;
	}
	*/

}


//cheby

//butter

//find out array sizes necessary for using butter()
//order - number of poles
//type - filter type (use enum)
//bufsize - returns minimum array size required for work
//num - returns minimum array size for numerator of specified filter
//den - returns minimum array size for denominator of specified filter
void butterSize(uint8_t order, FILTERTYPE type, uint8_t *bufsize, uint8_t *numsize, uint8_t *densize)
{

    switch(type)
    {
    case LPF:
        *bufsize = order;
        *numsize = 2;
        *densize = order+1;
        return;
    case HPF:
        *bufsize = 2*order;
        *numsize = order;
        *densize = order+1;
        return;
    default:
        *bufsize = order;
        *numsize = 2;
        *densize = order+1;
        return;

    }
}

//design an analog butterworth filter
//order - number of poles
//cutoff - cutoff frequency (hz)
//type - filter type (use enum)
//buf - memory space for work (must be > order*2)
//num - numerator of resulting difference function (must be > 2)
//den - denominator of resulting difference function (must be > order+1)
void butter(uint8_t order, float cutoff, FILTERTYPE type, float Ts, float* buf, float* num, float* den)
{
    float *polesRe = buf;
    float *polesIm = &buf[order/2+1];
    float *zerosRe = &buf[order+2];
    float *zerosIm = &buf[3*order/2 + 2];
    float tmp1, tmp2;
    uint8_t i;
    switch(type)
    {
    case LPF:
    {
        for(i=1; i<=order/2; i++)
        {
            polesRe[i-1] = cutoff*2.0*PI*cos(PI*(2.0*k+order-1.0)/(2.0*order));
            polesIm[i-1] = cutoff*2.0*PI*sin(PI*(2.0*k+order-1.0)/(2.0*order));
        }
        if(order%2)
        {
            //add odd pole
            polesRe[i-1] = -cutoff*2.0*PI;
            polesIm[i-1] = 0;
        }
        czpuf2filter(0,0,0,polesRe,polesIm,i,cutoff/2,Ts,buf,num,den);
        break;
    }
    case HPF:
    {
        for(i=1; i<=order/2; i++)
        {
            //I'm not sure this makes sense, just add zeros for lpf->hpf
            //tmp1 = cos(PI*(2.0*k+order-1.0)/(2.0*order));
            //tmp2 = sin(PI*(2.0*k+order-1.0)/(2.0*order));
            //polesRe[i-1] = -cutoff*2.0*PI*tmp1/(tmp1*tmp1-tmp2*tmp2);
            //polesIm[i-1] = cutoff*2.0*PI*tmp2/(tmp1*tmp1-tmp2*tmp2);
            polesRe[i-1] = cutoff*2.0*PI*cos(PI*(2.0*k+order-1.0)/(2.0*order));
            polesIm[i-1] = cutoff*2.0*PI*sin(PI*(2.0*k+order-1.0)/(2.0*order));
            //add 2 zeros (1 pole adds complex pair)
            zerosRe[2*i-2] = zerosRe[2*i-1] = 0;
            zerosIm[2*i-2] = zerosIm[2*i-1] = 0;
        }
        if(order%2)
        {
            //add odd zero & pole
            polesRe[i-1] = -cutoff*2.0*PI;
            polesIm[i-1] = 0;
            zerosRe[2*i-2] = 0;
            zerosIm[2*i-2] = 0;
        }
        czpuf2filter(zerosRe,zerosIm,i,polesRe,polesIm,i,cutoff/2,Ts,buf,num,den);
        break;
    }
    default:
        return;
    }
}

//sparse tf's always have dels and taps sorted by delay
void printsparsetf(float *numtaps, uint16_t *numdels, uint8_t numntaps, float* dentaps, uint16_t *dendels, uint8_t denntaps)
{
    uint16_t i,j=0;
    uint16_t nnum = numdels[numntaps];
    uint16_t nden = dendels[denntaps];
    for(i=0; i<nnum-1; i++)
    	if(i==numdels[j])
			printf(" %f z^%i  +",numtaps[j++],nnum-i-1);
    printf(" %f\n",numtaps[j]);
    for(i=0; i<numntaps; i++)
        printf("-----------");
    printf("-----------\n");
    j = 0;
    for(i=0; i<nden-1; i++)
    	if(i==numdels[j])
			printf(" %f z^%i  +",dentaps[j++],nden-i-1);
    printf(" %f\n",dentaps[j]);

}

void printtf(float *num, uint8_t nnum, float* den, uint8_t nden)
{
    uint8_t i;
    for(i=0; i<nnum-1; i++)
        printf(" %f z^%i  +",num[i],nnum-i-1);
    printf(" %f\n",num[i]);
    for(i=0; i<nnum; i++)
        printf("-----------");
    printf("-----------\n");
    for(i=0; i<nden-1; i++)
        printf(" %f z^%i  +",den[i],nden-i-1);
    printf(" %f\n",den[i]);

}


//for testing
#define TEST
#ifdef TEST
void main()
{
    /*
    	float a = -20000;
    	float b = 0;
    	float c,d;
    	s2z(a,b,1.0/44100,&c,&d);
    	printf("%f %f\n",c,d);
    */

    float rezeros[] = {-2};
    float imzeros[] = {0};

    float repoles[] = {-1,3};
    float impoles[] = {0,4};
    /*
    float rezeros[] = {-3.3011e+04,1.1251e+03};
    float imzeros[] ={6.9032e+04,4.7615e+04};

    float repoles[] = {-1.1661e+03,-5.8331e+03};
    float impoles[] = {3.8233e+04,2.0143e+04};
    */

    float b[5], a[5];//5 coeff == 4 roots!
    float buf[5];
    czpuf2filter(rezeros,imzeros,1,repoles,impoles,2,20000,1.0/44100,buf,b,a);
    printtf(b,2,a,4);

}
#endif
