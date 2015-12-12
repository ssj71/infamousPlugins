#ifndef DRAW_TINYBUTTON_H
#define DRAW_TINYBUTTON_H
inline int cairo_code_draw_tinyButton_get_width()
{
    return 22;
}
inline int cairo_code_draw_tinyButton_get_height()
{
    return 22;
}
inline void draw_nothing_render(cairo_t *cr, int val) { };
inline void cairo_code_draw_tinyButton_render(cairo_t *cr, int val)
{
    cairo_pattern_t *pattern;
    cairo_matrix_t matrix;

    if(!val)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(0.501961,0.501961,0.501961,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 3.527344, 0.753906);
        cairo_line_to(cr, 17.972656, 0.753906);
        cairo_curve_to(cr, 19.507812, 0.753906, 20.75, 2, 20.75, 3.535156);
        cairo_line_to(cr, 20.75, 17.976562);
        cairo_curve_to(cr, 20.75, 19.511719, 19.507812, 20.753906, 17.972656, 20.753906);
        cairo_line_to(cr, 3.527344, 20.753906);
        cairo_curve_to(cr, 1.992188, 20.753906, 0.75, 19.511719, 0.75, 17.976562);
        cairo_line_to(cr, 0.75, 3.535156);
        cairo_curve_to(cr, 0.75, 2, 1.992188, 0.753906, 3.527344, 0.753906);
        cairo_close_path(cr);
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
        cairo_pattern_add_color_stop_rgba(pattern, 1,1,1,1,1);
        cairo_matrix_init(&matrix, 1,0,0,1,924.164629,451.302032);
        cairo_pattern_set_matrix(pattern, &matrix);
        cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
        cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 3.527344, 0.753906);
        cairo_line_to(cr, 17.972656, 0.753906);
        cairo_curve_to(cr, 19.507812, 0.753906, 20.75, 2, 20.75, 3.535156);
        cairo_line_to(cr, 20.75, 17.976562);
        cairo_curve_to(cr, 20.75, 19.511719, 19.507812, 20.753906, 17.972656, 20.753906);
        cairo_line_to(cr, 3.527344, 20.753906);
        cairo_curve_to(cr, 1.992188, 20.753906, 0.75, 19.511719, 0.75, 17.976562);
        cairo_line_to(cr, 0.75, 3.535156);
        cairo_curve_to(cr, 0.75, 2, 1.992188, 0.753906, 3.527344, 0.753906);
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
        cairo_move_to(cr, 8.738281, 7.007812);
        cairo_line_to(cr, 12.761719, 7.007812);
        cairo_curve_to(cr, 14.261719, 7.007812, 15.480469, 8.226562, 15.480469, 9.726562);
        cairo_line_to(cr, 15.480469, 11.785156);
        cairo_curve_to(cr, 15.480469, 13.285156, 14.261719, 14.503906, 12.761719, 14.503906);
        cairo_line_to(cr, 8.738281, 14.503906);
        cairo_curve_to(cr, 7.238281, 14.503906, 6.019531, 13.285156, 6.019531, 11.785156);
        cairo_line_to(cr, 6.019531, 9.726562);
        cairo_curve_to(cr, 6.019531, 8.226562, 7.238281, 7.007812, 8.738281, 7.007812);
        cairo_close_path(cr);
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
        cairo_move_to(cr, 8.738281, 7.007812);
        cairo_line_to(cr, 12.761719, 7.007812);
        cairo_curve_to(cr, 14.261719, 7.007812, 15.480469, 8.226562, 15.480469, 9.726562);
        cairo_line_to(cr, 15.480469, 11.785156);
        cairo_curve_to(cr, 15.480469, 13.285156, 14.261719, 14.503906, 12.761719, 14.503906);
        cairo_line_to(cr, 8.738281, 14.503906);
        cairo_curve_to(cr, 7.238281, 14.503906, 6.019531, 13.285156, 6.019531, 11.785156);
        cairo_line_to(cr, 6.019531, 9.726562);
        cairo_curve_to(cr, 6.019531, 8.226562, 7.238281, 7.007812, 8.738281, 7.007812);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_stroke_preserve(cr);
    }
    else
    {
        /********************/
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(0.501961,0.501961,0.501961,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 3.527344, 0.753906);
        cairo_line_to(cr, 17.972656, 0.753906);
        cairo_curve_to(cr, 19.507812, 0.753906, 20.75, 2, 20.75, 3.535156);
        cairo_line_to(cr, 20.75, 17.976562);
        cairo_curve_to(cr, 20.75, 19.511719, 19.507812, 20.753906, 17.972656, 20.753906);
        cairo_line_to(cr, 3.527344, 20.753906);
        cairo_curve_to(cr, 1.992188, 20.753906, 0.75, 19.511719, 0.75, 17.976562);
        cairo_line_to(cr, 0.75, 3.535156);
        cairo_curve_to(cr, 0.75, 2, 1.992188, 0.753906, 3.527344, 0.753906);
        cairo_close_path(cr);
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
        pattern = cairo_pattern_create_linear(948.91461, 450.74918, 976.48608, 479.32062);
        cairo_pattern_add_color_stop_rgba(pattern, 0,0,0,0,1);
        cairo_pattern_add_color_stop_rgba(pattern, 1,1,1,1,1);
        cairo_matrix_init(&matrix, 1,0,0,1,950.16463,452.315041);
        cairo_pattern_set_matrix(pattern, &matrix);
        cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
        cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 3.527344, 0.753906);
        cairo_line_to(cr, 17.972656, 0.753906);
        cairo_curve_to(cr, 19.507812, 0.753906, 20.75, 2, 20.75, 3.535156);
        cairo_line_to(cr, 20.75, 17.976562);
        cairo_curve_to(cr, 20.75, 19.511719, 19.507812, 20.753906, 17.972656, 20.753906);
        cairo_line_to(cr, 3.527344, 20.753906);
        cairo_curve_to(cr, 1.992188, 20.753906, 0.75, 19.511719, 0.75, 17.976562);
        cairo_line_to(cr, 0.75, 3.535156);
        cairo_curve_to(cr, 0.75, 2, 1.992188, 0.753906, 3.527344, 0.753906);
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
        cairo_move_to(cr, 8.738281, 7.007812);
        cairo_line_to(cr, 12.761719, 7.007812);
        cairo_curve_to(cr, 14.261719, 7.007812, 15.480469, 8.226562, 15.480469, 9.726562);
        cairo_line_to(cr, 15.480469, 11.785156);
        cairo_curve_to(cr, 15.480469, 13.285156, 14.261719, 14.503906, 12.761719, 14.503906);
        cairo_line_to(cr, 8.738281, 14.503906);
        cairo_curve_to(cr, 7.238281, 14.503906, 6.019531, 13.285156, 6.019531, 11.785156);
        cairo_line_to(cr, 6.019531, 9.726562);
        cairo_curve_to(cr, 6.019531, 8.226562, 7.238281, 7.007812, 8.738281, 7.007812);
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
        cairo_move_to(cr, 8.738281, 7.007812);
        cairo_line_to(cr, 12.761719, 7.007812);
        cairo_curve_to(cr, 14.261719, 7.007812, 15.480469, 8.226562, 15.480469, 9.726562);
        cairo_line_to(cr, 15.480469, 11.785156);
        cairo_curve_to(cr, 15.480469, 13.285156, 14.261719, 14.503906, 12.761719, 14.503906);
        cairo_line_to(cr, 8.738281, 14.503906);
        cairo_curve_to(cr, 7.238281, 14.503906, 6.019531, 13.285156, 6.019531, 11.785156);
        cairo_line_to(cr, 6.019531, 9.726562);
        cairo_curve_to(cr, 6.019531, 8.226562, 7.238281, 7.007812, 8.738281, 7.007812);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_stroke_preserve(cr);
        /********************/
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_linear(128.75, 337.91769, 128.75, 355.34933);
        cairo_pattern_add_color_stop_rgba(pattern, 0,1,0,0,0);
        cairo_pattern_add_color_stop_rgba(pattern, 0.217951,1,0,0,1);
        cairo_pattern_add_color_stop_rgba(pattern, 0.77006,1,0,0,1);
        cairo_pattern_add_color_stop_rgba(pattern, 1,1,0,0,0);
        cairo_matrix_init(&matrix, 4.447149,0,0,1.289319,82.404232,332.769785);
        cairo_pattern_set_matrix(pattern, &matrix);
        cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
        cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 4.972656, 4.363281);
        cairo_line_to(cr, 16.527344, 4.363281);
        cairo_line_to(cr, 16.066406, 7.558594);
        cairo_curve_to(cr, 16.066406, 9.691406, 16.066406, 13.953125, 16.066406, 13.953125);
        cairo_line_to(cr, 16.527344, 17.148438);
        cairo_line_to(cr, 4.972656, 17.148438);
        cairo_line_to(cr, 5.433594, 13.953125);
        cairo_line_to(cr, 5.433594, 7.558594);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
}
#endif
