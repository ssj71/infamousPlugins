#ifndef DRAW_VINTAGEKNOB_H
#define DRAW_VINTAGEKNOB_H
#define PI 3.1415926535897932384626433832795
inline int cairo_code_draw_ivoryDial_get_width()
{
    return 91;
}
inline int cairo_code_draw_ivoryDial_get_height()
{
    return 91;
}
inline void cairo_code_draw_ivoryDial_render(cairo_t *cr, float val)
{
    cairo_surface_t *temp_surface;
    cairo_t *old_cr;
    cairo_pattern_t *pattern;
    cairo_matrix_t matrix;

    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_radial(78.743378, 172.53114, 0, 78.743378, 172.53114, 20.063856);
    cairo_pattern_add_color_stop_rgba(pattern, 0,1,0.964706,0.682353,1);
    cairo_pattern_add_color_stop_rgba(pattern, 1,1,1,1,1);
    cairo_matrix_init(&matrix, 0.386391,0.361601,-0.35725,0.391097,77.459081,132.424916);
    cairo_pattern_set_matrix(pattern, &matrix);
    cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
    cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 68.546875, 45.414062);
    cairo_curve_to(cr, 68.546875, 58.195312, 58.1875, 68.554688, 45.410156, 68.554688);
    cairo_curve_to(cr, 32.628906, 68.554688, 22.269531, 58.195312, 22.269531, 45.414062);
    cairo_curve_to(cr, 22.269531, 32.636719, 32.628906, 22.277344, 45.410156, 22.277344);
    cairo_curve_to(cr, 58.1875, 22.277344, 68.546875, 32.636719, 68.546875, 45.414062);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
    cairo_fill_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 0.842103);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0,0,0,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 68.546875, 45.414062);
    cairo_curve_to(cr, 68.546875, 58.195312, 58.1875, 68.554688, 45.410156, 68.554688);
    cairo_curve_to(cr, 32.628906, 68.554688, 22.269531, 58.195312, 22.269531, 45.414062);
    cairo_curve_to(cr, 22.269531, 32.636719, 32.628906, 22.277344, 45.410156, 22.277344);
    cairo_curve_to(cr, 58.1875, 22.277344, 68.546875, 32.636719, 68.546875, 45.414062);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
//cairo_matrix_init(&matrix, 1.178003,0,0,1.178003,-48.41074,-155.52423);
//cairo_pattern_set_matrix(pattern, &matrix);
    cairo_stroke_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_linear(52.458691, 825.30457, 40.941853, 782.5293);
    cairo_pattern_add_color_stop_rgba(pattern, 0,1,0.964706,0.682353,1);
    cairo_pattern_add_color_stop_rgba(pattern, 1,1,1,1,1);
    cairo_matrix_init(&matrix, 1.748555,1.641277,-0.420674,0.448171,-12.595116,698.083472);
    cairo_pattern_set_matrix(pattern, &matrix);
    cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
    cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);

    cairo_translate(cr,45.5,45.5);
    cairo_rotate(cr,3*PI/2*val - 3*PI/4);
    cairo_translate(cr,-45.5,-45.5);

    cairo_new_path(cr);
    cairo_move_to(cr, 57.8125, 84.710938);
    cairo_curve_to(cr, 56.824219, 91.421875, 34.003906, 91.601562, 33.007812, 84.902344);
    cairo_curve_to(cr, 32.011719, 78.207031, 43.382812, 1.007812, 45.367188, 0.992188);
    cairo_curve_to(cr, 47.351562, 0.976562, 58.800781, 77.996094, 57.8125, 84.710938);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
    cairo_fill_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 1.214123);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0.301961,0.301961,0.301961,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 57.8125, 84.710938);
    cairo_curve_to(cr, 56.824219, 91.421875, 34.003906, 91.601562, 33.007812, 84.902344);
    cairo_curve_to(cr, 32.011719, 78.207031, 43.382812, 1.007812, 45.367188, 0.992188);
    cairo_curve_to(cr, 47.351562, 0.976562, 58.800781, 77.996094, 57.8125, 84.710938);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
//cairo_matrix_init(&matrix, 0.304031,-1.113414,0.285378,1.186189,-195.38851,-842.08265);
//cairo_pattern_set_matrix(pattern, &matrix);
    cairo_stroke_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 1.543);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0,0,0,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 45.410156, 2.796875);
    cairo_line_to(cr, 45.410156, 22.640625);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
//cairo_matrix_init(&matrix, 1,0,0,1,-331.73407,-481.23254);
//cairo_pattern_set_matrix(pattern, &matrix);
    cairo_stroke_preserve(cr);
    /********************/
}
#endif
