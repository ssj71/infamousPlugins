//spencer jackson

//gpl v2 and all that

//a simple and kinda boring lfo implementation

class Lfo
{
public:
    lfo(double sample_rate, uint32_t fragsize);
    ~lfo();
    float out(float _shape);
    float out();
    float shape;
    float gain;
    float freq;
private:
    float phase; 
    float prev_x;
    float prev_y;
    float coeff;
    float phastep;
}
