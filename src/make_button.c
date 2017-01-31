#include <cairo.h>
#include <cairo-svg.h>
#include <math.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include "draw/draw_powerButton.h"

//to use this you must remove 'inline' from the function
// gcc -Wall -g make_button.c -lm `pkg-config --cflags --libs cairo` -o buttonmake

#ifndef min
#define min(x, y) ((x) < (y) ? (x) : (y))
#endif
#ifndef max
#define max(x, y) ((x) < (y) ? (y) : (x))
#endif

const double scale_zero = 20 * (M_PI/180); // defines "dead zone" for knobs


int main(int argc, char* argv[])
{

    int knob_offset = 0;
    int imgw = 160;
    int imgh = 64;
   
    char png_file[80];
    char svg_file[80];
    sprintf(png_file, "button.png");
    sprintf(svg_file, "button.svg");

    /** use this instead the svg surface when you don't need the svg format **/
    //cairo_surface_t *frame = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, knob_size, knob_size);
    cairo_surface_t *frame = cairo_svg_surface_create(NULL, imgw, imgh);
    cairo_t *crf = cairo_create(frame);
    /** use this instead the svg surface when you don't need the svg format **/
    //cairo_surface_t *knob_img = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, knob_image_widht, knob_size);
    cairo_surface_t *knob_img = cairo_svg_surface_create(svg_file, imgw, imgh*2);
    cairo_t *cr = cairo_create(knob_img);

    /** draw the widgets to image **/
    cairo_code_draw_powerButton_render(cr,0);

    cairo_translate(cr,0,imgh);
    cairo_code_draw_powerButton_render(cr,1);

    /** save to png file **/
    cairo_surface_flush(knob_img);
    cairo_surface_write_to_png(knob_img, png_file);

    /** clean up **/
    cairo_destroy(crf);
    cairo_destroy(cr);
    cairo_surface_destroy(knob_img);
    cairo_surface_destroy(frame);
    return 0;
}

