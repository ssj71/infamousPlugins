#ifndef DRAW_TABDIAL_H
#define DRAW_TABDIAL_H
#define PI 3.1415926535897932384626433832795
inline int cairo_code_draw_tabDial_get_width()
{
    return 60;
}
inline int cairo_code_draw_tabDial_get_height()
{
    return 60;
}
inline void cairo_code_draw_tabDial_render(cairo_t *cr,float val)
{
    cairo_pattern_t *pattern;
    cairo_matrix_t matrix;

    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_radial(78.072823, 172.32506, 0, 78.072823, 172.32506, 20.063856);
    cairo_pattern_add_color_stop_rgba(pattern, 0,0,0,0,1);
    cairo_pattern_add_color_stop_rgba(pattern, 0.892578,1,1,1,1);
    cairo_pattern_add_color_stop_rgba(pattern, 1,0,0,0,0);
    cairo_matrix_init(&matrix, -0.024135,0.178731,-0.202277,-0.0213257,86.768353,166.742483);
    cairo_pattern_set_matrix(pattern, &matrix);
    cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
    cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 52.921875, 29.78125);
    cairo_curve_to(cr, 52.921875, 42.5625, 42.5625, 52.921875, 29.78125, 52.921875);
    cairo_curve_to(cr, 17.003906, 52.921875, 6.640625, 42.5625, 6.640625, 29.78125);
    cairo_curve_to(cr, 6.640625, 17.003906, 17.003906, 6.640625, 29.78125, 6.640625);
    cairo_curve_to(cr, 42.5625, 6.640625, 52.921875, 17.003906, 52.921875, 29.78125);
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
    cairo_new_path(cr);
    cairo_move_to(cr, 52.921875, 29.78125);
    cairo_curve_to(cr, 52.921875, 42.5625, 42.5625, 52.921875, 29.78125, 52.921875);
    cairo_curve_to(cr, 17.003906, 52.921875, 6.640625, 42.5625, 6.640625, 29.78125);
    cairo_curve_to(cr, 6.640625, 17.003906, 17.003906, 6.640625, 29.78125, 6.640625);
    cairo_curve_to(cr, 42.5625, 6.640625, 52.921875, 17.003906, 52.921875, 29.78125);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
//cairo_matrix_init(&matrix, 1.178003,0,0,1.178003,-64.03769,-171.15775);
//cairo_pattern_set_matrix(pattern, &matrix);
    cairo_stroke_preserve(cr);
    /********************/

    cairo_translate(cr,30,30);
    cairo_rotate(cr,3*PI/2*val - 3*PI/4);
    cairo_translate(cr,-30,-30);

    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_radial(244.40021, 708.68555, 0, 244.40021, 708.68555, 11.214286);
    cairo_pattern_add_color_stop_rgba(pattern, 0,0,0,0,1);
    cairo_pattern_add_color_stop_rgba(pattern, 1,1,1,1,1);
    cairo_matrix_init(&matrix, -0.0027055,0.250406,-0.0735616,-0.00920957,246.673504,701.323353);
    cairo_pattern_set_matrix(pattern, &matrix);
    cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
    cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 24.78125, 0.496094);
    cairo_line_to(cr, 34.78125, 0.496094);
    cairo_curve_to(cr, 37.9375, 0.496094, 40.496094, 3.054688, 40.496094, 6.210938);
    cairo_line_to(cr, 40.496094, 53.351562);
    cairo_curve_to(cr, 40.496094, 56.507812, 37.9375, 59.066406, 34.78125, 59.066406);
    cairo_line_to(cr, 24.78125, 59.066406);
    cairo_curve_to(cr, 21.625, 59.066406, 19.066406, 56.507812, 19.066406, 53.351562);
    cairo_line_to(cr, 19.066406, 6.210938);
    cairo_curve_to(cr, 19.066406, 3.054688, 21.625, 0.496094, 24.78125, 0.496094);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
    cairo_fill_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 1);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0,0,0,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 24.78125, 0.496094);
    cairo_line_to(cr, 34.78125, 0.496094);
    cairo_curve_to(cr, 37.9375, 0.496094, 40.496094, 3.054688, 40.496094, 6.210938);
    cairo_line_to(cr, 40.496094, 53.351562);
    cairo_curve_to(cr, 40.496094, 56.507812, 37.9375, 59.066406, 34.78125, 59.066406);
    cairo_line_to(cr, 24.78125, 59.066406);
    cairo_curve_to(cr, 21.625, 59.066406, 19.066406, 56.507812, 19.066406, 53.351562);
    cairo_line_to(cr, 19.066406, 6.210938);
    cairo_curve_to(cr, 19.066406, 3.054688, 21.625, 0.496094, 24.78125, 0.496094);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
//cairo_matrix_init(&matrix, 1,0,0,1,-293.0753,-365.4375);
//cairo_pattern_set_matrix(pattern, &matrix);
    cairo_stroke_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_rgba(1,1,1,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 27.640625, 1.425781);
    cairo_line_to(cr, 31.925781, 1.425781);
    cairo_line_to(cr, 31.925781, 10.710938);
    cairo_line_to(cr, 27.640625, 10.710938);
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
    cairo_new_path(cr);
    cairo_move_to(cr, 27.640625, 1.425781);
    cairo_line_to(cr, 31.925781, 1.425781);
    cairo_line_to(cr, 31.925781, 10.710938);
    cairo_line_to(cr, 27.640625, 10.710938);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
//cairo_matrix_init(&matrix, 1,0,0,1,-293.0753,-365.4375);
//cairo_pattern_set_matrix(pattern, &matrix);
    cairo_stroke_preserve(cr);
    /********************/
}
#endif
