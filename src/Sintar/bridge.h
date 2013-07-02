//Spencer Jackson
//bridge.h
#include<constants.h>

typedef struct _BRIDGE
{
    float length;
    float c1, c2, c3;
    float input_force;
    float y;
    float yprev;
    float v;
    float vprev;
    float dt;
    float sample_rate;
}BRIDGE;

void init_bridge(BRIDGE* self, double samplerate);
void update_bridge(BRIDGE* self);
