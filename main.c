#include <stdio.h>
#include<casynth.h>

int main(void)
{
    CASYNTH synth;
    init_casynth(&synth,48000,"cow",NULL);
    run_casynth(&synth,1000);
    printf("Hello World!\n");
    return 0;
}

