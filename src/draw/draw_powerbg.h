#ifndef DRAW_POWERBG_H
#define DRAW_POWERBG_H
inline int cairo_code_draw_powerbg_get_width()
{
    return 487;
}
inline int cairo_code_draw_powerbg_get_height()
{
    return 317;
}
inline void cairo_code_draw_powerbg_render(cairo_t *cr)
{
    cairo_pattern_t *pattern;
    cairo_matrix_t matrix;

    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_linear(381.83768, 660.42303, 381.83768, 235.14418);
    cairo_pattern_add_color_stop_rgba(pattern, 0,0.3,0.3,0.3,1);
    cairo_pattern_add_color_stop_rgba(pattern, 0.7,0.6,0.6,0.6,1);
    cairo_pattern_add_color_stop_rgba(pattern, 1,0.3,0.3,0.3,1);
    cairo_matrix_init(&matrix, 1.173365,0,0,1.142857,68.571426,221.637735);
    cairo_pattern_set_matrix(pattern, &matrix);
    cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
    cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 24.351562, 0);
    cairo_curve_to(cr, 79.949219, 0.300781, 487, 0, 487, 0);
    cairo_line_to(cr, 487, 317.394531);
    cairo_curve_to(cr, 315.113281, 317.394531, 151.8125, 317.394531, 0, 317.394531);
    cairo_line_to(cr, 0, 24.382812);
    cairo_curve_to(cr, 0, 10.535156, 10.859375, 0, 24.351562, 0);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
    cairo_fill_preserve(cr);
    /********************/
}
#endif
