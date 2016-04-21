#ifndef DRAW_FLATDIAL_H
#define DRAW_FLATDIAL_H
inline int cairo_code_draw_flatDial_get_width()
{
    return 30;
}
inline int cairo_code_draw_flatDial_get_height()
{
    return 30;
}
inline void cairo_code_draw_flatDial_render(cairo_t *cr, float val)
{
    cairo_pattern_t *pattern;
    cairo_matrix_t matrix;

    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_rgba(0,0,0,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 29.269531, 14.945312);
    cairo_curve_to(cr, 29.269531, 22.855469, 22.855469, 29.269531, 14.945312, 29.269531);
    cairo_curve_to(cr, 7.03125, 29.269531, 0.617188, 22.855469, 0.617188, 14.945312);
    cairo_curve_to(cr, 0.617188, 7.03125, 7.03125, 0.617188, 14.945312, 0.617188);
    cairo_curve_to(cr, 22.855469, 0.617188, 29.269531, 7.03125, 29.269531, 14.945312);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
    cairo_fill_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 1.697789);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_radial(109.38804, 152.98503, 0, 109.38804, 152.98503, 19.642857);
    cairo_pattern_add_color_stop_rgba(pattern, 0,1,1,1,1);
    cairo_pattern_add_color_stop_rgba(pattern, 1,0,0,0,1);
    cairo_matrix_init(&matrix, -0.034243,1.289785,-2.358123,-0.0187294,114.606378,147.333024);
    cairo_pattern_set_matrix(pattern, &matrix);
    cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
    cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 29.269531, 14.945312);
    cairo_curve_to(cr, 29.269531, 22.855469, 22.855469, 29.269531, 14.945312, 29.269531);
    cairo_curve_to(cr, 7.03125, 29.269531, 0.617188, 22.855469, 0.617188, 14.945312);
    cairo_curve_to(cr, 0.617188, 7.03125, 7.03125, 0.617188, 14.945312, 0.617188);
    cairo_curve_to(cr, 22.855469, 0.617188, 29.269531, 7.03125, 29.269531, 14.945312);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_stroke_preserve(cr);
    /********************/

    cairo_translate(cr,15,15);
    cairo_rotate(cr,3*PI/2*val - 3*PI/4);
    cairo_translate(cr,-15, -15);

    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_rgba(1,1,1,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 14.320312, 1.976562);
    cairo_line_to(cr, 15.566406, 1.976562);
    cairo_line_to(cr, 15.566406, 14.449219);
    cairo_line_to(cr, 14.320312, 14.449219);
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
    pattern = cairo_pattern_create_rgba(0.501961,0.501961,0.501961,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 14.320312, 1.976562);
    cairo_line_to(cr, 15.566406, 1.976562);
    cairo_line_to(cr, 15.566406, 14.449219);
    cairo_line_to(cr, 14.320312, 14.449219);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_stroke_preserve(cr);
    /********************/
}
#endif
