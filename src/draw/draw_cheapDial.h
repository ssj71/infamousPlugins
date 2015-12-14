#ifndef DRAW_CHEAPDIAL_H
#define DRAW_CHEAPDIAL_H
inline int cairo_code_draw_cheapDial_get_width()
{
    return 99;
}
inline int cairo_code_draw_cheapDial_get_height()
{
    return 119;
}
inline void cairo_code_draw_cheapDial_render(cairo_t *cr, float val)
{
    cairo_pattern_t *pattern;

    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 10);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0,0,0,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 93.507812, 19.648438);
    cairo_line_to(cr, 77.851562, 19.648438);
    cairo_line_to(cr, 77.851562, 5);
    cairo_line_to(cr, 20.65625, 5);
    cairo_line_to(cr, 20.65625, 19.648438);
    cairo_line_to(cr, 5, 19.648438);
    cairo_line_to(cr, 5, 99.109375);
    cairo_line_to(cr, 20.65625, 99.109375);
    cairo_line_to(cr, 20.65625, 113.757812);
    cairo_line_to(cr, 77.851562, 113.757812);
    cairo_line_to(cr, 77.851562, 99.109375);
    cairo_line_to(cr, 93.507812, 99.109375);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_stroke_preserve(cr);
    /********************/
    if(val<.33334)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(0,0,0,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 44.753906, 32.414062);
        cairo_line_to(cr, 53.824219, 32.34375);
        cairo_line_to(cr, 53.753906, 50.414062);
        cairo_line_to(cr, 53.753906, 77.414062);
        cairo_line_to(cr, 62.753906, 77.414062);
        cairo_line_to(cr, 62.753906, 86.414062);
        cairo_line_to(cr, 35.753906, 86.414062);
        cairo_line_to(cr, 35.753906, 77.414062);
        cairo_line_to(cr, 44.753906, 77.414062);
        cairo_line_to(cr, 44.753906, 50.414062);
        cairo_line_to(cr, 35.753906, 50.414062);
        cairo_line_to(cr, 35.753906, 41.414062);
        cairo_line_to(cr, 44.753906, 41.414062);
        cairo_line_to(cr, 44.753906, 32.414062);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    else if(val<.666667)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(0,0,0,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 44.753906, 32.414062);
        cairo_line_to(cr, 53.824219, 32.34375);
        cairo_line_to(cr, 53.753906, 41.414062);
        cairo_line_to(cr, 44.753906, 41.414062);
        cairo_line_to(cr, 44.753906, 32.414062);
        cairo_move_to(cr, 35.753906, 41.414062);
        cairo_line_to(cr, 44.753906, 41.414062);
        cairo_line_to(cr, 44.753906, 50.414062);
        cairo_line_to(cr, 35.753906, 50.414062);
        cairo_line_to(cr, 35.753906, 41.414062);
        cairo_move_to(cr, 53.753906, 41.414062);
        cairo_line_to(cr, 62.753906, 41.414062);
        cairo_line_to(cr, 62.753906, 59.414062);
        cairo_line_to(cr, 53.753906, 59.414062);
        cairo_line_to(cr, 53.753906, 41.414062);
        cairo_move_to(cr, 44.753906, 59.414062);
        cairo_line_to(cr, 53.753906, 59.414062);
        cairo_line_to(cr, 53.753906, 68.414062);
        cairo_line_to(cr, 44.753906, 68.414062);
        cairo_line_to(cr, 44.753906, 59.414062);
        cairo_move_to(cr, 35.753906, 68.414062);
        cairo_line_to(cr, 44.753906, 68.414062);
        cairo_line_to(cr, 44.753906, 77.414062);
        cairo_line_to(cr, 62.753906, 77.414062);
        cairo_line_to(cr, 62.753906, 86.414062);
        cairo_line_to(cr, 35.753906, 86.414062);
        cairo_line_to(cr, 35.753906, 68.414062);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    else
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(0,0,0,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 35.753906, 32.378906);
        cairo_line_to(cr, 62.753906, 32.378906);
        cairo_line_to(cr, 62.753906, 50.378906);
        cairo_line_to(cr, 53.753906, 50.378906);
        cairo_line_to(cr, 53.753906, 59.378906);
        cairo_line_to(cr, 62.753906, 59.378906);
        cairo_line_to(cr, 62.753906, 77.378906);
        cairo_line_to(cr, 53.753906, 77.378906);
        cairo_line_to(cr, 53.753906, 86.378906);
        cairo_line_to(cr, 44.753906, 86.378906);
        cairo_line_to(cr, 44.753906, 77.378906);
        cairo_line_to(cr, 35.753906, 77.378906);
        cairo_line_to(cr, 35.753906, 68.378906);
        cairo_line_to(cr, 44.753906, 68.378906);
        cairo_line_to(cr, 44.753906, 77.378906);
        cairo_line_to(cr, 53.753906, 77.378906);
        cairo_line_to(cr, 53.753906, 59.378906);
        cairo_line_to(cr, 44.753906, 59.378906);
        cairo_line_to(cr, 44.753906, 50.378906);
        cairo_line_to(cr, 53.753906, 50.378906);
        cairo_line_to(cr, 53.753906, 41.378906);
        cairo_line_to(cr, 35.753906, 41.378906);
        cairo_line_to(cr, 35.753906, 32.378906);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
}
#endif
