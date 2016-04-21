#ifndef DRAW_WHITETINYBUTTON_H
#define DRAW_WHITETINYBUTTON_H
inline int cairo_code_draw_whiteTinyButton_get_width() { return 22; }
inline int cairo_code_draw_whiteTinyButton_get_height() { return 22; }
inline void cairo_code_draw_whiteTinyButton_render(cairo_t *cr, int val) {
cairo_pattern_t *pattern;
cairo_matrix_t matrix;

    if(!val)
    {
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(0.164706,0.164706,0.164706,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 3.527344, 0.75);
cairo_line_to(cr, 17.972656, 0.75);
cairo_curve_to(cr, 19.507812, 0.75, 20.75, 1.992188, 20.75, 3.527344);
cairo_line_to(cr, 20.75, 17.972656);
cairo_curve_to(cr, 20.75, 19.507812, 19.507812, 20.75, 17.972656, 20.75);
cairo_line_to(cr, 3.527344, 20.75);
cairo_curve_to(cr, 1.992188, 20.75, 0.75, 19.507812, 0.75, 17.972656);
cairo_line_to(cr, 0.75, 3.527344);
cairo_curve_to(cr, 0.75, 1.992188, 1.992188, 0.75, 3.527344, 0.75);
cairo_close_path(cr);
cairo_move_to(cr, 3.527344, 0.75);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 1.5);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_linear(943.0932, 475.09332, 922.98602, 448.48618);
cairo_pattern_add_color_stop_rgba(pattern, 0,0,0,0,1);
cairo_pattern_add_color_stop_rgba(pattern, 1,0.592157,0.592157,0.592157,1);
cairo_matrix_init(&matrix, 1,0,0,1,924.16466,451.30761);
cairo_pattern_set_matrix(pattern, &matrix);
cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 3.527344, 0.75);
cairo_line_to(cr, 17.972656, 0.75);
cairo_curve_to(cr, 19.507812, 0.75, 20.75, 1.992188, 20.75, 3.527344);
cairo_line_to(cr, 20.75, 17.972656);
cairo_curve_to(cr, 20.75, 19.507812, 19.507812, 20.75, 17.972656, 20.75);
cairo_line_to(cr, 3.527344, 20.75);
cairo_curve_to(cr, 1.992188, 20.75, 0.75, 19.507812, 0.75, 17.972656);
cairo_line_to(cr, 0.75, 3.527344);
cairo_curve_to(cr, 0.75, 1.992188, 1.992188, 0.75, 3.527344, 0.75);
cairo_close_path(cr);
cairo_move_to(cr, 3.527344, 0.75);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_matrix_init(&matrix, 1,0,0,1,-281.81076,-163.33714);
cairo_pattern_set_matrix(pattern, &matrix);
cairo_stroke_preserve(cr);
/********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(0.572549,0.572549,0.572549,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 8.738281, 7);
cairo_line_to(cr, 12.761719, 7);
cairo_curve_to(cr, 14.261719, 7, 15.480469, 8.21875, 15.480469, 9.71875);
cairo_line_to(cr, 15.480469, 11.78125);
cairo_curve_to(cr, 15.480469, 13.28125, 14.261719, 14.5, 12.761719, 14.5);
cairo_line_to(cr, 8.738281, 14.5);
cairo_curve_to(cr, 7.238281, 14.5, 6.019531, 13.28125, 6.019531, 11.78125);
cairo_line_to(cr, 6.019531, 9.71875);
cairo_curve_to(cr, 6.019531, 8.21875, 7.238281, 7, 8.738281, 7);
cairo_close_path(cr);
cairo_move_to(cr, 8.738281, 7);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 0.694952);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(0.101961,0.101961,0.101961,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 8.738281, 7);
cairo_line_to(cr, 12.761719, 7);
cairo_curve_to(cr, 14.261719, 7, 15.480469, 8.21875, 15.480469, 9.71875);
cairo_line_to(cr, 15.480469, 11.78125);
cairo_curve_to(cr, 15.480469, 13.28125, 14.261719, 14.5, 12.761719, 14.5);
cairo_line_to(cr, 8.738281, 14.5);
cairo_curve_to(cr, 7.238281, 14.5, 6.019531, 13.28125, 6.019531, 11.78125);
cairo_line_to(cr, 6.019531, 9.71875);
cairo_curve_to(cr, 6.019531, 8.21875, 7.238281, 7, 8.738281, 7);
cairo_close_path(cr);
cairo_move_to(cr, 8.738281, 7);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_matrix_init(&matrix, 1,0,0,1,-281.81076,-163.33714);
cairo_pattern_set_matrix(pattern, &matrix);
cairo_stroke_preserve(cr);
    }
    else
    {
/********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(0.164706,0.164706,0.164706,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 17.972656, 20.75);
cairo_line_to(cr, 3.527344, 20.75);
cairo_curve_to(cr, 1.992188, 20.75, 0.75, 19.507812, 0.75, 17.972656);
cairo_line_to(cr, 0.75, 3.527344);
cairo_curve_to(cr, 0.75, 1.992188, 1.992188, 0.75, 3.527344, 0.75);
cairo_line_to(cr, 17.972656, 0.75);
cairo_curve_to(cr, 19.507812, 0.75, 20.75, 1.992188, 20.75, 3.527344);
cairo_line_to(cr, 20.75, 17.972656);
cairo_curve_to(cr, 20.75, 19.507812, 19.507812, 20.75, 17.972656, 20.75);
cairo_close_path(cr);
cairo_move_to(cr, 17.972656, 20.75);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 1.5);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_linear(943.0932, 475.09332, 922.98602, 448.48618);
cairo_pattern_add_color_stop_rgba(pattern, 0,0,0,0,1);
cairo_pattern_add_color_stop_rgba(pattern, 1,0.592157,0.592157,0.592157,1);
cairo_matrix_init(&matrix, -1,0,0,-1,945.66454,472.80764);
cairo_pattern_set_matrix(pattern, &matrix);
cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 17.972656, 20.75);
cairo_line_to(cr, 3.527344, 20.75);
cairo_curve_to(cr, 1.992188, 20.75, 0.75, 19.507812, 0.75, 17.972656);
cairo_line_to(cr, 0.75, 3.527344);
cairo_curve_to(cr, 0.75, 1.992188, 1.992188, 0.75, 3.527344, 0.75);
cairo_line_to(cr, 17.972656, 0.75);
cairo_curve_to(cr, 19.507812, 0.75, 20.75, 1.992188, 20.75, 3.527344);
cairo_line_to(cr, 20.75, 17.972656);
cairo_curve_to(cr, 20.75, 19.507812, 19.507812, 20.75, 17.972656, 20.75);
cairo_close_path(cr);
cairo_move_to(cr, 17.972656, 20.75);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_matrix_init(&matrix, -1,0,0,-1,-281.81076,-163.33714);
cairo_pattern_set_matrix(pattern, &matrix);
cairo_stroke_preserve(cr);
/********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_linear(128.75, 337.91769, 128.75, 355.34933);
cairo_pattern_add_color_stop_rgba(pattern, 0,1,1,1,0);
cairo_pattern_add_color_stop_rgba(pattern, 0.283991,1,1,1,1);
cairo_pattern_add_color_stop_rgba(pattern, 0.723832,1,1,1,1);
cairo_pattern_add_color_stop_rgba(pattern, 1,1,1,1,0);
cairo_matrix_init(&matrix, 4.447149,0,0,1.289319,82.404294,332.776981);
cairo_pattern_set_matrix(pattern, &matrix);
cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 4.972656, 4.359375);
cairo_line_to(cr, 16.527344, 4.359375);
cairo_line_to(cr, 16.066406, 7.554688);
cairo_curve_to(cr, 16.066406, 9.683594, 16.066406, 13.945312, 16.066406, 13.945312);
cairo_line_to(cr, 16.527344, 17.140625);
cairo_line_to(cr, 4.972656, 17.140625);
cairo_line_to(cr, 5.433594, 13.945312);
cairo_line_to(cr, 5.433594, 7.554688);
cairo_close_path(cr);
cairo_move_to(cr, 4.972656, 4.359375);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
}
 /********************/
}
#endif
