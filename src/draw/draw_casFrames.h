#ifndef DRAW_CASCELLFRAME_H
#define DRAW_CASCELLFRAME_H
inline int cairo_code_draw_casCellFrame_get_width()
{
    return 252;
}
inline int cairo_code_draw_casCellFrame_get_height()
{
    return 482;
}
inline void cairo_code_draw_casCellFrame_render(cairo_t *cr)
{
    cairo_pattern_t *pattern;

    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 1.238209);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0,0,0,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 0.0078125, 0.617188);
    cairo_line_to(cr, 91.773438, 0.617188);
    cairo_line_to(cr, 91.773438, 110.347656);
    cairo_line_to(cr, 251.582031, 110.347656);
    cairo_line_to(cr, 251.582031, 481.925781);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_stroke_preserve(cr);
    /********************/
}
#endif
#ifndef DRAW_CASFRAME_H
#define DRAW_CASFRAME_H
inline int cairo_code_draw_casFrame_get_width()
{
    return 164;
}
inline int cairo_code_draw_casFrame_get_height()
{
    return 70;
}
inline void cairo_code_draw_casFrame_render(cairo_t *cr)
{
    cairo_pattern_t *pattern;

    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 1.238209);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0,0,0,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 0.0117188, 0.621094);
    cairo_line_to(cr, 163.785156, 0.621094);
    cairo_line_to(cr, 163.785156, 69.609375);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_stroke_preserve(cr);
    /********************/
}
#endif
