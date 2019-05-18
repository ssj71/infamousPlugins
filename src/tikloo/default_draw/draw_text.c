#include<ctype.h>
#include "tk_default_draw.h"
#include "tk.h"

// here we assume a single line
// line and fill must be arrays describing rgba (and a width for line)
// to see the actual function used by default see next function
void tk_drawtextcolor(cairo_t *cr, float w, float h, void* valp, float* line, float* fill)
{
    tk_text_stuff* tkts = (tk_text_stuff*)valp;
    tk_text_table* tkt = (tk_text_table*)tkts->tkt;
    int n = tkts->n;

    //TODO: cache drawing?
    w /= tkt->scale;
    h /= tkt->scale;
    if(!w || !h)
        return;
    tkt->strchange[n] = false;
    cairo_save( cr );
    cairo_scale(cr,tkt->scale,tkt->scale);
    //cairo_translate(cr, 0, tkt->tkf[n]->base);//start at foot of line

    cairo_glyph_path(cr, tkt->glyphs[n], tkt->glyph_end[n]);
    cairo_set_source_rgba(cr, fill[0], fill[1], fill[2], fill[3]);
    cairo_fill_preserve(cr);
    cairo_set_source_rgba(cr, line[0], line[1], line[2], line[3]);
    cairo_set_line_width(cr, line[4]);
    cairo_stroke(cr);
    cairo_restore( cr );
} 

//this defaults to a light text, you can easily write your own to get the color you desire!
void tk_drawtext(cairo_t *cr, float w, float h, void* cache, void* valp)
{
    float line[] = {.1,.1,.1,1,.1};//rgba width
    float fill[] = {.9,.9,.9,1};//rgba
    tk_drawtextcolor(cr,w,h,valp,line,fill);
}

void tk_drawtip(cairo_t *cr, float w, float h, void* cache, void* valp)
{
    //float line[] = {.2,.2,.2,1,.5};//rgba width
    float line[] = {.9,.9,.9,0,0};//rgba width
    float fill[] = {.8,.8,.8,1};//rgba
    //float scale = ((tk_text_table*)((tk_text_stuff*)valp)->tkt)->scale;

    //draw a background square 
    cairo_save( cr );
    cairo_set_source_rgba(cr, TK_COLOR_DARK, 1);
    cairo_new_path(cr);
    cairo_move_to(cr, 0, 0);
    cairo_line_to(cr, 0, h);
    cairo_line_to(cr, w, h);
    cairo_line_to(cr, w, 0);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_fill(cr);
    cairo_restore( cr ) ; // */

    cairo_save( cr );
    //cairo_translate(cr,-4*scale,-4*scale);//this should correspond with b in textlayout
    tk_drawtextcolor(cr,w,h,valp,line,fill);
    cairo_restore( cr ) ; 
}


void tk_drawtextentry(cairo_t *cr, float w, float h, void* cache, void* valp)
{
    tk_text_table* tkt = ((tk_text_stuff*)valp)->tkt;
    uint16_t n = ((tk_text_stuff*)valp)->n;
    int x,y,sx,sy;

    tk_gettextcursor(valp,&x,&y,&sx,&sy);
    x += 2*tkt->scale; //offset for margin
    //draw bg/text if necessary
    if(tkt->strchange[n] || !(tkt->cursorstate&TK_CURSOR_CHANGED))
    {//string has changed OR we got resized or something
        cairo_save( cr );
        tk_drawtip(cr,w,h,cache,valp);
        cairo_restore( cr ) ;
    }
    if(tkt->select[n])
    {
        if(tkt->cursorstate&TK_CURSOR_MOVED)
        {//draw selection box if it changed
            cairo_save( cr );
            cairo_set_source_rgba(cr, .0,.0,.0,.5);
            cairo_set_line_width(cr, 1);
            cairo_new_path(cr);
            cairo_move_to(cr, x, y);
            cairo_line_to(cr, sx, y);//sy+tkt->tkf[n]->fontsize*tkt->scale);
            cairo_line_to(cr, sx, sy+tkt->tkf[n]->fontsize*tkt->scale);
            cairo_line_to(cr, x, sy+tkt->tkf[n]->fontsize*tkt->scale); //TODO: handle multiple lines (y,h)
            cairo_close_path(cr);
            cairo_set_tolerance(cr, 0.1);
            cairo_fill(cr);
            cairo_restore( cr ) ;
        }
    }
    else if(tkt->cursorstate&TK_CURSOR_STATE)
    {
        if(x<w)
        {//draw cursor
            //TODO: maybe cache cursor so we don't have to redraw the whole widget
            cairo_save( cr );
            cairo_set_source_rgba(cr, .0,.0,.0,1);
            cairo_set_line_width(cr, 2);
            cairo_new_path(cr);
            cairo_move_to(cr, x, y);
            cairo_line_to(cr, x, y+tkt->tkf[n]->fontsize*tkt->scale);
            cairo_set_tolerance(cr, 0.1);
            cairo_stroke(cr);
            cairo_restore( cr ) ;
        }
    }
    else
    {//draw a not-cursor
        cairo_save( cr );
        cairo_set_source_rgba(cr, TK_COLOR_DARK, 1);//same color as the box
        cairo_set_line_width(cr, 2);
        cairo_new_path(cr);
        cairo_move_to(cr, x, y);
        cairo_line_to(cr, x, y+tkt->tkf[n]->fontsize*tkt->scale);
        cairo_set_tolerance(cr, 0.1);
        cairo_stroke(cr);
        cairo_restore( cr ) ;
    }
}
