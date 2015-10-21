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


#ifndef FFF_LUSHLIFE_GRAPH_GROUP_H
#define FFF_LUSHLIFE_GRAPH_GROUP_H


#include <FL/Fl_Widget.H>
#include <valarray>
#include <string>
#include "xybounds.h"

//avtk drawing method (adapted)
namespace ffffltk
{

class Graph_Group: public Fl_Group
{
public:
    Graph_Group(int _x, int _y, int _w, int _h, const char *_label = ""):
        Fl_Group(_x, _y, _w, _h, _label)
    {
        x0 = 0; 
    }

    XBound* x0,*x1,*x2,*x3,*x4,*x5;
    YBound* y0,*y1,*y2,*y3,*y4,*y5;

    void draw()
    {
        if (damage() & ~FL_DAMAGE_CHILD)
        {
            if(x0)
            {
                cairo_t *cr = Fl::cairo_cc();

                cairo_save( cr );

                int os;
                int ymn, ymx, xmn, xmx;
                float r,g,b;
                XYhandle* cp = y0->centerpoint;
                XBound *xb;
                YBound *yb;

                cairo_pattern_t *pattern;

                //red
                cp = y0->centerpoint;
                xb = x0;
                yb = y0;
                r=1;g=0;b=0;

                cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
                cairo_set_line_width(cr, 1);
                cairo_set_miter_limit(cr, 1);
                cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
                cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
                pattern = cairo_pattern_create_rgba(r,g,b,1);
                cairo_set_source(cr, pattern);
                cairo_pattern_destroy(pattern);
                cairo_new_path(cr);

                //find drawn size of widgets
                os = xb->h;
                if(os > yb->w)
                    os = yb->w;

                //y trace
                if(y0->active())
                {
                    ymn = yb->y + yb->h;
                    ymx = (cp->y - (yb->y + yb->h)) + cp->y + os;
                }
                else
                {
                    ymn = cp->y;
                    ymx = cp->y + os;
                } 
                if(ymn<y()) ymn = y();
                if(ymx>y()+h()) ymx = y() + h();

                //x trace
                if(x0->active())
                {
                    xmn = xb->x;
                    xmx = (cp->x - xb->x) + cp->x + os;
                }
                else
                {
                    xmn = cp->x;
                    xmx = cp->x + os;
                } 
                if(xmn<x()) xmn = x();
                if(xmx>x()+w()) xmx = x() + w();

                os /= 2;
                cairo_move_to(cr, yb->x+yb->w-os, ymn);
                cairo_line_to(cr, yb->x+yb->w-os, ymx);
                cairo_move_to(cr, xmn, xb->y+os);
                cairo_line_to(cr, xmx, xb->y+os);

                cairo_set_tolerance(cr, 0.1);
                cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
                cairo_stroke_preserve(cr);

                cairo_restore( cr );
            }
        }
        draw_children();
    }

    void set_graph(XBound*_x0,YBound*_y0,XBound*_x1,YBound*_y1,
        XBound*_x2,YBound*_y2,XBound*_x3,YBound*_y3,
        XBound*_x4,YBound*_y4,XBound*_x5,YBound*_y5)
    {
        x0 = _x0; y0 = _y0;
        x1 = _x1; y1 = _y1;
        x2 = _x2; y2 = _y2;
        x3 = _x3; y3 = _y3;
        x4 = _x4; y4 = _y4;
        x5 = _x5; y5 = _y5;
    }
};

} // ffffltk

#endif // FFF_BACKGROUND_H

