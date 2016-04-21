#ifndef DRAW_LUSHGRAPHXBOUND_H
#define DRAW_LUSHGRAPHXBOUND_H
inline int cairo_code_draw_lushGraphXBound_get_width() { return 8; }
inline int cairo_code_draw_lushGraphXBound_get_height() { return 21; }
inline void cairo_code_draw_lushGraphXBound_render(cairo_t *cr, float r, float g, float b) {
cairo_pattern_t *pattern;
//cairo_matrix_t matrix;

cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 7.318619);
cairo_set_miter_limit(cr, 8);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(r,g,b,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 3.671875, 0.00390625);
cairo_line_to(cr, 3.671875, 20.652344);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
//cairo_matrix_init(&matrix, 1,0,0,1,7.3125,-18.09375);
//cairo_pattern_set_matrix(pattern, &matrix);
cairo_stroke_preserve(cr);
/********************/
}

inline void cairo_code_draw_lushGraphXBoundr_render(cairo_t *cr)
{
    cairo_code_draw_lushGraphXBound_render(cr, 1, 0, 0);
}

inline void cairo_code_draw_lushGraphXBoundb_render(cairo_t *cr)
{
    cairo_code_draw_lushGraphXBound_render(cr, 0.2, 0.1, 1);
}

inline void cairo_code_draw_lushGraphXBoundg_render(cairo_t *cr)
{
    cairo_code_draw_lushGraphXBound_render(cr, 0, 0.88235, 0);
}

inline void cairo_code_draw_lushGraphXBoundo_render(cairo_t *cr)
{
    cairo_code_draw_lushGraphXBound_render(cr, 1, .33333, 0);
}

inline void cairo_code_draw_lushGraphXBoundy_render(cairo_t *cr)
{
    cairo_code_draw_lushGraphXBound_render(cr, 0.92157, 0.92157, 0);
}

inline void cairo_code_draw_lushGraphXBoundp_render(cairo_t *cr)
{
    cairo_code_draw_lushGraphXBound_render(cr, 0.78431, 0, 1);
}
#endif
