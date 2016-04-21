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


#ifndef FFF_BUTTON_H
#define FFF_BUTTON_H

#include <FL/Fl_Button.H>
#include <cairo.h>

static void default_bg_drawing(cairo_t *cr, int val)
{
    cairo_rectangle( cr, 1, 1, 98, 98 );
    cairo_set_source_rgb( cr,28 / 255.f,  28 / 255.f ,  28 / 255.f  );
    cairo_fill_preserve(cr);

    cairo_set_line_width(cr, 1.5);
    cairo_rectangle( cr, 1, 1, 98, 98 );

    if ( val )
    {
        cairo_set_source_rgba(cr, 1.0, 0.48,   0, 0.4);
        cairo_fill_preserve(cr);
    }

    cairo_set_source_rgba(cr, 1.0, 0.48,   0, 1);
    cairo_stroke(cr);

}

namespace ffffltk
{

class Button : public Fl_Button
{
public:
    Button(int _x, int _y, int _w, int _h, const char *_label=""):
        Fl_Button(_x, _y, _w, _h, _label)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;

        drawing_w = 100;
        drawing_h = 100;
        drawing_f = &default_bg_drawing;
        floatvalue = value();

        label = _label;

        highlight = false;
        mouseOver = false;
    }

    bool mouseOver;
    bool highlight;
    int x, y, w, h;
    const char* label;

    int drawing_w;
    int drawing_h;
    void (*drawing_f)(cairo_t*,int);
    float floatvalue;

    void draw()
    {
        if (damage() & FL_DAMAGE_ALL)
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
            draw_label();
            //move to position in the window
            cairo_translate(cr,x+shiftx,y+shifty);
            //scale the drawing
            cairo_scale(cr,scale,scale);
            //call the draw function
            if(drawing_f) drawing_f(cr,value());
            else default_bg_drawing(cr,value());

            cairo_restore( cr );

            draw_label();
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

    /*    int handle(int event)
        {
          switch(event) {
            case FL_PUSH:
              highlight = 1;
              redraw();
              return 1;
            case FL_DRAG: {
                int t = Fl::event_inside(this);
                if (t != highlight) {
                  highlight = t;
                  redraw();
                }
              }
              return 1;
            case FL_ENTER:
              mouseOver = true;
              redraw();
              return 1;
            case FL_LEAVE:
              mouseOver = false;
              redraw();
              return 1;
            case FL_RELEASE:
              if (highlight) {
                highlight = 0;
                redraw();
                do_callback();
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
    int handle(int event)
    {
        int rtn = Fl_Button::handle(event);
        floatvalue = value();
        return rtn;
    }
};


} // ffffltk

#endif // FFF_BUTTON_H

