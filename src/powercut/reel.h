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


#ifndef FFF_REEL_H
#define FFF_REEL_H


#include <FL/Fl_Widget.H>
#include <FL/Fl.H>
#include <valarray>
#include <string>
#include"draw_reel.h"

//avtk drawing method (adapted)
namespace ffffltk
{

static void reel_callback(void* handle);

class PowerReel: public Fl_Widget
{
public:
    PowerReel(int _x, int _y, int _w, int _h, const char *_label = ""):
        Fl_Widget(_x, _y, _w, _h, _label)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;

        label = _label;

        drawing_w = 100;
        drawing_h = 100;
        stretch = false;

        curve = 0;
        time = .5;
        trigger = 0;

        logosurf = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,cairo_code_draw_reel_get_width(),cairo_code_draw_reel_get_height());//w,h;
        reelsurf = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,cairo_code_draw_reel_get_width(),cairo_code_draw_reel_get_height());//w,h
        logocr = cairo_create(logosurf);
        reelcr = cairo_create(reelsurf);
        cairo_code_draw_reel_logo_render(logocr);
        cairo_code_draw_reel_render(reelcr);

        Fl::add_timeout(.06,reel_callback,this);
    }

    ~PowerReel()
    {
        Fl::remove_timeout(reel_callback);
        //cairo_destroy(logocr);
        //cairo_destroy(reelcr);
        //cairo_surface_destroy(logosurf);
        //cairo_surface_destroy(reelsurf);
    }


    bool highlight;
    int x, y, w, h;
    const char* label;

    int drawing_w;
    int drawing_h;
    void (*drawing_f)(cairo_t*,float);//pointer to draw function
    bool stretch;

    float curve;
    float time;
    float samples;
    int trigger;
    double angle;

    cairo_t *logocr;
    cairo_t *reelcr;
    cairo_surface_t *logosurf;
    cairo_surface_t *reelsurf;

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
            cairo_set_source_surface(cr,logosurf,0,0);
            cairo_paint(cr);
            cairo_translate(cr,drawing_w/2.0,drawing_h/2.0);
            cairo_rotate(cr,angle);
            cairo_translate(cr,-drawing_w/2.0,-drawing_h/2.0);
            cairo_set_source_surface(cr,reelsurf,0,0);
            cairo_paint(cr);

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
        return 0;

        switch(event)
        {
        case FL_PUSH:
            highlight = 0;
            redraw();
            return 1;
        case FL_DRAG:
        {
            int t = Fl::event_inside(this);
            if (t != highlight)
            {
                redraw();
            }
        }
        return 1;
        case FL_RELEASE:
            if (highlight)
            {
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
};

static void reel_callback(void* handle)
{

    PowerReel* reel = (PowerReel*)handle;
    if(reel->trigger)
    {
        if(reel->samples < reel->time)
        {
            float exp_decay = exp2(reel->curve>0?reel->curve:-reel->curve);

            if(reel->curve > 0)//logarithmic (convex)
            {
                reel->angle += .10/(reel->curve)*log2(exp_decay - (exp_decay-1)*reel->samples/reel->time);
            }
            else if(reel->curve == 0)//linear
            {
                reel->angle += .10*(1-reel->samples/reel->time);
            }
            else//exponential (concave)
            {
                reel->angle += .10*(exp_decay*exp2(reel->samples*reel->curve/reel->time) - 1)/(exp_decay - 1);
            }
            reel->samples++;
        }
    }
    else
    {
        reel->angle += .10;
        reel->samples = 0;
    }
    Fl::repeat_timeout(.06,reel_callback,handle);
    reel->redraw();
};

} // ffffltk

#endif // FFF_BACKGROUND_H

