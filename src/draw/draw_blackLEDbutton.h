#ifndef DRAW_BLACKLEDBUTTON_H
#define DRAW_BLACKLEDBUTTON_H
inline int cairo_code_draw_blackLEDbutton_get_width()
{
    return 30;
}
inline int cairo_code_draw_blackLEDbutton_get_height()
{
    return 45;
}
inline void cairo_code_draw_blackLEDbutton_render(cairo_t *cr, int val)
{
    cairo_pattern_t *pattern;
    cairo_matrix_t matrix;

    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_rgba(0.101961,0.101961,0.101961,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 3.742188, 0.75);
    cairo_line_to(cr, 26.476562, 0.75);
    cairo_curve_to(cr, 28.132812, 0.75, 29.476562, 2.089844, 29.476562, 3.746094);
    cairo_line_to(cr, 29.476562, 41.539062);
    cairo_curve_to(cr, 29.476562, 43.195312, 28.132812, 44.539062, 26.476562, 44.539062);
    cairo_line_to(cr, 3.742188, 44.539062);
    cairo_curve_to(cr, 2.082031, 44.539062, 0.742188, 43.195312, 0.742188, 41.539062);
    cairo_line_to(cr, 0.742188, 3.746094);
    cairo_curve_to(cr, 0.742188, 2.089844, 2.082031, 0.75, 3.742188, 0.75);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
    cairo_fill_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 1.5);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0,0,0,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 3.742188, 0.75);
    cairo_line_to(cr, 26.476562, 0.75);
    cairo_curve_to(cr, 28.132812, 0.75, 29.476562, 2.089844, 29.476562, 3.746094);
    cairo_line_to(cr, 29.476562, 41.539062);
    cairo_curve_to(cr, 29.476562, 43.195312, 28.132812, 44.539062, 26.476562, 44.539062);
    cairo_line_to(cr, 3.742188, 44.539062);
    cairo_curve_to(cr, 2.082031, 44.539062, 0.742188, 43.195312, 0.742188, 41.539062);
    cairo_line_to(cr, 0.742188, 3.746094);
    cairo_curve_to(cr, 0.742188, 2.089844, 2.082031, 0.75, 3.742188, 0.75);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
//cairo_matrix_init(&matrix, 1,0,0,1,-728.0625,-186.71875);
//cairo_pattern_set_matrix(pattern, &matrix);
    cairo_stroke_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 1);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0.301961,0.301961,0.301961,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 28.3125, 15.34375);
    cairo_line_to(cr, 1.875, 15.34375);
    cairo_line_to(cr, 1.875, 42.28125);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
//cairo_matrix_init(&matrix, 1,0,0,1,-728.0625,-186.71875);
//cairo_pattern_set_matrix(pattern, &matrix);
    cairo_stroke_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_rgba(0.501961,0,0,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 13.714844, 4.5625);
    cairo_line_to(cr, 16.5, 4.5625);
    cairo_curve_to(cr, 17.542969, 4.5625, 18.386719, 5.40625, 18.386719, 6.449219);
    cairo_line_to(cr, 18.386719, 7.875);
    cairo_curve_to(cr, 18.386719, 8.917969, 17.542969, 9.761719, 16.5, 9.761719);
    cairo_line_to(cr, 13.714844, 9.761719);
    cairo_curve_to(cr, 12.671875, 9.761719, 11.828125, 8.917969, 11.828125, 7.875);
    cairo_line_to(cr, 11.828125, 6.449219);
    cairo_curve_to(cr, 11.828125, 5.40625, 12.671875, 4.5625, 13.714844, 4.5625);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
    cairo_fill_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 0.481782);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0.101961,0.101961,0.101961,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 13.714844, 4.5625);
    cairo_line_to(cr, 16.5, 4.5625);
    cairo_curve_to(cr, 17.542969, 4.5625, 18.386719, 5.40625, 18.386719, 6.449219);
    cairo_line_to(cr, 18.386719, 7.875);
    cairo_curve_to(cr, 18.386719, 8.917969, 17.542969, 9.761719, 16.5, 9.761719);
    cairo_line_to(cr, 13.714844, 9.761719);
    cairo_curve_to(cr, 12.671875, 9.761719, 11.828125, 8.917969, 11.828125, 7.875);
    cairo_line_to(cr, 11.828125, 6.449219);
    cairo_curve_to(cr, 11.828125, 5.40625, 12.671875, 4.5625, 13.714844, 4.5625);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
//cairo_matrix_init(&matrix, 1,0,0,1,-728.0625,-186.71875);
//cairo_pattern_set_matrix(pattern, &matrix);
    cairo_stroke_preserve(cr);
    /********************/
    if(val)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_linear(128.75, 337.91769, 128.75, 355.34933);
        cairo_pattern_add_color_stop_rgba(pattern, 0,1,0,0,0);
        cairo_pattern_add_color_stop_rgba(pattern, 0.217951,1,0,0,1);
        cairo_pattern_add_color_stop_rgba(pattern, 0.77006,1,0,0,1);
        cairo_pattern_add_color_stop_rgba(pattern, 1,1,0,0,0);
        cairo_matrix_init(&matrix, 6.414841,0,0,1.859793,33.294438,333.317164);
        cairo_pattern_set_matrix(pattern, &matrix);
        cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
        cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 11.101562, 2.730469);
        cairo_line_to(cr, 19.113281, 2.730469);
        cairo_line_to(cr, 18.792969, 4.945312);
        cairo_curve_to(cr, 18.792969, 6.421875, 18.792969, 9.378906, 18.792969, 9.378906);
        cairo_line_to(cr, 19.113281, 11.59375);
        cairo_line_to(cr, 11.101562, 11.59375);
        cairo_line_to(cr, 11.421875, 9.378906);
        cairo_line_to(cr, 11.421875, 4.945312);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
}
#endif
