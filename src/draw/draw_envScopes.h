#ifndef DRAW_ENVSCOPES_H
#define DRAW_ENVSCOPES_H
#include"blur.h"
inline int cairo_code_draw_envScope_get_width()
{
    return 600;
}
inline int cairo_code_draw_envScope_get_height()
{
    return 200;
}
inline void cairo_code_draw_blue_envScope_render(cairo_t *cr, float *data, uint16_t start)
{
    cairo_surface_t *temp_surface;
    cairo_t *old_cr = cr;
    cairo_pattern_t *pattern;

    temp_surface = cairo_image_surface_create( CAIRO_FORMAT_ARGB32,600,200);
    cr = cairo_create(temp_surface);

    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 1);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(.3,.6,1,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);

    start = (start-1)&0x7FF;
    cairo_move_to(cr,598,-183.33*data[start]+183.33);
    for(uint16_t i=1; i<596; i++)
    {
        cairo_line_to(cr,598-i,183.33-183.33*data[(start - i)&0x7FF]);
    }

    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_stroke_preserve(cr);
    /********************/

    cairo_set_source_surface(old_cr,temp_surface,0,0);
    cairo_paint(old_cr);
    cairo_surface_destroy(temp_surface);
    cairo_destroy(cr);

}

inline void cairo_code_draw_green_envScope_render(cairo_t *cr, float *data, uint16_t start)
{
    cairo_surface_t *temp_surface;
    cairo_t *old_cr = cr;
    cairo_pattern_t *pattern;

    temp_surface = cairo_image_surface_create( CAIRO_FORMAT_ARGB32,600,200);
    cr = cairo_create(temp_surface);

    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 1);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0,1,0,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);

    start = (start-1)&0x7FF;
    cairo_move_to(cr,598,-183.33*data[start]+183.33);
    for(uint16_t i=1; i<596; i++)
    {
        cairo_line_to(cr,598-i,183.33-183.33*data[(start - i)&0x7FF]);
    }

    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_stroke_preserve(cr);
    /********************/

//blur_image_surface(temp_surface,3);
    cairo_set_source_surface(old_cr,temp_surface,0,0);
    cairo_paint(old_cr);
    cairo_surface_destroy(temp_surface);
    cairo_destroy(cr);

}
#endif
