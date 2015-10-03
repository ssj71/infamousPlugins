#ifndef DRAW_LUSHGRAPHPOINT_H
#define DRAW_LUSHGRAPHPOINT_H
inline int cairo_code_draw_lushgraphpoint_get_width() { return 21; }
inline int cairo_code_draw_lushgraphpoint_get_height() { return 21; }
inline void cairo_code_draw_lushgraphpoint_render(cairo_t *cr) {
cairo_surface_t *temp_surface;
cairo_t *old_cr;
cairo_pattern_t *pattern;
cairo_matrix_t matrix;

cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 4);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(1,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 19.582031, 10.753906);
cairo_curve_to(cr, 19.582031, 15.636719, 15.621094, 19.597656, 10.734375, 19.597656);
cairo_curve_to(cr, 5.851562, 19.597656, 1.890625, 15.636719, 1.890625, 10.753906);
cairo_curve_to(cr, 1.890625, 5.867188, 5.851562, 1.910156, 10.734375, 1.910156);
cairo_curve_to(cr, 15.621094, 1.910156, 19.582031, 5.867188, 19.582031, 10.753906);
cairo_close_path(cr);
cairo_move_to(cr, 19.582031, 10.753906);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_matrix_init(&matrix, 0.952449,0,0,0.952449,318.921679,-179.030695);
cairo_pattern_set_matrix(pattern, &matrix);
cairo_stroke_preserve(cr);
/********************/
}
#endif
