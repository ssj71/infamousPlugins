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


#ifndef FFF_CELLGRID_H
#define FFF_CELLGRID_H


#include <FL/Fl_Widget.H>
#include <FL/Fl.H>
#include <valarray>
#include <string>

//avtk drawing method (adapted)
static void default_cell_drawing(cairo_t *cr,int v)
{
    v++;
};

namespace ffffltk
{

class CellGrid: public Fl_Widget
{
public:
    CellGrid(int _x, int _y, int _w, int _h, const char *_label = ""):
        Fl_Widget(_x, _y, _w, _h, _label)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;

        label = _label;

        drawing_w = 100;
        drawing_h = 100;
        drawing_f = &default_cell_drawing;

        rule = 30;
        initial_condition = 1;
    }
    int x, y, w, h;
    const char* label;

    int drawing_w;
    int drawing_h;
    void (*drawing_f)(cairo_t*,int);//pointer to draw function

    uint8_t rule;
    uint16_t initial_condition;

    void draw()
    {
        if (damage() & FL_DAMAGE_ALL)
        {
            cairo_t *cr = Fl::cairo_cc();

            //calcluate scale and centering
            double scalex,
                   scaley,
                   offset = 0;//distance between leds
            scalex = w/(double)(drawing_w*24);//1.5*16=24
            scaley = h/(double)drawing_h;
            if(scalex > scaley)
            {
                scalex = scaley;
            }
            else
            {
                scaley = scalex;
            }
            offset = scalex*1.5*drawing_w;//1.5 so there is a space between

            //call the draw function for each character
            int nrows = h/offset;
            uint16_t cells = initial_condition,
                     temp=0;
            for (int i=0; i<nrows; i++)
            {
                for (int j=0; j<16; j++)
                {

                    int v = cells&0x8000>>j;
                    cairo_save( cr );

                    //move
                    cairo_translate(cr,x+j*offset,y+i*offset);
                    //scale
                    cairo_scale(cr,scalex,scaley);
                    if(drawing_f) drawing_f(cr,v);
                    else default_cell_drawing(cr,v);

                    cairo_restore(cr);
                }

                //calculate cells
                temp = 0;
                for(uint8_t index=0; index<=15; index++)
                {
                    //the idea is to shift the rule mask (w/rollover) according to the 3
                    //bits in the neighborhood at $index, mask that bit in the rule to
                    //then determine the next cell state and OR it into a temp value
                    //       |cell state-----------------------------------------------|
                    //               | rule mask ---------------------------------|
                    //                   |neighborhood ---------------------------|
                    temp |= ((rule & 1<<((cells>>index|cells<<(15-index+1) )&7) )>0)<<index;
                }
                cells=temp<<1|temp>>15;
            }//rows
        }//if damage
    }//end draw

    void resize(int X, int Y, int W, int H)
    {
        Fl_Widget::resize(X,Y,W,H);
        x = X;
        y = Y;
        w = W;
        h = H;
        redraw();
    }
};//class
} // ffffltk

#endif // FFF_CELLGRIDD_H

