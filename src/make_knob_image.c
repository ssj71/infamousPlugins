#include <cairo.h>
#include <cairo-svg.h>
#include <math.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include "draw/draw_silverDial.h"
#include "draw/draw_squareDial.h"

//to use this you must remove 'inline' from the function
// gcc -Wall -g make_knob_image.c -lm `pkg-config --cflags --libs cairo` -o knobmake

#ifndef min
#define min(x, y) ((x) < (y) ? (x) : (y))
#endif
#ifndef max
#define max(x, y) ((x) < (y) ? (y) : (x))
#endif
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const double scale_zero = 20 * (M_PI/180); // defines "dead zone" for knobs


int main(int argc, char* argv[])
{
    if (argc < 3) {
        fprintf(stdout, "usage: %s knob_size frame_count [offset] \n", basename(argv[0]));
        return 1;
    }

    int knob_size = atoi(argv[1]);
    int knob_frames = atoi(argv[2]);
    int knob_image_width = knob_size * knob_frames;
    int knob_offset = 0;
    if (argc >= 4) {
        knob_offset = atoi(argv[3]);
    }
   
    char* sz = argv[1];
    char* fr = argv[2];
    char png_file[80];
    char svg_file[80];
    sprintf(png_file, "knob_%sx%s.png", sz,fr);
    sprintf(svg_file, "knob_%sx%s.svg", sz,fr);

    /** use this instead the svg surface when you don't need the svg format **/
    //cairo_surface_t *frame = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, knob_size, knob_size);
    cairo_surface_t *frame = cairo_svg_surface_create(NULL, knob_size, knob_size);
    cairo_t *crf = cairo_create(frame);
    /** use this instead the svg surface when you don't need the svg format **/
    //cairo_surface_t *knob_img = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, knob_image_widht, knob_size);
    cairo_surface_t *knob_img = cairo_svg_surface_create(svg_file, knob_image_width, knob_size);
    cairo_t *cr = cairo_create(knob_img);

    /** draw the knob per frame to image **/
    for (int i = 0; i < knob_frames; i++) {
        //paint_knob_state(crf, knob_size, knob_offset, (double)((double)i/ knob_frames));
        cairo_save(cr);
        cairo_translate(cr,i*(knob_size+knob_offset),0);
        //cairo_code_draw_silverDial_render(cr,(float)i/(knob_frames-1));
        cairo_code_draw_squareDialbccw_render(cr,(float)i/(knob_frames-1));
        //cairo_code_draw_squareDialbccw_render(cr,(float)i/(knob_frames-1));
        //cairo_code_draw_squareDialgccw_render(cr,(float)i/(knob_frames-1));
        //cairo_code_draw_squareDialo_render(cr,(float)i/(knob_frames-1));
        //cairo_code_draw_squareDialy_render(cr,(float)i/(knob_frames-1));
        //cairo_code_draw_squareDialpccw_render(cr,(float)i/(knob_frames-1));
        cairo_restore(cr);
        /*
        cairo_set_source_surface(cr, frame, knob_size*i, 0);
        cairo_paint(cr);
        cairo_set_operator(crf,CAIRO_OPERATOR_CLEAR);
        cairo_paint(crf);
        cairo_set_operator(crf,CAIRO_OPERATOR_OVER);
        */
    }

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

