//Spencer Jackson

//a search for the perfect sine function
#include<math.h>
#include<stdio.h>
#include<stdint.h>

float mySin(float x)
{
    float y = 1.27323954474*x - 0.40528473456*x*(x>0?x:-x);
    return 0.225*(y*(y>0?y:-y) - y) + y;
}

int32_t intSin2(int32_t x)
{
    int32_t y;
    x = x>>15;
    y = (41722*(x - ((x*abs(x))>>16)))>>15;
    return 23162*((y*abs(y))>>16) +25395*y;
}
int32_t intSin(int32_t x)
{
    int32_t y;
    x >>= 15;
    y = ~x +1;
    y *= x;
    y >>= 16;
    y *= 41722;
    
        
}

int main()
{
    //0x02
    //0xfe
    
    float a = 1.27323954474*(double)(1<<15); 
    float b = M_PI*0.40528473456*(double)(1<<15);
    float c = M_PI*.225*(double)(1<<15);
    float d = 0.775*(double)(1<<15);
    int32_t phase = -30451;
    phase = phase&0x7fffffff;//abs val

    printf("abs %i\n",phase);
    
    printf("%f\n%f\n%f\n%f\n",a,b,c,d);
    //results:
    //41721.511719
    //41721.511719
    //23162.333984
    //25395.199219
    return 0;
}
