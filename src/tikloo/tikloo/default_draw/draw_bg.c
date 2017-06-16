#include "tk_default_draw.h"

void tk_drawnothing(cairo_t *cr, float w, float h, void* c, void* v)
{
    (void)cr;(void)w;(void)h;(void)c;(void)v;
}

typedef struct
{
    cairo_surface_t* surf;
    float w,h;
}mycache;

void tk_drawbg(cairo_t *cr, float w, float h, void* cache, void* valp)
{
    cairo_pattern_t *pattern;
    mycache* mc;
    float xscale,yscale;

    (void)valp;
    if(cache)
        mc = (mycache*)cache;
    if(!cache || w/mc->w>2.0 || h/mc->h>2.0)
    {
        cairo_t* tmpcr = cr;
        if(!cache)
        {
            mc = (void*)malloc(sizeof(mycache));
            cache = mc;
        }
        else
            cairo_surface_destroy(mc->surf);
        mc->surf = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,w,h);
        mc->w = w;
        mc->h = h;
        cr = cairo_create(mc->surf);

        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_linear(.3*w, 0, .8*w, h);
        cairo_pattern_add_color_stop_rgba(pattern, 0,.4,.4,.4,1);
        cairo_pattern_add_color_stop_rgba(pattern, 0.517951,.7,.7,.7,1);
        cairo_pattern_add_color_stop_rgba(pattern, 0.67006,.7,.7,.7,1);
        cairo_pattern_add_color_stop_rgba(pattern, 1,.4,.4,.4,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 0,0);
        cairo_line_to(cr, w, 0);
        cairo_line_to(cr, w, h);
        cairo_line_to(cr, 0, h);
        cairo_line_to(cr, 0, 0);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill(cr);

        cairo_destroy(cr);
        cr = tmpcr;
    }
    xscale = w/mc->w;
    yscale = h/mc->h;
    cairo_save( cr );
    cairo_scale(cr,xscale,yscale);
    cairo_set_source_surface(cr,mc->surf,0,0);
    cairo_paint(cr);
    cairo_restore( cr );
}
