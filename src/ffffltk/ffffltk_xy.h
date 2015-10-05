/*
 * Author: spencer jackson 2014
 *         ssjackson71@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */


 //This class provides an adjustable point on an xy table such that you can have several points on the same axes


#ifndef FFF_DIAL_H
#define FFF_DIAL_H

#include <FL/Fl_Dial.H>
#include <FL/Fl_Slider.H>
#include <FL/fl_ask.H>
#include "ffffltk_input.h"

//avtk drawing method (adapted)
static void default_bg_drawing(cairo_t *cr, float val)
{

    cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);

    cairo_set_line_width(cr, 3.97);
    cairo_move_to( cr, 50, 50);
    cairo_line_to( cr, 50, 50);
    cairo_set_source_rgba(cr, 0.5, 0.5, 0.5, 0.4 );

    // draw dash guide
    double dashes[2];
    cairo_set_line_width(cr, 1.7);
    dashes[0] = 3.0;
    dashes[1] = 3.0;
    cairo_set_dash ( cr, dashes, 2, 0.0);
    cairo_stroke(cr);

    cairo_arc(cr, 50,50, 46, 2.46, 0.75 );
    //cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 0.4 );
    cairo_stroke(cr);
    cairo_set_dash ( cr, dashes, 0, 0.0);

    float angle = 2.46 + ( 4.54 * val );
    cairo_set_line_width(cr, 4.97);
    cairo_arc(cr, 50,50, 46, 2.46, angle );
    cairo_line_to(cr, 50,50);
    cairo_set_source_rgba(cr, 1.0, 0.48,   0, 1.0);
    cairo_stroke(cr);
}

namespace ffffltk
{

class XYhandle : public Fl_Widget
{
public:
    XYhandle(int _x, int _y, int _w, int _h, const char* _label=0):
        Fl_Widget(_x, _y, _w, _h, _label)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;

        drawing_w = 100;
        drawing_h = 100;
        drawing_f = &default_bg_drawing;
        floatvaluex = 0;
        floatvaluey = 0;
        unitsx[0] = 0;
        unitsy[0] = 0;
        lock2int = 0;

        clickOffsetY = 0;
        mouseClicked = false;

    }

    int x, y, w, h;

    Fl_Valuator X,Y;//hidden valuators

    int clickOffsetY;
    int clickOffsetX;
    bool mouseClicked;

    nonmodal_input entervalx;
    nonmodal_input entervaly;

    int drawing_w;
    int drawing_h;
    void (*drawing_f)(cairo_t*,float);//function pointer to draw function
    float floatvaluex;//these hold the actual value used (could be restricted to integer vals)
    float floatvaluey;
    char unitsx[6];
    char unitsy[6];
    int lock2int;//flag to draw only integer values 

    static void set_ffffltk_valuex(void* obj, float val)
    {
        XYhandle* me = (XYhandle*)obj;
        if ( val > me->X.maximum() ) val = me->X.maximum();
        if ( val < me->X.minimum() ) val = me->X.minimum();
        me->X.set_value(val);
        me->floatvaluex = val;

        me->redraw();
        me->do_callback();
    }
    static void set_ffffltk_valuey(void* obj, float val)
    {
        XYhandle* me = (XYhandle*)obj;
        if ( val > me->Y.maximum() ) val = me->Y.maximum();
        if ( val < me->Y.minimum() ) val = me->Y.minimum();
        me->Y.set_value(val);
        me->floatvaluey = val;

        me->redraw();
        me->do_callback();
    }

    void draw()
    {
        if (damage() & FL_DAMAGE_ALL && active())
        {
            cairo_t *cr = Fl::cairo_cc();

            cairo_save( cr );

            //calculate scale and centering
            double scale,
                   shiftx=0,
                   shifty=0;
            scale = w/(double)drawing_w;
            if(scale > h/(double)drawing_h)
            {
                scale = h/(double)drawing_h;
                shiftx = (w - scale*drawing_w)/2.f;
            }
            else
                shifty = h - scale*drawing_h;
            //label behind value
            //move to position in the window
            cairo_translate(cr,x+shiftx,y+shifty);
            //scale the drawing
            cairo_scale(cr,scale,scale);
            //call the draw function
            if(drawing_f) drawing_f(cr,val);
            else default_bg_drawing(cr,val);

            cairo_restore( cr );

        }
    }


    void resize(int X, int Y, int W, int H)
    {
        Fl_Widget::resize(X,Y,W,H);
        x = X;
        y = Y;
        w = W;
        h = H;
        redraw();
    }

    int handle(int event)
    {
        //cout << "handle event type = " << event << " value = " << value() << endl;

        //Fl_Slider::handle( event );

        float val = value();
        int pos;
        Fl_Group *g;//parent
        switch(event)
        {
        case FL_PUSH:
            //highlight = 1;
            if(Fl::event_button() == FL_MIDDLE_MOUSE || Fl::event_button() == FL_RIGHT_MOUSE)
            {
                entervalx.show(X.value(),(char*)X.tooltip(),unitsx,(void*)this,set_ffffltk_valuex);
                entervaly.show(Y.value(),(char*)Y.tooltip(),unitsy,(void*)this,set_ffffltk_valuey);
            }
            return 1;
        case FL_DRAG:
        {
            if ( Fl::event_state(FL_BUTTON1) )
            {
                if ( mouseClicked == false ) // catch the "click" event
                {
                    clickOffsetX = Fl::event_x()-x;//offsets make the drag point wherever you click on the object
                    clickOffsetY = Fl::event_y()-y;
                    mouseClicked = true;
                } 

                g = parent();
                pos = Fl::event_x()-clickOffsetX;
                if(pos < g->x()) pos = g->x();
                if(pos > g->x()+g->w() - w) pos = g->x() + g->w() - w;
                x = pos;

                pos = Fl::event_y()-clickOffsetY;//origin is bottom left
                if(pos < g->y()) pos = g->y();
                if(pos > g->y()+g->h() - h) pos = g->y() + g->h() - h;
                y = pos;

                val = ( (x - g->x()) / (g->w() - w) ) * (X.maximum() - X.minimum()) + X.minimum();
                X.set_value(val);
                if(lock2int) val = (int)val;
                floatvaluex = val;

                val = ( (g->y() - y) / (g->h() - h) ) * (Y.maximum() - Y.minimum()) + Y.minimum();
                Y.set_value(val);
                if(lock2int) val = (int)val;
                floatvaluey = val;

                redraw();
                do_callback(); // makes FLTK call "extra" code entered in FLUID
            }
        }
        return 1;
        case FL_RELEASE:
            //if (highlight) {
            // highlight = 0;
            Fl_Widget::copy_label("");
            redraw();
            floatvalue = value();
            // never do anything after a callback, as the callback
            // may delete the widget!
            //}
            mouseClicked = false;
            return 1;
        case FL_ENTER:
            redraw();
            return 1;
        case FL_LEAVE:
            redraw();
            return 1;
        default:
            return Fl_Widget::handle(event);
        }
    }
};

} // ffffltk

#endif // FFF_DIAL_H