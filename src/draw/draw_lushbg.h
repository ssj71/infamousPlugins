#ifndef DRAW_LUSHBG_H
#define DRAW_LUSHBG_H
inline int cairo_code_draw_lushbg_get_width() { return 630; }
inline int cairo_code_draw_lushbg_get_height() { return 400; }
inline void cairo_code_draw_lushbg_render(cairo_t *cr) {
cairo_pattern_t *pattern;
cairo_matrix_t matrix;

cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_linear(229.25, 318.07648, 245.03569, 213.79076);
cairo_pattern_add_color_stop_rgba(pattern, 0,0.0235294,0.0235294,0.0235294,1);
cairo_pattern_add_color_stop_rgba(pattern, 0.268445,0.168627,0.168627,0.168627,1);
cairo_pattern_add_color_stop_rgba(pattern, 1,0.054902,0.054902,0.054902,1);
cairo_matrix_init(&matrix, 0.657829,0,0,0.596428,30.632166,91.644363);
cairo_pattern_set_matrix(pattern, &matrix);
cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 32.097656, 1.203125);
cairo_line_to(cr, 597.929688, 1.203125);
cairo_curve_to(cr, 614.988281, 1.203125, 628.816406, 15.03125, 628.816406, 32.089844);
cairo_line_to(cr, 628.816406, 367.921875);
cairo_curve_to(cr, 628.816406, 384.980469, 614.988281, 398.808594, 597.929688, 398.808594);
cairo_line_to(cr, 32.097656, 398.808594);
cairo_curve_to(cr, 15.039062, 398.808594, 1.210938, 384.980469, 1.210938, 367.921875);
cairo_line_to(cr, 1.210938, 32.089844);
cairo_curve_to(cr, 1.210938, 15.03125, 15.039062, 1.203125, 32.097656, 1.203125);
cairo_close_path(cr);
cairo_move_to(cr, 32.097656, 1.203125);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 2.394725);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(0.901961,0.901961,0.901961,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 32.097656, 1.203125);
cairo_line_to(cr, 597.929688, 1.203125);
cairo_curve_to(cr, 614.988281, 1.203125, 628.816406, 15.03125, 628.816406, 32.089844);
cairo_line_to(cr, 628.816406, 367.921875);
cairo_curve_to(cr, 628.816406, 384.980469, 614.988281, 398.808594, 597.929688, 398.808594);
cairo_line_to(cr, 32.097656, 398.808594);
cairo_curve_to(cr, 15.039062, 398.808594, 1.210938, 384.980469, 1.210938, 367.921875);
cairo_line_to(cr, 1.210938, 32.089844);
cairo_curve_to(cr, 1.210938, 15.03125, 15.039062, 1.203125, 32.097656, 1.203125);
cairo_close_path(cr);
cairo_move_to(cr, 32.097656, 1.203125);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_matrix_init(&matrix, 1,0,0,1,72.6875,24.71875);
cairo_pattern_set_matrix(pattern, &matrix);
cairo_stroke_preserve(cr);
/********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_radial(-156.68268, 256.25381, 0, -156.68268, 256.25381, 347.17856);
cairo_pattern_add_color_stop_rgba(pattern, 0,0.0980392,0.0980392,0.0980392,1);
cairo_pattern_add_color_stop_rgba(pattern, 1,0,0,0,1);
cairo_matrix_init(&matrix, 0.0875326,1.493564,-2.582628,0.0607843,217.080885,-159.641249);
cairo_pattern_set_matrix(pattern, &matrix);
cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 71.660156, 17.863281);
cairo_line_to(cr, 489.597656, 17.863281);
cairo_curve_to(cr, 499.515625, 17.863281, 507.554688, 25.90625, 507.554688, 35.824219);
cairo_line_to(cr, 507.554688, 277.207031);
cairo_curve_to(cr, 507.554688, 287.125, 499.515625, 295.164062, 489.597656, 295.164062);
cairo_line_to(cr, 71.660156, 295.164062);
cairo_curve_to(cr, 61.742188, 295.164062, 53.703125, 287.125, 53.703125, 277.207031);
cairo_line_to(cr, 53.703125, 35.824219);
cairo_curve_to(cr, 53.703125, 25.90625, 61.742188, 17.863281, 71.660156, 17.863281);
cairo_close_path(cr);
cairo_move_to(cr, 71.660156, 17.863281);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 1.700661);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(0.8,0.8,0.8,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 71.660156, 17.863281);
cairo_line_to(cr, 489.597656, 17.863281);
cairo_curve_to(cr, 499.515625, 17.863281, 507.554688, 25.90625, 507.554688, 35.824219);
cairo_line_to(cr, 507.554688, 277.207031);
cairo_curve_to(cr, 507.554688, 287.125, 499.515625, 295.164062, 489.597656, 295.164062);
cairo_line_to(cr, 71.660156, 295.164062);
cairo_curve_to(cr, 61.742188, 295.164062, 53.703125, 287.125, 53.703125, 277.207031);
cairo_line_to(cr, 53.703125, 35.824219);
cairo_curve_to(cr, 53.703125, 25.90625, 61.742188, 17.863281, 71.660156, 17.863281);
cairo_close_path(cr);
cairo_move_to(cr, 71.660156, 17.863281);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_matrix_init(&matrix, 1,0,0,1,72.6875,24.71875);
cairo_pattern_set_matrix(pattern, &matrix);
cairo_stroke_preserve(cr);
/********************/
}
#endif
