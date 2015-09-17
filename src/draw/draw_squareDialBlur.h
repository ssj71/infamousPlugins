#ifndef DRAW_SQUAREDIAL_H
#define DRAW_SQUAREDIAL_H
#include "blur.h"
inline int cairo_code_draw_squareDial_get_width()
{
    return 88;
}
inline int cairo_code_draw_squareDial_get_height()
{
    return 88;
}
inline void cairo_code_draw_squareDial_render(cairo_t *cr, int ccw, float r, float g, float b, float val)
{
    cairo_surface_t *temp_surface;
    cairo_t *old_cr;
    cairo_pattern_t *pattern;
    cairo_matrix_t matrix;

//blur stuff
    temp_surface = cairo_image_surface_create ( CAIRO_FORMAT_ARGB32, 88,88);//w,h
    old_cr = cr;
    cr = cairo_create(temp_surface);

    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 6);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(r,g,b,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);

    if(!ccw)
    {
        cairo_move_to(cr, 84.9, 84.9);
        cairo_line_to(cr, 3.1, 84.9);
        if(val<.4)
        {
            cairo_line_to(cr, 3.1, (val/.4)*9.1 + (1-val/.4)*84.9 - 6);
        }
        else if(val<.6)
        {
            cairo_line_to(cr, 3.1, 3.1);
            cairo_line_to(cr, ((val-.4)/.2)*84.9 + (1-(val-.4)/.2)*3.1, 3.1);
        }
        else
        {
            cairo_line_to(cr, 3.1, 3.1);
            cairo_line_to(cr, 84.9, 3.1);
            cairo_line_to(cr, 84.9, ((val-.6)/.4)*75.9 + (1-(val-.6)/.4)*3.1);
        }
    }
    else
    {
        cairo_move_to(cr, 3.1, 84.9);
        cairo_line_to(cr, 84.9, 84.9);
        val = 1-val;
        if(val<.4)
        {
            cairo_line_to(cr, 84.9, (val/.4)*9.1 + (1-val/.4)*84.9 - 6);
        }
        else if(val<.6)
        {
            cairo_line_to(cr, 84.9, 3.1);
            cairo_line_to(cr, ((val-.4)/.2)*3.1 + (1-(val-.4)/.2)*84.9, 3.1);
        }
        else
        {
            cairo_line_to(cr, 84.9, 3.1);
            cairo_line_to(cr, 3.1, 3.1);
            cairo_line_to(cr, 3.1, ((val-.6)/.4)*75.9 + (1-(val-.6)/.4)*3.1);
        }
    }

    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_stroke_preserve(cr);
    double xx,yy;
    cairo_surface_get_device_offset(cairo_get_target(old_cr),&xx,&yy);
    blur_image_surface(temp_surface, 10);
    cairo_set_source_surface(old_cr,temp_surface,xx,yy);
    cairo_paint(old_cr);
    cairo_surface_destroy(temp_surface);
    cairo_destroy(cr);
    /********************/
}
inline void cairo_code_draw_squareDialr_render(cairo_t *cr, float val)
{
    cairo_code_draw_squareDial_render(cr, 0, 1, 0, 0, val);
}

inline void cairo_code_draw_squareDialbccw_render(cairo_t *cr, float val)
{
    cairo_code_draw_squareDial_render(cr, 1, 0, 0, 1, val);
}

inline void cairo_code_draw_squareDialgccw_render(cairo_t *cr, float val)
{
    cairo_code_draw_squareDial_render(cr, 1, 0, 0.88235, 0, val);
}

inline void cairo_code_draw_squareDialo_render(cairo_t *cr, float val)
{
    cairo_code_draw_squareDial_render(cr, 0, 1, .33333, 0, val);
}

inline void cairo_code_draw_squareDialy_render(cairo_t *cr, float val)
{
    cairo_code_draw_squareDial_render(cr, 0, 0.92157, 0.92157, 0, val);
}

inline void cairo_code_draw_squareDialpccw_render(cairo_t *cr, float val)
{
    cairo_code_draw_squareDial_render(cr, 1, 0.78431, 0, 1, val);
}
#endif
