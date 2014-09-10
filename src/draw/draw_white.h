#ifndef DRAW_WHITE_H
#define DRAW_WHITE_H
inline int cairo_code_draw_white_get_width() { return 99; }
inline int cairo_code_draw_white_get_height() { return 119; }
inline void cairo_code_draw_white_render(cairo_t *cr) {
cairo_surface_t *temp_surface;
cairo_t *old_cr;
cairo_pattern_t *pattern;
cairo_matrix_t matrix;

cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(1,1,1,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_paint(cr);
/********************/
}
#endif
