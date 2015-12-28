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


#ifndef FFF_ASPECT_GROUP_H
#define FFF_ASPECT_GROUP_H


#include <FL/Fl_Widget.H>
#include <valarray>
#include <string>
#include <cairo.h>

//avtk drawing method (adapted)
static void default_ag_drawing(cairo_t *cr)
{
    cairo_set_line_width(cr, 1.5);


    // fill background
    cairo_rectangle( cr, 0, 0, 100, 100);
    cairo_set_source_rgba( cr, 66 / 255.f,  66 / 255.f ,  66 / 255.f , 1 );
    cairo_fill( cr );


    // set up dashed lines, 1 px off, 1 px on
    double dashes[1];
    dashes[0] = 2.0;

    cairo_set_dash ( cr, dashes, 1, 0.0);
    cairo_set_line_width( cr, 1.0);

    // loop over each 2nd line, drawing dots
    for ( int i = 0; i < 100; i += 4 )
    {
        cairo_move_to( cr, i, 0 );
        cairo_line_to( cr, i, 100 );
    }

    cairo_set_source_rgba( cr,  28 / 255.f,  28 / 255.f ,  28 / 255.f , 0.5 );
    cairo_stroke(cr);
    cairo_set_dash ( cr, dashes, 0, 0.0);


    // draw header
    // backing
    cairo_rectangle(cr, 0, 0, 100, 20);
    cairo_set_source_rgb( cr, 28 / 255.f,  28 / 255.f ,  28 / 255.f );
    cairo_fill( cr );

    // text NOT YET SUPPORTED
    //cairo_move_to( cr, 10, 14 );
    //cairo_set_source_rgba( cr, 0 / 255.f, 153 / 255.f , 255 / 255.f , 1 );
    //cairo_set_font_size( cr, 10 );
    //cairo_show_text( cr, label );

    // lower stripe
    cairo_move_to( cr, 0  , 20 );
    cairo_line_to( cr, 100, 20 );
    cairo_stroke( cr );


    // stroke rim
    cairo_rectangle(cr, 0, 0, 100, 100);
    cairo_set_source_rgba( cr, 0 / 255.f, 153 / 255.f , 255 / 255.f , 1 );
    cairo_stroke( cr );
}


namespace ffffltk
{

class Aspect_Group: public Fl_Group
{
public:
    Aspect_Group(int _x, int _y, int _w, int _h, const char *_label = ""):
        Fl_Group(_x, _y, _w, _h, _label)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;

        label = _label;

        drawing_w = 100;
        drawing_h = 100;
        drawing_f = &default_ag_drawing;

        highlight = false;
    }
    bool highlight;
    int x, y, w, h;
    const char* label;

    int drawing_w;
    int drawing_h;
    void (*drawing_f)(cairo_t*);//pointer to draw function

    void draw()
    {
        if (damage() & ~FL_DAMAGE_CHILD)
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
            if(scalex > scaley)
            {
                scalex = scaley;
                shiftx = (w - scalex*drawing_w)/2.f;
            }
            else
            {
                scaley = scalex;
                shifty = (h - scaley*drawing_h)/2.f;
            }
            //label behind value
            draw_label();
            //move to position in the window
            cairo_translate(cr,x+shiftx,y+shifty);
            //scale the drawing
            cairo_scale(cr,scalex,scaley);
            //call the draw function
            if(drawing_f) drawing_f(cr);
            else default_ag_drawing(cr);

            cairo_restore( cr );
        }
        draw_children();
    }

    void resize(int X, int Y, int W, int H)
    {
        //Fl_Widget::resize(X,Y,W,H);
        w = W;
        h = H;
        if( W/(float)H < drawing_w/(float)drawing_h)
        {
            H = W*drawing_h/(float)drawing_w;
            Y += (h-H)/2.f;
            //need to shift Y to center?
        }
        else if( W/(float)H > drawing_w/(float)drawing_h)
        {
            W = H*drawing_w/(float)drawing_h;
            X += (w-W)/2.f;
        }
        x = X;
        y = Y;
        w = W;
        h = H;
        Fl_Group::resize(X,Y,W,H);
    }

    /*    int handle(int event)
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
        }*/
};

} // ffffltk

#endif // FFF_BACKGROUND_H

