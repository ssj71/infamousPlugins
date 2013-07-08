#include<unistd.h> 
#include<stdio.h>

void ruleprint(unsigned char x)
{
    unsigned char i;
    printf("\n111 110 101 100 011 010 001 000\n");
    for(i=128;i>0;i=i>>1)
    {
        printf(" %c  ",(x&i)?'1':'0');
    }
    printf("\n");
}
    
void binprint(unsigned long x, unsigned char n)
{
    unsigned long i;
    for(i=1<<n;i>0;i=i>>1)
    {
        printf("%c",(x&i)?'0':' ');
    }
    printf("\n");
}

void useage()
{
    printf("\nrule, a constrained cellular automation visualizer\n");
    printf("\n");
    printf("USEAGE:\n");
    printf(" rule <rule number> [<initial condition>]\n");
    printf("\n");
    printf("EXAMPLES:\n");
    printf(" rule 30\n");
    printf(" rule 110 0xFAFF\n");
    printf("\n");
    printf("NOTES:\n");
    printf(" There are 16 cells on a torus. Arguments can be hex or decimal.\n");
    printf(" If no initial condition is supplied, default is 1. For more\n");
    printf(" information read 'elementary cellular automation' on wikipedia\n");
    printf("\n");
    return;
} 

int main(int argc, char **argv)
{
unsigned char rule=0xD0;//0x7c;
unsigned char t;
unsigned long cells = 1;
unsigned long temp;
unsigned char index;
unsigned char ncells = 16;

if (argc > 1) 
{
    if(argv[1][0] == '0' && argv[1][1] == 'x')
    {
        unsigned int a;
        sscanf(argv[1],"%x",&a);
        rule = (unsigned char)a;
    }
    else
    {
        rule = atoi(argv[1]);
    }
    if (argc > 2)
    {
        if(argv[2][0] == '0' && argv[2][1] == 'x')
        {
            unsigned int a;
            sscanf(argv[2],"%x",&a);
            cells = (unsigned short)a;
        }
        else
        {
            cells = atoi(argv[2]);
        }
    }
}
else
{
    printf("No argument! \n");
    useage();
    return;
}

ruleprint(rule);
printf("use ctl+C to stop \n");
ncells--;
    for(;;cells=temp<<1|temp>>ncells)
    {
    
        binprint(cells,ncells);
        temp=0;
        for(index=0;index<=ncells;index++)
        {
            
            //the idea is to shift the rule mask (w/rollover) according to the 3 
            //bits in the neighborhood at $index, mask that bit in the rule to
            //then determine the next cell state and OR it into a temp value
            //       |cell state-----------------------------------------------|
            //               | rule mask ---------------------------------|
            //                   |neighborhood ---------------------------|
            temp |= ((rule & 1<<((cells>>index|cells<<(ncells-index+1) )&7) )>0)<<index;
            
        }
        usleep(100000);
    }
}
