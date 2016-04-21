#ifndef DRAW_POWERBUTTON_H
#define DRAW_POWERBUTTON_H
inline int cairo_code_draw_powerButton_get_width()
{
    return 160;
}
inline int cairo_code_draw_powerButton_get_height()
{
    return 64;
}
inline void cairo_code_draw_powerButton_render(cairo_t *cr, int val)
{
    cairo_pattern_t *pattern;
    cairo_matrix_t matrix;

    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_linear(91.923882, 144.12209, 91.923882, 93.393311);
    cairo_pattern_add_color_stop_rgba(pattern, 0,0.509804,0.509804,0.509804,1);
    cairo_pattern_add_color_stop_rgba(pattern, 0.612644,0.658824,0.658824,0.658824,1);
    cairo_pattern_add_color_stop_rgba(pattern, 1,0.517647,0.517647,0.517647,1);
    cairo_matrix_init(&matrix, 1.142857,0,0,1.142857,29.814725,91.98792);
    cairo_pattern_set_matrix(pattern, &matrix);
    cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
    cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 15.011719, 1.3125);
    cairo_line_to(cr, 144.921875, 1.3125);
    cairo_curve_to(cr, 152.488281, 1.3125, 158.621094, 7.445312, 158.621094, 15.011719);
    cairo_line_to(cr, 158.621094, 48.761719);
    cairo_curve_to(cr, 158.621094, 56.328125, 152.488281, 62.460938, 144.921875, 62.460938);
    cairo_line_to(cr, 15.011719, 62.460938);
    cairo_curve_to(cr, 7.445312, 62.460938, 1.3125, 56.328125, 1.3125, 48.761719);
    cairo_line_to(cr, 1.3125, 15.011719);
    cairo_curve_to(cr, 1.3125, 7.445312, 7.445312, 1.3125, 15.011719, 1.3125);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
    cairo_fill_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 2.625);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0.2,0.2,0.2,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 15.011719, 1.3125);
    cairo_line_to(cr, 144.921875, 1.3125);
    cairo_curve_to(cr, 152.488281, 1.3125, 158.621094, 7.445312, 158.621094, 15.011719);
    cairo_line_to(cr, 158.621094, 48.761719);
    cairo_curve_to(cr, 158.621094, 56.328125, 152.488281, 62.460938, 144.921875, 62.460938);
    cairo_line_to(cr, 15.011719, 62.460938);
    cairo_curve_to(cr, 7.445312, 62.460938, 1.3125, 56.328125, 1.3125, 48.761719);
    cairo_line_to(cr, 1.3125, 15.011719);
    cairo_curve_to(cr, 1.3125, 7.445312, 7.445312, 1.3125, 15.011719, 1.3125);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_stroke_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_rgba(0.501961,0,0,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 19.410156, 25.628906);
    cairo_line_to(cr, 46.25, 25.628906);
    cairo_curve_to(cr, 48.757812, 25.628906, 50.789062, 27.660156, 50.789062, 30.167969);
    cairo_line_to(cr, 50.789062, 33.605469);
    cairo_curve_to(cr, 50.789062, 36.113281, 48.757812, 38.144531, 46.25, 38.144531);
    cairo_line_to(cr, 19.410156, 38.144531);
    cairo_curve_to(cr, 16.90625, 38.144531, 14.871094, 36.113281, 14.871094, 33.605469);
    cairo_line_to(cr, 14.871094, 30.167969);
    cairo_curve_to(cr, 14.871094, 27.660156, 16.90625, 25.628906, 19.410156, 25.628906);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
    cairo_fill_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 1.75);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0.101961,0.101961,0.101961,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 19.410156, 25.628906);
    cairo_line_to(cr, 46.25, 25.628906);
    cairo_curve_to(cr, 48.757812, 25.628906, 50.789062, 27.660156, 50.789062, 30.167969);
    cairo_line_to(cr, 50.789062, 33.605469);
    cairo_curve_to(cr, 50.789062, 36.113281, 48.757812, 38.144531, 46.25, 38.144531);
    cairo_line_to(cr, 19.410156, 38.144531);
    cairo_curve_to(cr, 16.90625, 38.144531, 14.871094, 36.113281, 14.871094, 33.605469);
    cairo_line_to(cr, 14.871094, 30.167969);
    cairo_curve_to(cr, 14.871094, 27.660156, 16.90625, 25.628906, 19.410156, 25.628906);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
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
        cairo_matrix_init(&matrix, 1.170992,0,0,0.772184,91.524863,322.013961);
        cairo_pattern_set_matrix(pattern, &matrix);
        cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
        cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 11.089844, 21.214844);
        cairo_line_to(cr, 54.984375, 21.214844);
        cairo_line_to(cr, 53.234375, 26.550781);
        cairo_curve_to(cr, 53.234375, 30.109375, 53.234375, 37.222656, 53.234375, 37.222656);
        cairo_line_to(cr, 54.984375, 42.5625);
        cairo_line_to(cr, 11.089844, 42.5625);
        cairo_line_to(cr, 12.839844, 37.222656);
        cairo_line_to(cr, 12.839844, 26.550781);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }

    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 3);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0.8,0.8,0.8,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 68.914062, 13.386719);
    cairo_line_to(cr, 68.914062, 50.386719);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_stroke_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 2);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0.8,0.8,0.8,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 74.914062, 53.386719);
    cairo_line_to(cr, 100.914062, 10.386719);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_stroke_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 3.600395);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0.8,0.8,0.8,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 118.035156, 13.136719);
    cairo_line_to(cr, 118.035156, 33.96875);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
//cairo_matrix_init(&matrix, 0.833242,0,0,0.833242,-106.58387,-421.87839);
//cairo_pattern_set_matrix(pattern, &matrix);
    cairo_stroke_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 3.600395);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0.8,0.8,0.8,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 123.148438, 18.960938);
    cairo_curve_to(cr, 130.691406, 21.464844, 135.320312, 29.058594, 134.082031, 36.914062);
    cairo_curve_to(cr, 132.84375, 44.765625, 126.105469, 50.570312, 118.15625, 50.632812);
    cairo_curve_to(cr, 110.207031, 50.695312, 103.378906, 44.992188, 102.023438, 37.160156);
    cairo_curve_to(cr, 100.664062, 29.324219, 105.175781, 21.660156, 112.683594, 19.042969);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
//cairo_matrix_init(&matrix, 0.262256,-0.790894,0.790894,0.262256,-78.825199,690.267755);
//cairo_pattern_set_matrix(pattern, &matrix);
    cairo_stroke_preserve(cr);
    /********************/
}
inline void cairo_code_draw_powerButton_render_reverse(cairo_t *cr, int val)
{
    cairo_code_draw_powerButton_render(cr,1-val);
}
#endif
