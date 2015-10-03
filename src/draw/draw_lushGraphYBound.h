#ifndef DRAW_LUSHGRAPHYBOUND_H
#define DRAW_LUSHGRAPHYBOUND_H
inline int cairo_code_draw_lushGraphYBound_get_width() { return 21; }
inline int cairo_code_draw_lushGraphYBound_get_height() { return 3; }
inline void cairo_code_draw_lushGraphYBound_render(cairo_t *cr) {
cairo_surface_t *temp_surface;
cairo_t *old_cr;
cairo_pattern_t *pattern;
cairo_matrix_t matrix;

cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 3.318619);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(1,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 0, 1.671875);
cairo_line_to(cr, 20.648438, 1.671875);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_matrix_init(&matrix, 1,0,0,1,-52.0625,-16.875);
cairo_pattern_set_matrix(pattern, &matrix);
cairo_stroke_preserve(cr);
/********************/
}

inline void cairo_code_draw_lushGraphYBoundr_render(cairo_t *cr)
{
    cairo_code_draw_lushGraphYBound_render(cr, 1, 0, 0);
}

inline void cairo_code_draw_lushGraphYBoundb_render(cairo_t *cr)
{
    cairo_code_draw_lushGraphYBound_render(cr, 0, 0, 1);
}

inline void cairo_code_draw_lushGraphYBoundg_render(cairo_t *cr)
{
    cairo_code_draw_lushGraphYBound_render(cr, 0, 0.88235, 0);
}

inline void cairo_code_draw_lushGraphYBoundo_render(cairo_t *cr)
{
    cairo_code_draw_lushGraphYBound_render(cr, 1, .33333, 0);
}

inline void cairo_code_draw_lushGraphYBoundy_render(cairo_t *cr)
{
    cairo_code_draw_lushGraphYBound_render(cr, 0.92157, 0.92157, 0);
}

inline void cairo_code_draw_lushGraphYBoundp_render(cairo_t *cr)
{
    cairo_code_draw_lushGraphYBound_render(cr, 0.78431, 0, 1);
} 
#endif
