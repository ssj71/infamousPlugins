#ifndef DRAW_HAL_H
#define DRAW_HAL_H
inline int cairo_code_draw_hal_get_width()
{
    return 82;
}
inline int cairo_code_draw_hal_get_height()
{
    return 82;
}
inline void cairo_code_draw_hal_render(cairo_t *cr, int bogus)
{
    cairo_pattern_t *pattern;
    cairo_matrix_t matrix;

    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_radial(114.28571, 1230.9336, 0, 114.28571, 1230.9336, 109.32143);
    cairo_pattern_add_color_stop_rgba(pattern, 0,1,0.333333,0.137255,1);
    cairo_pattern_add_color_stop_rgba(pattern, 0.1,0.470588,0,0,1);
    cairo_pattern_add_color_stop_rgba(pattern, 0.294,0.952941,0,0,1);
    cairo_pattern_add_color_stop_rgba(pattern, 0.488,0.968627,0,0,1);
    cairo_pattern_add_color_stop_rgba(pattern, 0.744,0.286275,0,0,1);
    cairo_pattern_add_color_stop_rgba(pattern, 1,0.0313725,0,0,1);
    cairo_matrix_init(&matrix, 2.866843,0,0,2.866843,-2.821369,1113.82653);
    cairo_pattern_set_matrix(pattern, &matrix);
    cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
    cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 78.71875, 40.847656);
    cairo_curve_to(cr, 78.71875, 61.765625, 61.765625, 78.71875, 40.847656, 78.71875);
    cairo_curve_to(cr, 19.933594, 78.71875, 2.976562, 61.765625, 2.976562, 40.847656);
    cairo_curve_to(cr, 2.976562, 19.933594, 19.933594, 2.976562, 40.847656, 2.976562);
    cairo_curve_to(cr, 61.765625, 2.976562, 78.71875, 19.933594, 78.71875, 40.847656);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
    cairo_fill_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 3);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0.301961,0.301961,0.301961,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 78.71875, 40.847656);
    cairo_curve_to(cr, 78.71875, 61.765625, 61.765625, 78.71875, 40.847656, 78.71875);
    cairo_curve_to(cr, 19.933594, 78.71875, 2.976562, 61.765625, 2.976562, 40.847656);
    cairo_curve_to(cr, 2.976562, 19.933594, 19.933594, 2.976562, 40.847656, 2.976562);
    cairo_curve_to(cr, 61.765625, 2.976562, 78.71875, 19.933594, 78.71875, 40.847656);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
//cairo_matrix_init(&matrix, 0.348816,0,0,0.348816,0.984138,-388.52027);
//cairo_pattern_set_matrix(pattern, &matrix);
    cairo_stroke_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 3);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0.2,0.2,0.2,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 81.625, 41.160156);
    cairo_curve_to(cr, 81.625, 63.507812, 63.507812, 81.625, 41.160156, 81.625);
    cairo_curve_to(cr, 18.8125, 81.625, 0.699219, 63.507812, 0.699219, 41.160156);
    cairo_curve_to(cr, 0.699219, 18.8125, 18.8125, 0.699219, 41.160156, 0.699219);
    cairo_curve_to(cr, 63.507812, 0.699219, 81.625, 18.8125, 81.625, 41.160156);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
//cairo_matrix_init(&matrix, 0.372692,0,0,0.372692,-1.432036,-417.597428);
//cairo_pattern_set_matrix(pattern, &matrix);
    cairo_stroke_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 3);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(1,1,1,0.760784);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 32.699219, 10.726562);
    cairo_curve_to(cr, 39.167969, 8.847656, 46.089844, 9.261719, 52.289062, 11.902344);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
//cairo_matrix_init(&matrix, 0.559793,0,0,0.559793,-141.483807,-609.127432);
//cairo_pattern_set_matrix(pattern, &matrix);
    cairo_stroke_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 3.2);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(1,1,1,0.760784);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 20.949219, 17.402344);
    cairo_curve_to(cr, 23.0625, 15.429688, 25.457031, 13.785156, 28.058594, 12.519531);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
//cairo_matrix_init(&matrix, 0.559793,0,0,0.559793,-141.483807,-609.127432);
//cairo_pattern_set_matrix(pattern, &matrix);
    cairo_stroke_preserve(cr);
    /********************/

    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 5);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_linear(10.846272, 1289.5225, 209.64394, 1142.0402);
    cairo_pattern_add_color_stop_rgba(pattern, 0,0.301961,0.301961,0.301961,0);
    cairo_pattern_add_color_stop_rgba(pattern, 0.5,0.627451,0.627451,0.627451,1);
    cairo_pattern_add_color_stop_rgba(pattern, 1,0.388235,0.388235,0.388235,0);
    cairo_matrix_init(&matrix, 2.853728,0,0,2.853728,-2.285712,1114.362164);
    cairo_pattern_set_matrix(pattern, &matrix);
    cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
    cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 78.894531, 40.847656);
    cairo_curve_to(cr, 78.894531, 61.859375, 61.859375, 78.894531, 40.847656, 78.894531);
    cairo_curve_to(cr, 19.835938, 78.894531, 2.804688, 61.859375, 2.804688, 40.847656);
    cairo_curve_to(cr, 2.804688, 19.835938, 19.835938, 2.804688, 40.847656, 2.804688);
    cairo_curve_to(cr, 61.859375, 2.804688, 78.894531, 19.835938, 78.894531, 40.847656);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
////cairo_matrix_init(&matrix, 0.350419,0,0,0.350419,0.800957,-390.49345);
////cairo_pattern_set_matrix(pattern, &matrix);
    cairo_stroke_preserve(cr);

    /********************/
}
#endif
