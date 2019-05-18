#include "tk_default_draw.h"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

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
        cairo_pattern_add_color_stop_rgba(pattern, 0,TK_COLOR_DARK,1);
        cairo_pattern_add_color_stop_rgba(pattern, 0.617951,TK_COLOR_LIGHT,1);
        cairo_pattern_add_color_stop_rgba(pattern, 0.67006,TK_COLOR_LIGHT,1);
        cairo_pattern_add_color_stop_rgba(pattern, 1,TK_COLOR_DARK,1);
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

void tk_drawbutton(cairo_t *cr, float w, float h, void* cache, void* valp)
{
    bool val = *(bool*)valp;
    cairo_pattern_t *pattern;
    const float curve = 4.5;
    const float width = 1.0;

    cairo_save( cr );

    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    if(val)
        pattern = cairo_pattern_create_rgba(TK_COLOR_LIGHT,1);
    else
        pattern = cairo_pattern_create_rgba(TK_COLOR_MAIN,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, curve, width);
    cairo_line_to(cr, w-curve, width);
    cairo_curve_to(cr, w-curve, width, w-width, width, w-width, curve);
    cairo_line_to(cr, w-width, h-curve);
    cairo_curve_to(cr, w-width, h-curve, w-width, h-width, w-curve, h-width);
    cairo_line_to(cr, curve, h-width);
    cairo_curve_to(cr, curve, h-width, width, h-width, width, h-curve);
    cairo_line_to(cr, width, curve);
    cairo_curve_to(cr, width, curve, width, width, curve, width);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, width);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
    cairo_fill_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 2*width);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0,0,0,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_stroke(cr);

    cairo_restore(cr);
}

void tk_drawdial(cairo_t *cr, float w, float h, void* cache, void* valp)
{
    float val = *(float*)valp;
    cairo_pattern_t *pattern;
    const float width = 1.0;
    float unit;

    cairo_save( cr );

    if(w > h)
    {
        unit = h/2.0-width;
        cairo_translate(cr,0,(w-h)/2.0);
    }
    else
    {
        unit = w/2.0-width;
        cairo_translate(cr,(h-w)/2.0,0);
    }
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_rgba(TK_COLOR_MAIN,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_arc(cr,unit,unit,unit,0,2*M_PI);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, width);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
    cairo_fill_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 2*width);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0,0,0,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_stroke(cr);
    /********************/

    cairo_translate(cr,unit,unit);
    cairo_rotate(cr,3*M_PI/2*val - 3*M_PI/4);
    cairo_translate(cr,-unit,-unit);

    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_rgba(TK_COLOR_LIGHT,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, .9*unit, .2*unit);
    cairo_line_to(cr, 1.1*unit, .2*unit);
    cairo_line_to(cr, 1.1*unit, .65*unit);
    cairo_line_to(cr, .9*unit, .65*unit);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, width);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
    cairo_fill_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 2*width);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0,0,0,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_stroke(cr);

    cairo_restore(cr);
}
