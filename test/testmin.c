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
		a = 1.5*(-arr[0] + arr[1] - 3*arr[2] + arr[3]);
		b = 2*arr[0] - 5*arr[1] + 4*arr[2] - arr[3];
		c = .5*(-arr[0] + arr[2]);

        printf("less a=%f b=%f c=%f %f\n",a,b,c,b*b-4*a*c);
		return 1-(-b+sqrt(b*b-4*a*c))/(2*a);//its possible that this is wrong but I think b-.. will be out of domain t E[0,1]
	}
	else if(m2<0)
	{
		//minima is after sample
		a = 1.5*(-arr[1] + arr[2] - 3*arr[3] + arr[4]);
		b = 2*arr[1] - 5*arr[2] + 4*arr[3] - arr[4];
		c = .5*(-arr[1] + arr[3]);

        printf("more a=%f b=%f c=%f %f\n",a,b,c,b*b-4*a*c);
		return (-b+sqrt(b*b-4*a*c))/(2*a);//its possible that this is wrong but I think b-.. will be out of domain t E[0,1]
	}
	else return 0;
}


int main()
{ 
    float x[] = {3, 2, 1, 1.5, 2}; //more
    //float x[] = {2, 1.5, 1, 2, 3}; //less

    printf("%f\n",findminx(x));
    return 0;
}
