#ifndef DRAW_CASBG_H
#define DRAW_CASBG_H
inline int cairo_code_draw_casbg_get_width()
{
    return 460;
}
inline int cairo_code_draw_casbg_get_height()
{
    return 600;
}
inline void cairo_code_draw_casbg_render(cairo_t *cr)
{
    cairo_pattern_t *pattern;
    cairo_matrix_t matrix;

    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_linear(184.28572, 485.93359, 701.42859, 678.79071);
    cairo_pattern_add_color_stop_rgba(pattern, 0,0.501961,0.501961,0.501961,1);
    cairo_pattern_add_color_stop_rgba(pattern, 0.5,0.666667,0.666667,0.666667,1);
    cairo_pattern_add_color_stop_rgba(pattern, 1,0.592157,0.592157,0.592157,1);
    cairo_matrix_init(&matrix, 1.514798,0,0,1.421429,25.714295,162.362159);
    cairo_pattern_set_matrix(pattern, &matrix);
    cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
    cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_paint(cr);
    /********************/
}
#endif
