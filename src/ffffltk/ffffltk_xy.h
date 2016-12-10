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


#ifndef FFF_XY_H
#define FFF_XY_H

#include <FL/Fl_Dial.H>
#include <FL/Fl_Slider.H>
#include <FL/fl_ask.H>
#include <cairo.h>
#include "ffffltk_input.h"

//avtk drawing method (adapted)
static void default_xy_drawing(cairo_t *cr)
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

    float angle = 2.46 + ( 4.54 * 1 );
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
        drawing_f = &default_xy_drawing;
        floatvaluex = 0;
        floatvaluey = 0;
        unitsx[0] = 0;
        unitsy[0] = 0;
        lock2int = 0;
        squaredmaxx = 0;
        squaredmaxy = 0;

        clickOffsetX = 0;
        clickOffsetY = 0;
        mouseClicked = false;

        //entervalx.winder = NULL;
        //entervaly.winder = NULL;
        entervals.winder = NULL;
        entervals.setparams("X Value","","Y Value","");

        Fl_Group* tmp = Fl_Group::current();//store current group so it doesn't get lost
        Fl_Group::current(NULL);
        Xv = new Fl_Dial(0,0,0,0,NULL);
        Yv = new Fl_Dial(0,0,0,0,NULL);
        Fl_Group::current(tmp);

    }
    ~XYhandle(){delete Xv; delete Yv;}

    int x, y, w, h;

    Fl_Dial *Xv,*Yv;//hidden valuators

    int clickOffsetY;
    int clickOffsetX;
    bool mouseClicked;

    //nonmodal_input entervalx;
    //nonmodal_input entervaly;
    nonmodal_2input entervals;

    int drawing_w;
    int drawing_h;
    void (*drawing_f)(cairo_t*);//function pointer to draw function
    float floatvaluex;//these hold the actual value used (could be restricted to integer vals)
    float floatvaluey;
    char unitsx[6];
    char unitsy[6];
    int lock2int;//flag to draw only integer values 
    float squaredmaxx;//max if meant to be squared (for log approx) floatval = val()*val()*squaredmaxx
    float squaredmaxy;//max if meant to be squared (for log approx)

    static void set_ffffltk_valuex(void* obj, float val)
    {
        XYhandle* me = (XYhandle*)obj;
        if(me->squaredmaxx)
            val = sqrt(val/me->squaredmaxx);//reverse squaring for bounds check
        if ( val > me->Xv->maximum() ) val = me->Xv->maximum();
        if ( val < me->Xv->minimum() ) val = me->Xv->minimum();
        me->Xv->value(val);
        if(me->squaredmaxx)
            me->floatvaluex = val*val*me->squaredmaxx;
        else
            me->floatvaluex = val;
        Fl_Group *g = me->parent();//parent
        me->x = ( (val - me->Xv->minimum()) / (me->Xv->maximum() - me->Xv->minimum()) ) * (g->w() - me->w) + g->x();

        me->position(me->x,me->y);
        //me->do_callback();
        me->redraw();
        g->redraw();
    }
    static void set_ffffltk_valuey(void* obj, float val)
    {
        XYhandle* me = (XYhandle*)obj;
        if(me->squaredmaxy)
            val = sqrt(val/me->squaredmaxy);//reverse squaring for bounds check
        if ( val > me->Yv->maximum() ) val = me->Yv->maximum();
        if ( val < me->Yv->minimum() ) val = me->Yv->minimum();
        me->Yv->value(val);
        if(me->squaredmaxy)
            me->floatvaluey = val*val*me->squaredmaxy;
        else
            me->floatvaluey = val;
        Fl_Group *g = me->parent();//parent
        me->y = ( (me->Yv->maximum() - val) / (me->Yv->maximum() - me->Yv->minimum()) ) * (g->h() - me->h) + g->y();

        me->position(me->x,me->y);
        //me->do_callback();
        me->redraw();
        g->redraw();
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
                shiftx = (w - scale*drawing_w);//2.f;
            }
            else
                shifty = 0;//h - scale*drawing_h;//shift to top right for bounds
            //label behind value
            //move to position in the window
            cairo_translate(cr,x+shiftx,y+shifty);
            //scale the drawing
            cairo_scale(cr,scale,scale);
            //call the draw function
            if(drawing_f) drawing_f(cr);
            else default_xy_drawing(cr);

            cairo_restore( cr );

        }
    }


    void resize(int _X, int _Y, int _W, int _H)
    {
        Fl_Widget::resize(_X,_Y,_W,_H);
        x = _X;
        y = _Y;
        w = _W;
        h = _H;
        redraw();
    }

    int handle(int event)
    {
        //cout << "handle event type = " << event << " value = " << value() << endl;

        //Fl_Slider::handle( event );

        float val;
        int pos;
        Fl_Group *g;//parent
        switch(event)
        {
        case FL_PUSH:
            //highlight = 1;
            if(Fl::event_button() == FL_MIDDLE_MOUSE || Fl::event_button() == FL_RIGHT_MOUSE)
            {
                /*if(!Xv->tooltip())
                    Xv->copy_tooltip("X Parameter");
                if(!Yv->tooltip())
                    Yv->copy_tooltip("Y Parameter");
                entervaly.show(floatvaluey,(char*)Yv->tooltip(),unitsy,(void*)this,set_ffffltk_valuey);
                entervalx.show(floatvaluex,(char*)Xv->tooltip(),unitsx,(void*)this,set_ffffltk_valuex);
                */
                entervals.show((void*)this, floatvaluex, set_ffffltk_valuex, floatvaluey, set_ffffltk_valuey);
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

                val = ( (float)(x - g->x()) / (float)(g->w() - w) ) * (Xv->maximum() - Xv->minimum()) + Xv->minimum();
                Xv->value(val);
                if(lock2int) val = (int)val;
                if(squaredmaxx)
                    floatvaluex = val*val*squaredmaxx;
                else
                    floatvaluex = val;

                val = Yv->maximum() - ( (float)(y - g->y()) / (float)(g->h() - h) ) * (Yv->maximum() - Yv->minimum());
                Yv->value(val);
                if(lock2int) val = (int)val;
                if(squaredmaxy)
                    floatvaluey = val*val*squaredmaxy;
                else
                    floatvaluey = val;

                Fl_Widget::position(x,y);
                redraw();
                g->redraw();
                do_callback(); // makes FLTK call "extra" code entered in FLUID
            }
        }
        return 1;
        case FL_RELEASE:
            //if (highlight) {
            // highlight = 0;
            Fl_Widget::copy_label("");
            redraw();
            //floatvaluex = Xv->value();
            //floatvaluey = Yv->value();
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
