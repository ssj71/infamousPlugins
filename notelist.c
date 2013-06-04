//Spencer Jackson
//notelist.c
#include<notelist.h>

//local function declarations
NOTELIST* append_notelist(NOTELIST* self, unsigned char index);

NOTELIST* init_notelist(NOTELIST* self)
{
    unsigned char i;
    self->nodes  = 1;
    self->index  = 0;
    self->prev = self;//point first at self (it's better than space)
    self->next = self;
    self->last = self;
    self->end = self;
    self->nodes = (unsigned char*)malloc(sizeof(i));
    self->nactive = (unsigned char*)malloc(sizeof(i));
    self->active = 0;
    *(self->nodes) = 1;
    *(self->nactive) = 0;

    for(;*(self->nodes)<127;append_notelist(self));
    self->prev = self->last;//make list circular
    self->last->next = self;
}


NOTELIST* append_notelist(NOTELIST* self, unsigned char index)
{
    NOTELIST* node = self->last;
    NOTELIST* newguy = (NOTELIST*)malloc(sizeof(NOTELIST));
    node->next = newguy;
    newguy->prev = node;
    newguy->index = *(node->nodes)++;
    newguy->nactive = node->nactive;
    newguy->nodes = node->nodes;
    for(node = newguy;node->index >0;node = node->prev)
    {
        node->last = newguy;
    }
    node->last = newguy;
    return self;
}

NOTELIST* deactivate(NOTELIST* self, unsigned char index)
{
    unsigned char i;
    NOTELIST* node = self;
    //find the supposedly active note
    if(self->index == index)//head is the target
    {
        self->active = FALSE;
        *(self->nactive)--;
        self->prev->next = self->next;//make neighbors meet
        self->next->prev = self->prev;
        node = self->next;//new head
        self->end->next->prev = self;//insert old head after end
        self->end->next = self;
        self = node;
        return self;
    }
    for(i=0;i<*(self->nactive);node = node->next)
    {
        i++;
        if(node->index == index)
        {
            node->active = FALSE;
            *(node->nactive)--;
            node->prev->next = node->next;
            node->next->prev = node->prev;
            node->end->next->prev = node;//insert inactive note after end
            node->end->next = node;
            return self;
        }
    }
    return self;
}

void activate(unsigned char index)
{
    unsigned char active[127];
    unsigned char nactive,i;

    //activate
    for(i=0;i<nactive;i++)
    {
        if(active[i]==index)
        {
            active[nactive++] = index;
            break;
        }
    }

    //deactivate
    for(i=0;i<nactive;i++)
    {
        if(active[i]==index)
        {
            break;
        }
    }
    nactive--;
    for(;i<nactive;i++)
    {
        active[i]=active[i+1];
    }

}

