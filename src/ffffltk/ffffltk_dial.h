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


#ifndef FFF_DIAL_H
#define FFF_DIAL_H

#include <FL/Fl_Dial.H>
#include <FL/Fl_Slider.H>
#include <FL/fl_ask.H>

//avtk drawing method (adapted)
static void default_bg_drawing(cairo_t *cr, float val)
{
    
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    
    cairo_set_line_width(cr, 3.97);
    cairo_move_to( cr, 50, 50);
    cairo_line_to( cr, 50, 50);
    cairo_set_source_rgba(cr, 0.5, 0.5, 0.5, 0.4 );
    
    // draw dash guide
    double dashes[2];
    cairo_set_line_width(cr, 1.7);
    dashes[0] = 3.0;
    dashes[1] = 3.0;
    cairo_set_dash ( cr, dashes, 2, 0.0);
    cairo_stroke(cr);
    
    cairo_arc(cr, 50,50, 46, 2.46, 0.75 );
    //cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 0.4 );
    cairo_stroke(cr);
    cairo_set_dash ( cr, dashes, 0, 0.0);
    
    float angle = 2.46 + ( 4.54 * val );
    cairo_set_line_width(cr, 4.97);
    cairo_arc(cr, 50,50, 46, 2.46, angle );
    cairo_line_to(cr, 50,50);
    cairo_set_source_rgba(cr, 1.0, 0.48,   0, 1.0);
    cairo_stroke(cr);
}

namespace ffffltk
{

class Dial : public Fl_Slider
{
  public:
    Dial(int _x, int _y, int _w, int _h, const char* _label=0):
        Fl_Slider(_x, _y, _w, _h, _label)
    {
      x = _x;
      y = _y;
      w = _w;
      h = _h;
      
      drawing_w = 100;
      drawing_h = 100;
      drawing_f = &default_bg_drawing;
      
      mouseClickedY = 0;
      mouseClicked = false;
      
//      highlight = false;
      label = _label;
    }
    
 //   bool highlight;
    int x, y, w, h;
    const char* label;
    bool drawLab;
    void drawLabel(bool b){drawLab = b; redraw();}
    
    int mouseClickedY;
    bool mouseClicked;
    

    int drawing_w;
    int drawing_h;
    void (*drawing_f)(cairo_t*,float);//function pointer to draw function

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
        
      }
    }
    
    
    void resize(int X, int Y, int W, int H)
    {
      Fl_Slider::resize(X,Y,W,H);
      x = X;
      y = Y;
      w = W;
      h = H;
      redraw();
    }
    
    int handle(int event)
    {
      //cout << "handle event type = " << event << " value = " << value() << endl;
      
      //Fl_Slider::handle( event );
      
      switch(event) {
        case FL_PUSH:
          //highlight = 1;
	  if(Fl::event_button() == FL_MIDDLE_MOUSE)
	  {
	   // Fl_Window tmp* = new Fl_Window(Fl::event_x(),Fl::event_y(),100,200,"Enter Value");
	    char n[20];
	    float val=0;
	    sprintf(n,"%f",value());
	    if(sscanf(fl_input("Enter Value:",n),"%f",&val))
	    {
              if ( val > maximum() ) val = maximum();
              if ( val < minimum() ) val = minimum();
	      set_value(val);
	    }
            redraw();
	    do_callback();
	  }
          return 1;
        case FL_DRAG:
          {
            if ( Fl::event_state(FL_BUTTON1) )
            {
              if ( mouseClicked == false ) // catch the "click" event
              {
                mouseClickedY = Fl::event_y();
                mouseClicked = true;
              }
              
              float deltaY = mouseClickedY - Fl::event_y();
	      char lable[20];
              
              float val = value();
	      if(step())
	      {
                  val += deltaY *step();/// 100.f*(maximum()-minimum());
	      }
	      else
	      {
	          val += deltaY/100.f;
	      }

              
              if ( val > maximum() ) val = maximum();
              if ( val < minimum() ) val = minimum();
              
              set_value( val );
              
              mouseClickedY = Fl::event_y();
	      sprintf(lable,"%1.4f",val);
	      Fl_Widget::copy_label(lable);
              redraw();
              do_callback(); // makes FLTK call "extra" code entered in FLUID
            }
          }
          return 1;
        case FL_RELEASE:
          //if (highlight) {
           // highlight = 0;
	    Fl_Widget::copy_label("");
            redraw();
            // never do anything after a callback, as the callback
            // may delete the widget!
          //}
          mouseClicked = false;
          return 1;
        default:
          return Fl_Widget::handle(event);
      }
    }
};

} // ffffltk

#endif // FFF_DIAL_H
