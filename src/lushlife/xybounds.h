/*
 * Author: spencer jackson 2014 *         ssjackson71@gmail.com
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


#ifndef FFF_XYBOUND_H
#define FFF_XYBOUND_H

#include <FL/Fl_Dial.H>
#include <FL/Fl_Slider.H>
#include <FL/fl_ask.H>
#include "ffffltk_input.h"
#include "ffffltk_xy.h"

namespace ffffltk
{


class XBound : public Fl_Widget
{
public:
    XBound(int _x, int _y, int _w, int _h, const char* _label=0):
        Fl_Widget(_x, _y, _w, _h, _label)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;

        drawing_w = 100;
        drawing_h = 100;
        drawing_f = &default_xy_drawing;
        floatvalue = 0;
        floatmin = 0;
        floatmax = 0;
        units[0] = 0;
        lock2int = 0;
        clickOffset = 0;
        mouseClicked = false; 
        enterval.winder = NULL;
    }

    int x, y, w, h;
    float floatmin,floatmax;
    bool dontdraw;

    int clickOffset;
    bool mouseClicked;

    nonmodal_input enterval;
    XYhandle* centerpoint;//this is the center point that this x range coresponds to

    int drawing_w;
    int drawing_h;
    void (*drawing_f)(cairo_t*);//function pointer to draw function
    float floatvalue;//these hold the actual value used (could be restricted to integer vals)
    char units[6];
    int lock2int;//flag to draw only integer values 

    static void set_ffffltk_value(void* obj, float val)
    {
        XBound* me = (XBound*)obj;
        if(val < me->floatmin) val = me->floatmin;
        if(val > me->floatmax) val = me->floatmax;
        me->floatvalue = val;

        me->update_position(); 
    }

    void update_position()
    {
        Fl_Group *g = parent();//parent
        float val = centerpoint->floatvaluex + floatvalue;
        if(centerpoint->squaredmaxx)
            val = sqrt(val/centerpoint->squaredmaxx);
        x = ( (val - centerpoint->Xv->minimum()) / (centerpoint->Xv->maximum() - centerpoint->Xv->minimum()) ) * (g->w() - centerpoint->w) + g->x();//reconvert to pixels based on value (this way it tracks log)
        x += centerpoint->w; //line up right hand sides
        y = centerpoint->y;

        if(x > g->x()+g->w()) dontdraw = true;
        else dontdraw = false;
        Fl_Widget::position(x,y);
        //do_callback();
        g->redraw();
        redraw();
    }

    void draw()
    {
        if (damage() & FL_DAMAGE_ALL && active() && !dontdraw)
        {
            cairo_t *cr = Fl::cairo_cc();

            cairo_save( cr );

            //calculate scale and centering
            double scale,
                   shiftx=0,
                   shifty=0;
            scale = centerpoint->w/(double)centerpoint->drawing_w;
            if(scale > centerpoint->h/(double)centerpoint->drawing_h)
            {
                scale = centerpoint->h/(double)centerpoint->drawing_h;
               // shiftx = (w - scale*drawing_w)/2.f;
            }
            //else
            //    shifty = h - scale*drawing_h;
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
                enterval.show(floatvalue,(char*)tooltip(),units,(void*)this,set_ffffltk_value);
            }
            return 1;
        case FL_DRAG:
        {
            if ( Fl::event_state(FL_BUTTON1) )
            {
                if ( mouseClicked == false ) // catch the "click" event
                {
                    clickOffset = Fl::event_x()-x;//offsets make the drag point wherever you click on the object
                    mouseClicked = true;
                } 

                g = parent();
                pos = Fl::event_x()-clickOffset;
                if(pos < centerpoint->x + centerpoint->w) pos = centerpoint->x + centerpoint->w;
                if(pos > g->x()+g->w() - w) pos = g->x() + g->w() - w;
                x = pos;

                pos -= centerpoint->w;//adjust for zero
                val = ( (float)(pos - g->x()) / (float)(g->w() - centerpoint->w) ) * (centerpoint->Xv->maximum() - centerpoint->Xv->minimum()) + centerpoint->Xv->minimum();
                if(lock2int) val = (int)val;
                if(centerpoint->squaredmaxx)
                    floatvalue = val*val*centerpoint->squaredmaxx;
                else
                    floatvalue = val;

                floatvalue -= centerpoint->floatvaluex;
                if(floatvalue<floatmin) floatvalue=floatmin;
                if(floatvalue>floatmax) floatvalue=floatmax;
                //update_position();

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
            //floatvaluex = centerpoint->Xv->value();
            //floatvaluey = centerpoint->Yv->value();
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
};//xbound

class YBound : public Fl_Widget
{
public:
    YBound(int _x, int _y, int _w, int _h, const char* _label=0):
        Fl_Widget(_x, _y, _w, _h, _label)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;

        drawing_w = 100;
        drawing_h = 100;
        drawing_f = &default_xy_drawing;
        floatvalue = 0;
        floatmin = 0;
        floatmax = 0;
        units[0] = 0;
        lock2int = 0;

        clickOffset = 0;
        mouseClicked = false; 
        enterval.winder = NULL;
    }

    int x, y, w, h;
    float floatmin,floatmax;
    bool dontdraw;

    int clickOffset;
    bool mouseClicked;

    nonmodal_input enterval;
    XYhandle* centerpoint;//this is the center point that this x range coresponds to

    int drawing_w;
    int drawing_h;
    void (*drawing_f)(cairo_t*);//function pointer to draw function
    float floatvalue;//these hold the actual value used (could be restricted to integer vals)
    char units[6];
    int lock2int;//flag to draw only integer values 

    static void set_ffffltk_value(void* obj, float val)
    {
        YBound* me = (YBound*)obj;
        if(val < me->floatmin) val = me->floatmin;
        if(val > me->floatmax) val = me->floatmax;
        me->floatvalue = val;

        me->update_position(); 
    }

    void update_position()
    {
        Fl_Group *g = parent();//parent
        float val = centerpoint->floatvaluey + floatvalue;
        if(centerpoint->squaredmaxy)
            val = sqrt(val/centerpoint->squaredmaxy);
        y = ( (centerpoint->Yv->maximum() - val) / (centerpoint->Yv->maximum() - centerpoint->Yv->minimum()) ) * (g->h() - centerpoint->h) + g->y() - h;//reconvert to pixels based on value (this way it tracks log)
        x = centerpoint->x;

        //if(y > g->y()+g->h()) dontdraw = true;
        if(y < g->y()) dontdraw = true;
        else dontdraw = false;
        Fl_Widget::position(x,y);
        do_callback();
        redraw();
        g->redraw();
    }

    void draw()
    {
        if (damage() & FL_DAMAGE_ALL && active() && !dontdraw)
        {
            cairo_t *cr = Fl::cairo_cc();

            cairo_save( cr );

            //calculate scale and centering
            double scale,
                   shiftx=0,
                   shifty=0;
            scale = centerpoint->w/(double)centerpoint->drawing_w;
            if(scale > centerpoint->h/(double)centerpoint->drawing_h)
            {
                scale = centerpoint->h/(double)centerpoint->drawing_h;
                shiftx = (w - scale*drawing_w);///2.f;
            }
            else
                shifty = h - scale*drawing_h;
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
                enterval.show(floatvalue,(char*)tooltip(),units,(void*)this,set_ffffltk_value);
            }
            return 1;
        case FL_DRAG:
        {
            if ( Fl::event_state(FL_BUTTON1) )
            {
                if ( mouseClicked == false ) // catch the "click" event
                {
                    clickOffset = Fl::event_y()-y;//offsets make the drag point wherever you click on the object
                    mouseClicked = true;
                } 

                g = parent();
                pos = Fl::event_y()-clickOffset;
                if(pos <= g->y()) pos = g->y();
                //if(pos >= centerpoint->y+centerpoint->h - h) pos = centerpoint->y + centerpoint->h - h;
                if(pos >= centerpoint->y - h) pos = centerpoint->y - h;
                y = pos;

                pos += h;//offset for size differences
                val = centerpoint->Yv->maximum() - ( (float)(pos - g->y()) / (float)(g->h() - centerpoint->h) ) * (centerpoint->Yv->maximum() - centerpoint->Yv->minimum());
                if(lock2int) val = (int)val;
                if(centerpoint->squaredmaxy)
                    floatvalue = val*val*centerpoint->squaredmaxy;
                else
                    floatvalue = val;

                floatvalue -= centerpoint->floatvaluey;
                //if(floatvalue<floatmin) floatvalue = floatmin;
                if(floatvalue>floatmax)
                {
                    floatvalue = floatmax;
                    update_position();
                }
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
            //floatvaluex = centerpoint->Xv->value();
            //floatvaluey = centerpoint->Yv->value();
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
};//y bound
} // ffffltk

#endif // FFF_DIAL_H
