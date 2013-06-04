//Spencer Jackson
//cell_automation.c

unsigned short torus_of_life(unsigned char rule, unsigned short cells, unsigned char ncells)
{
    unsigned short temp;
    unsigned char index;
    ncells--;
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
    cells=temp<<1|temp>>ncells;
    return cells;
}
