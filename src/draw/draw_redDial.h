#ifndef DRAW_REDDIAL_H
#define DRAW_REDDIAL_H
#define PI 3.1415926535897932384626433832795
inline int cairo_code_draw_redDial_get_width() { return 50; }
inline int cairo_code_draw_redDial_get_height() { return 50; }
inline void cairo_code_draw_redDial_render(cairo_t *cr, float val) {
cairo_pattern_t *pattern;
cairo_matrix_t matrix;

cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_radial(78.743378, 172.53114, 0, 78.743378, 172.53114, 20.063856);
cairo_pattern_add_color_stop_rgba(pattern, 0,0.407843,0,0,1);
cairo_pattern_add_color_stop_rgba(pattern, 1,0.984314,0,0,1);
cairo_matrix_init(&matrix, 0.702016,0.656977,-0.649072,0.710566,77.456404,132.417971);
cairo_pattern_set_matrix(pattern, &matrix);
cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 37.734375, 25);
cairo_curve_to(cr, 37.734375, 32.035156, 32.035156, 37.734375, 25, 37.734375);
cairo_curve_to(cr, 17.964844, 37.734375, 12.265625, 32.035156, 12.265625, 25);
cairo_curve_to(cr, 12.265625, 17.964844, 17.964844, 12.265625, 25, 12.265625);
cairo_curve_to(cr, 32.035156, 12.265625, 37.734375, 17.964844, 37.734375, 25);
cairo_close_path(cr);
cairo_move_to(cr, 37.734375, 25);
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
pattern = cairo_pattern_create_rgba(0.603922,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 37.734375, 25);
cairo_curve_to(cr, 37.734375, 32.035156, 32.035156, 37.734375, 25, 37.734375);
cairo_curve_to(cr, 17.964844, 37.734375, 12.265625, 32.035156, 12.265625, 25);
cairo_curve_to(cr, 12.265625, 17.964844, 17.964844, 12.265625, 25, 12.265625);
cairo_curve_to(cr, 32.035156, 12.265625, 37.734375, 17.964844, 37.734375, 25);
cairo_close_path(cr);
cairo_move_to(cr, 37.734375, 25);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_matrix_init(&matrix, 0.648375,0,0,0.648375,-26.638418,-85.597409);
cairo_pattern_set_matrix(pattern, &matrix);
cairo_stroke_preserve(cr);
/********************/

    cairo_translate(cr,25,25);
    cairo_rotate(cr,3*PI/2*val - 3*PI/4);
    cairo_translate(cr,-25,-25);

cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_linear(52.458691, 825.30457, 40.941853, 782.5293);
cairo_pattern_add_color_stop_rgba(pattern, 0,0.407843,0,0,1);
cairo_pattern_add_color_stop_rgba(pattern, 1,0.984314,0,0,1);
cairo_matrix_init(&matrix, 3.176871,2.981963,-0.764305,0.814261,-12.61461,698.060098);
cairo_pattern_set_matrix(pattern, &matrix);
cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);

//    cairo_translate(cr,25,25);
//    cairo_rotate(cr,3*PI/2*val - 3*PI/4);
//    cairo_translate(cr,-25,-25);

cairo_new_path(cr);
cairo_move_to(cr, 31.828125, 46.628906);
cairo_curve_to(cr, 31.28125, 50.324219, 18.722656, 50.421875, 18.175781, 46.734375);
cairo_curve_to(cr, 17.625, 43.046875, 23.882812, 0.558594, 24.976562, 0.550781);
cairo_curve_to(cr, 26.070312, 0.542969, 32.371094, 42.933594, 31.828125, 46.628906);
cairo_close_path(cr);
cairo_move_to(cr, 31.828125, 46.628906);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 2.428246);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(0.603922,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 31.828125, 46.628906);
cairo_curve_to(cr, 31.28125, 50.324219, 18.722656, 50.421875, 18.175781, 46.734375);
cairo_curve_to(cr, 17.625, 43.046875, 23.882812, 0.558594, 24.976562, 0.550781);
cairo_curve_to(cr, 26.070312, 0.542969, 32.371094, 42.933594, 31.828125, 46.628906);
cairo_close_path(cr);
cairo_move_to(cr, 31.828125, 46.628906);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_matrix_init(&matrix, 0.167339,-0.612825,0.157073,0.65288,-107.535205,-463.480282);
cairo_pattern_set_matrix(pattern, &matrix);
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
cairo_move_to(cr, 25, 1.542969);
cairo_line_to(cr, 25, 12.464844);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_matrix_init(&matrix, 0.550402,0,0,0.550402,-236.833886,127.48988);
cairo_pattern_set_matrix(pattern, &matrix);
cairo_stroke_preserve(cr);
/********************/
}
#endif
