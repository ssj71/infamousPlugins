//spencer jackson

//gpl v2 and all that

//a simple and kinda boring lfo implementation
#include<stdint.h>

class Lfo
{
public:
    Lfo(double sample_rate, uint32_t fragsize);
    ~Lfo();
    float out(float _shape);
    float out();
    void  reset();
    float shape;
    float gain;
    float freq;
private:
    float phase; 
    float prev_x;
    float prev_y;
    float coeff;
    float phastep;
};
