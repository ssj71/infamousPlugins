#include "tk_default_draw.h"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

typedef struct
{
    cairo_surface_t* knob;
    cairo_surface_t* needle; 
    float scale;
}mycache;

void tk_drawbasicdial(cairo_t *cr, float w, float h, void* cache, void* valp)
{
    float scale, shft, val = *(float*)valp;
    cairo_pattern_t *pattern; 
    cairo_matrix_t matrix;
    mycache* mc;

    scale = w/47.0;
    if(cache)
        mc = (mycache*)cache;
    if(!cache || (scale/mc->scale)>2.0)
    {
            
        cairo_t* tmpcr = cr;
        if(!cache)
        {
            mc = (void*)malloc(sizeof(mycache));
            cache = mc;
        }
        else
        {
            cairo_surface_destroy(mc->knob);
            cairo_surface_destroy(mc->needle);
        }
        mc->knob = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,47.5*scale,47.5*scale);
        mc->needle = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,47.5*scale,47.5*scale);
        mc->scale = scale;

        cr = cairo_create(mc->knob);
        cairo_scale(cr,scale,scale);

        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_radial(78.072823, 172.32506, 0, 78.072823, 172.32506, 20.063856);
        cairo_pattern_add_color_stop_rgba(pattern, 0,0,0,0,1);
        cairo_pattern_add_color_stop_rgba(pattern, 0.892578,1,1,1,1);
        cairo_pattern_add_color_stop_rgba(pattern, 1,0,0,0,0);

        cairo_matrix_init(&matrix, -0.024135,0.178731,-0.202277,-0.0213257,85.379285,167.713406);
        cairo_pattern_set_matrix(pattern, &matrix);
        cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
        cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 46.757812, 23.648438);
        cairo_curve_to(cr, 46.757812, 36.429688, 36.398438, 46.789062, 23.617188, 46.789062);
        cairo_curve_to(cr, 10.839844, 46.789062, 0.480469, 36.429688, 0.480469, 23.648438);
        cairo_curve_to(cr, 0.480469, 10.871094, 10.839844, 0.511719, 23.617188, 0.511719);
        cairo_curve_to(cr, 36.398438, 0.511719, 46.757812, 10.871094, 46.757812, 23.648438);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
         /********************/
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        cairo_set_line_width(cr, 0.842);
        cairo_set_miter_limit(cr, 4);
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
        pattern = cairo_pattern_create_rgba(0,0,0,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT); 
        cairo_stroke(cr);
        /********************/

        cairo_destroy(cr);
        cr = cairo_create(mc->needle);
        cairo_scale(cr,scale,scale);

        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(1,1,1,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 21.476562, 2.703125);
        cairo_line_to(cr, 25.761719, 2.703125);
        cairo_line_to(cr, 25.761719, 11.988281);
        cairo_line_to(cr, 21.476562, 11.988281);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
         /********************/
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        cairo_set_line_width(cr, 0.842);
        cairo_set_miter_limit(cr, 4);
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
        pattern = cairo_pattern_create_rgba(0,0,0,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_stroke(cr);
        /********************/
        cairo_destroy(cr);
        cr = tmpcr;
    }

    scale /= mc->scale;
    cairo_save( cr );
    cairo_scale(cr,scale,scale);

    cairo_set_source_surface(cr,mc->knob,0,0);
    cairo_paint(cr);

    shft = 23.5*mc->scale;
    cairo_translate(cr,shft,shft);
    cairo_rotate(cr,3*M_PI/2*val - 3*M_PI/4);
    cairo_translate(cr,-shft, -shft);

    cairo_set_source_surface(cr,mc->needle,0,0);
    cairo_paint(cr);

    cairo_restore( cr );
}
