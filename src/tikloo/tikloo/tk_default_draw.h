#ifndef TK_DEFAULT_DRAW_H
#define TK_DEFAULT_DRAW_H

// default draw functions for every widget
#include<cairo/cairo.h>
#include"tk_types.h"

//these are all defined in their respective files
void tk_drawdial(cairo_t *cr, float w, float h, void* valp);
void tk_drawbutton(cairo_t *cr, float w, float h, void* val);
void tk_drawbg(cairo_t *cr, float w, float h, void* valp);
void tk_drawtext(cairo_t *cr, float w, float h, void* valp);
void tk_drawtip(cairo_t *cr, float w, float h, void* valp);//in text.h

void tk_drawnothing(cairo_t *cr, float w, float h, void* v);//in bg.h


#endif
