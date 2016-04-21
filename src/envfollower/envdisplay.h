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


#ifndef FFF_ENVDISPLAY_H
#define FFF_ENVDISPLAY_H


#include <FL/Fl_Widget.H>
#include <valarray>
#include <string>

//avtk drawing method (adapted)
static void default_env_display_drawing(cairo_t *cr, char c)
{
}


namespace ffffltk
{

class EnvAsciiDisplay: public Fl_Widget
{
public:
    EnvAsciiDisplay(int _x, int _y, int _w, int _h, const char *_label = ""):
        Fl_Widget(_x, _y, _w, _h, _label)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;

        //label = _label;

        drawing_w = 100;
        drawing_h = 100;
        drawing_f = &default_env_display_drawing;

        nchars = 1;
        periods = true;

        bgcr = 0;
    }

    ~EnvAsciiDisplay()
    {
        cairo_surface_destroy(bgsurf);
        cairo_destroy(bgcr);
    }

    int x, y, w, h;
    //const char* label;

    int drawing_w;
    int drawing_h;
    void (*drawing_f)(cairo_t*,char);//pointer to draw function
    void (*bg_drawing_f)(cairo_t*);//pointer to draw function
    int nchars;
    bool periods;

    cairo_t * bgcr;
    cairo_surface_t *bgsurf;

    void draw()
    {

        if(!bgcr)
        {
            //initialize bg
            bgsurf  = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,w,h);//w,h;
            bgcr = cairo_create(bgsurf);
            bg_drawing_f(bgcr);
        }
        if (damage() & FL_DAMAGE_ALL)
        {
            cairo_t *cr = Fl::cairo_cc();


            //calcluate scale and centering
            double scalex,
                   scaley,
                   shiftx=0,
                   shifty=0,
                   offset = 0;//distance between characters
            //scalex = w/(double)(drawing_w);
            scalex = w/(double)(drawing_w*nchars);
            scaley = h/(double)drawing_h;
            if(scalex > scaley)
            {
                scalex = scaley;
                shiftx = (w - scalex*drawing_w*nchars)/2.f;
                //shiftx = (w - scalex*drawing_w)/2.f;
            }
            else
            {
                scaley = scalex;
                shifty = h - scaley*drawing_h;
            }
            offset = scalex*drawing_w;

            //call the draw function for each character
            const char* str = label();
            char c;
            int j = 0;
            for (int i=0; i<nchars; i++)
            {
                c = str[j++];
                if(c == 0)
                {
                    //draw blanks
                    j--;
                }
                else if(!periods && str[j] == '.')
                {
                    c+=128;//add period to digit
                    j++;
                }

                cairo_save( cr );

                //move
                cairo_translate(cr,x+shiftx+i*offset,y+shifty);
                //scale
                cairo_scale(cr,scalex,scaley);
                cairo_set_source_surface(cr,bgsurf,0,0);
                cairo_paint(cr);
                if(drawing_f) drawing_f(cr,c);
                else default_display_drawing(cr,c);

                cairo_restore(cr);
            }

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

