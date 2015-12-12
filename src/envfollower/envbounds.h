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


#ifndef FFF_ENVBOUNDS_H
#define FFF_ENVBOUNDS_H


#include <FL/Fl_Widget.H>
#include <valarray>
#include <string>

namespace ffffltk
{

class EnvBounds: public Fl_Widget
{
public:
    EnvBounds(int _x, int _y, int _w, int _h, const char *_label = ""):
        Fl_Widget(_x, _y, _w, _h, _label)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;

        //label = _label;

        drawing_w = 600;
        drawing_h = 202;

        min = 0;
        max = 1;
        drawlines = blue = false;
    }

    int x, y, w, h;
    //const int8_t* label;

    int drawing_w;
    int drawing_h;
    float min,max;
    bool drawlines;
    bool blue;

    void default_drawing(cairo_t *cr)
    {

        cairo_pattern_t *pattern;

        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        if(drawlines)
            cairo_set_line_width(cr, 1);
        else
            cairo_set_line_width(cr,5);
        cairo_set_miter_limit(cr, 4);
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
        if(blue)
            pattern = cairo_pattern_create_rgba(.3,.6,1,.75);
        else
            pattern = cairo_pattern_create_rgba(0,1,0,.53);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);

        cairo_move_to(cr,4,-183.33*min+188.33);
        if(drawlines)
            cairo_line_to(cr,598,-183.33*min+188.33);
        else
            cairo_line_to(cr,14,-183.33*min+188.33);

        cairo_move_to(cr,4,-183.33*max+188.33);
        if(drawlines)
            cairo_line_to(cr,598,-183.33*max+188.33);
        else
            cairo_line_to(cr,14,-183.33*max+188.33);

        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_stroke(cr);
        /********************/
        drawlines = false;
    }

    void draw()
    {

        if (damage() & FL_DAMAGE_ALL)
        {
            cairo_t *cr = Fl::cairo_cc();


            //calcluate scale and centering
            double scalex,
                   scaley;
            //scalex = w/(double)(drawing_w);
            scalex = w/(double)(drawing_w);
            scaley = h/(double)drawing_h;
            cairo_save( cr );

            //move
            cairo_translate(cr,x,y);
            //scale
            cairo_scale(cr,scalex,scaley);
            default_drawing(cr);

            cairo_restore(cr);

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
};

} // ffffltk

#endif // FFF_BACKGROUND_H

