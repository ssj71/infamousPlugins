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


#ifndef FFF_SCOPE_H
#define FFF_SCOPE_H


#include <FL/Fl_Widget.H>
#include <FL/Fl.H>
#include <valarray>
#include <string>
#include <cairo.h>

//avtk drawing method (adapted)
static void default_scope_drawing(cairo_t *cr,float *data,unsigned short start)
{
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr,1);
    cairo_set_miter_limit(cr,4);
    cairo_set_source_rgb(cr,0,1,0);
    cairo_new_path(cr);

    cairo_move_to(cr,100,100*data[start]);
    for (int i=1; i<100; i++)
    {
        cairo_line_to(cr,100-i,100*data[(start-i)&0x07FF]);
    }
    cairo_stroke(cr);
};

namespace ffffltk
{

static void scope_callback(void* handle);

class Scope: public Fl_Widget
{
public:
    Scope(int _x, int _y, int _w, int _h, const char *_label = ""):
        Fl_Widget(_x, _y, _w, _h, _label)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;

        label = _label;

        drawing_w = 100;
        drawing_h = 100;
        drawing_f = &default_scope_drawing;

        average = false;
        avg = 0;
        p = 0;
        nvals = 0;
        min_val = 0;
        max_val = 1;
        for(int i=0; i<2048; i++)
            data[i] = 0;
        Fl::add_timeout(.10,scope_callback,this);
    }

    ~Scope()
    {
        Fl::remove_timeout(scope_callback);
    }

    bool highlight;
    int x, y, w, h;
    const char* label;

    int drawing_w;
    int drawing_h;
    void (*drawing_f)(cairo_t*,float*, unsigned short);//pointer to draw function

    float data[2048];
    int min_val;
    int max_val;
    bool average;

    float avg;
    int p;
    int nvals;

    void push_val(float val)
    {
        if(average)
        {
            avg += val;
            nvals++;
        }
        else
        {
            data[p++] = val;
            p&=0x07FF;
        }
    }

    void push_avg()
    {
        avg/= (double)nvals;
        data[p++] = avg;
        p&=0x07FF;
        nvals = 0;
    }

    void draw()
    {
        if (damage() & FL_DAMAGE_ALL)
        {
            cairo_t *cr = Fl::cairo_cc();

            cairo_save( cr );

            //calcluate scale and centering
            double scalex,
                   scaley,
                   shiftx=0,
                   shifty=0;
            scalex = w/(double)drawing_w;
            scaley = h/(double)drawing_h;
            {
                if(scalex > scaley)
                {
                    scalex = scaley;
                    shiftx = (w - scalex*drawing_w)/2.f;
                }
                else
                {
                    scaley = scalex;
                    shifty = h - scaley*drawing_h;
                }
            }
            //move to position in the window
            cairo_translate(cr,x+shiftx,y+shifty);
            //scale the drawing
            cairo_scale(cr,scalex,scaley);
            //call the draw function
            if(drawing_f) drawing_f(cr,data,p);
            else default_scope_drawing(cr,data,p);

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

    /*
    int handle(int event)
    {
      return 0;

      switch(event)
      {
        case FL_PUSH:
          highlight = 0;
          redraw();
          return 1;
        case FL_DRAG: {
            int t = Fl::event_inside(this);
            if (t != highlight) {
              redraw();
            }
          }
          return 1;
        case FL_SHORTCUT:
          if ( test_shortcut() )
          {
            do_callback();
            return 1;
          }
          return 0;
        default:
          return Fl_Widget::handle(event);
      }
    }
    */
};

static void scope_callback(void* handle)
{
    Scope* scope = (Scope*)handle;
    Fl::repeat_timeout(.10,scope_callback,handle);
    if(scope->average)
    {
        scope->push_avg();
    }
    scope->redraw();
};

} // ffffltk

#endif // FFF_SCOPE_H

