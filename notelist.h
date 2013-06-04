//Spencer Jackson
//notelist.h

#include<constants.h>
#include<note.h>

typedef struct _NOTELIST{
    unsigned char length;
    NOTE* (*num)(unsigned char);//used to get note n
   // NOTE* (*add)(NOTELIST* self,unsigned char);//used to "append" new note
    _NOTELIST* prev;
    _NOTELIST* next;
    _NOTELIST* last;//points to last note in list (last node->last points to self)
    _NOTELIST* end;//points to last active note
    NOTE me;
    unsigned char index;//index no. of node;
    unsigned char *nodes;//total nodes in list
    unsigned char *nactive;//active notes in list
    bool active;
}NOTELIST;

NOTELIST* init_notelist(NOTELIST* self);
void destroy_notelist(NOTELIST* self);
