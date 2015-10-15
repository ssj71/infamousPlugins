#ifndef DRAW_LUSHGRAPHPOINT_H
#define DRAW_LUSHGRAPHPOINT_H
inline int cairo_code_draw_lushGraphPoint_get_width() { return 21; }
inline int cairo_code_draw_lushGraphPoint_get_height() { return 21; }
inline void cairo_code_draw_lushGraphPoint_render(cairo_t *cr, float r, float g, float b) {
cairo_pattern_t *pattern;
cairo_matrix_t matrix;

cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 4);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(r,g,b,1);
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

inline void cairo_code_draw_lushGraphPointr_render(cairo_t *cr)
{
    cairo_code_draw_lushGraphPoint_render(cr, 1, 0, 0);
}

inline void cairo_code_draw_lushGraphPointb_render(cairo_t *cr)
{
    cairo_code_draw_lushGraphPoint_render(cr, .2, .1, 1);
}

inline void cairo_code_draw_lushGraphPointg_render(cairo_t *cr)
{
    cairo_code_draw_lushGraphPoint_render(cr, 0, 0.88235, 0);
}

inline void cairo_code_draw_lushGraphPointo_render(cairo_t *cr)
{
    cairo_code_draw_lushGraphPoint_render(cr, 1, .33333, 0);
}

inline void cairo_code_draw_lushGraphPointy_render(cairo_t *cr)
{
    cairo_code_draw_lushGraphPoint_render(cr, 0.92157, 0.92157, 0);
}

inline void cairo_code_draw_lushGraphPointp_render(cairo_t *cr)
{
    cairo_code_draw_lushGraphPoint_render(cr, 0.78431, 0, 1);
}

inline void cairo_code_draw_lushGraphPointw_render(cairo_t *cr)
{
    cairo_code_draw_lushGraphPoint_render(cr, 0.9, 0.9, 0.9);
}
#endif
