#ifndef DRAW_IVORYSLIDER_H
#define DRAW_IVORYSLIDER_H
inline int cairo_code_draw_ivorySlider_get_width()
{
    return 38;
}
inline int cairo_code_draw_ivorySlider_get_height()
{
    return 157;
}
inline void cairo_code_draw_ivorySlider_render(cairo_t *cr, float val)
{
    cairo_pattern_t *pattern;
    cairo_matrix_t matrix;

//slot
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 3.688728);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0.101961,0.101961,0.101961,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 14.625, 3.242188);
    cairo_line_to(cr, 14.625, 154.613281);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_stroke_preserve(cr);
    /********************/

    float os = -val*144;//y offset

    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_linear(33.59362, 795.22748, 22.300592, 772.03607);
    cairo_pattern_add_color_stop_rgba(pattern, 0,1,0.964706,0.682353,1);
    cairo_pattern_add_color_stop_rgba(pattern, 1,1,1,1,1);
    cairo_matrix_init(&matrix, 1.018716,-1.085302,4.234344,3.974557,-625.375116,199.462944);
    cairo_pattern_set_matrix(pattern, &matrix);
    cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
    cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 2.523438, 154.683594 + os);
    cairo_curve_to(cr, -0.25, 154.277344 + os, -0.324219, 144.851562 + os, 2.441406, 144.441406 + os);
    cairo_curve_to(cr, 5.207031, 144.03125 + os, 37.085938, 153.609375 + os, 37.09375, 154.425781 + os);
    cairo_curve_to(cr, 37.097656, 155.246094 + os, 5.292969, 155.09375 + os, 2.523438, 154.683594 + os);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
    cairo_fill_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 0.825892);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0.301961,0.301961,0.301961,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 2.523438, 154.683594 + os);
    cairo_curve_to(cr, -0.25, 154.277344 + os, -0.324219, 144.851562 + os, 2.441406, 144.441406 + os);
    cairo_curve_to(cr, 5.207031, 144.03125 + os, 37.085938, 153.609375 + os, 37.09375, 154.425781 + os);
    cairo_curve_to(cr, 37.097656, 155.246094 + os, 5.292969, 155.09375 + os, 2.523438, 154.683594 + os);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_stroke_preserve(cr);
    /********************/
}
#endif
