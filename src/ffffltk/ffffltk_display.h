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


#ifndef FFF_DISPLAY_H
#define FFF_DISPLAY_H


#include <FL/Fl_Widget.H>
#include <valarray>
#include <string>
#include <cairo.h>

//avtk drawing method (adapted)
static void default_display_drawing(cairo_t *cr, char c)
{
}

static void default_rgb_display_drawing(cairo_t *cr, char c, float r, float g, float b)
{
}

namespace ffffltk
{

class AsciiDisplay: public Fl_Widget
{
public:
    AsciiDisplay(int _x, int _y, int _w, int _h, const char *_label = ""):
        Fl_Widget(_x, _y, _w, _h, _label)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;

        //label = _label;

        drawing_w = 100;
        drawing_h = 100;
        drawing_f = &default_display_drawing;

        nchars = 1;
        periods = true;
    }
    int x, y, w, h;
    //const char* label;

    int drawing_w;
    int drawing_h;
    void (*drawing_f)(cairo_t*,char);//pointer to draw function
    int nchars;
    bool periods;//flag, states that periods are treated as a full character (monospace)

    void draw()
    {
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
                    c = ' ';
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

//this special display is for ascii that changes colors (the whole message is always 1 textcolor)
class RGBAsciiDisplay: public Fl_Widget
{
public:
    RGBAsciiDisplay(int _x, int _y, int _w, int _h, const char *_label = ""):
        Fl_Widget(_x, _y, _w, _h, _label)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;

        //label = _label;

        drawing_w = 100;
        drawing_h = 100;
        drawing_f = &default_rgb_display_drawing;

        nchars = 1;
        periods = true;
        r = g = b = 1;
        textcolor = WHITE_COLOR;
    }
    int x, y, w, h;
    //const char* label;
    typedef enum
    {
        CUSTOM_COLOR,
        RED_COLOR,
        ORANGE_COLOR,
        YELLOW_COLOR,
        GREEN_COLOR,
        BLUE_COLOR,
        PURPLE_COLOR,
        WHITE_COLOR 
    } color_t;

    int drawing_w;
    int drawing_h;
    void (*drawing_f)(cairo_t*,char,float r, float g, float b);//pointer to draw function
    int nchars;
    bool periods;//flag, states that periods are treated as a full character (monospace)
    float r,g,b;
    color_t textcolor;

    void copy_label(const char* new_label, float _r, float _g, float _b)
    {
        textcolor = CUSTOM_COLOR;
        r = _r;
        g = _g;
        b = _b;
        Fl_Widget::copy_label(new_label);
    }
    void copy_label(const char* new_label, color_t c)
    {
        textcolor = c;
        switch(c)
        {
            case RED_COLOR:
                copy_label(new_label,1,0,0);
                break;
            case ORANGE_COLOR:
                copy_label(new_label,1,0.33333,0);
                break;
            case YELLOW_COLOR:
                copy_label(new_label,0.92157,0.92157,0);
                break;
            case GREEN_COLOR:
                copy_label(new_label,0,0.88235,0);
                break;
            case BLUE_COLOR:
                copy_label(new_label,0.1,0.2,1);
                break;
            case PURPLE_COLOR:
                copy_label(new_label,0.78431,0,1);
                break;
            case WHITE_COLOR:
                copy_label(new_label,1,1,1);
                break;
            case CUSTOM_COLOR:
                copy_label(new_label,r,g,b);//no change in textcolor since they haven't redefined it
                break;
        }
    }

    void draw()
    {
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
                    c = ' ';
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
                if(drawing_f) drawing_f(cr,c,r,g,b);
                else default_rgb_display_drawing(cr,c,r,g,b);

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

