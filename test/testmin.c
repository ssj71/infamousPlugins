//Spencer Jackson
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>



float findminx(float arr[])
{
	//return subsample index of minima
	float m2 = arr[3]-arr[1];
	float a,b,c;
	if(m2>0)
	{
		//minima is before sample
		a = 1.5*(-arr[0] + 3*arr[1] - 3*arr[2] + arr[3]);
		b = 2*arr[0] - 5*arr[1] + 4*arr[2] - arr[3];
		c = .5*(-arr[0] + arr[2]);

        printf("less a=%f b=%f c=%f %f\n",a,b,c,b*b-4*a*c);
        if(!a) return -c/b;
		return 1-(-b+sqrt(b*b-4*a*c))/(2*a);//its possible that this is wrong but I think b-.. will be out of domain t E[0,1]
	}
	else if(m2<0)
	{
		//minima is after sample
		a = 1.5*(-arr[1] + 3*arr[2] - 3*arr[3] + arr[4]);
		b = 2*arr[1] - 5*arr[2] + 4*arr[3] - arr[4];
		c = .5*(-arr[1] + arr[3]);

        printf("more a=%f b=%f c=%f %f\n",a,b,c,b*b-4*a*c);
        if(!a) return -c/b;
		return (-b+sqrt(b*b-4*a*c))/(2*a);//its possible that this is wrong but I think b-.. will be out of domain t E[0,1]
	}
	else return 0;
}


int main()
{ 
    //float x[] = {6.25,  2.25, .25, .25, 2.25, 6.25}; // a parabola with minima 0 at .5
    //float x[] = {5.0625,  1.5625, .0625, .5625, 3.0625, 7.5625}; // a parabola with minima 0 at .25
    //float x[] = { 5.70732,  1.92932,  0.15132,  0.37332,  2.59532,  6.81732}; // a parabola with min at .389
    float x[] = {32.573513   ,3.722280   ,0.022898   ,0.139369   ,6.735691 , 46.475866}; // a parabola squared min .389
    //float x[] = {3, 2, 1, 1.5, 2}; //more
    //float x[] = {2, 1.5, 1, 2, 3}; //less

    printf("%f\n",findminx(x));
    return 0;
}
