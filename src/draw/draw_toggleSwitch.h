#ifndef DRAW_TOGGLESWITCH_H
#define DRAW_TOGGLESWITCH_H
inline int cairo_code_draw_toggleSwitch_get_width()
{
    return 11;
}
inline int cairo_code_draw_toggleSwitch_get_height()
{
    return 36;
}
inline void cairo_code_draw_toggleSwitch_render(cairo_t *cr, int val)
{
    cairo_pattern_t *pattern;
    cairo_matrix_t matrix;

    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_rgba(0,0,0,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 9.957031, 17.996094);
    cairo_curve_to(cr, 9.957031, 20.507812, 7.921875, 22.539062, 5.414062, 22.539062);
    cairo_curve_to(cr, 2.90625, 22.539062, 0.871094, 20.507812, 0.871094, 17.996094);
    cairo_curve_to(cr, 0.871094, 15.488281, 2.90625, 13.457031, 5.414062, 13.457031);
    cairo_curve_to(cr, 7.921875, 13.457031, 9.957031, 15.488281, 9.957031, 17.996094);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
    cairo_fill_preserve(cr);
    /********************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    cairo_set_line_width(cr, 2);
    cairo_set_miter_limit(cr, 4);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    pattern = cairo_pattern_create_rgba(0.8,0.8,0.8,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 9.957031, 17.996094);
    cairo_curve_to(cr, 9.957031, 20.507812, 7.921875, 22.539062, 5.414062, 22.539062);
    cairo_curve_to(cr, 2.90625, 22.539062, 0.871094, 20.507812, 0.871094, 17.996094);
    cairo_curve_to(cr, 0.871094, 15.488281, 2.90625, 13.457031, 5.414062, 13.457031);
    cairo_curve_to(cr, 7.921875, 13.457031, 9.957031, 15.488281, 9.957031, 17.996094);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_stroke_preserve(cr);
    /********************/
    if(val)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_radial(-209.03572, 554.65656, 0, -209.03572, 554.65656, 6.726976);
        cairo_pattern_add_color_stop_rgba(pattern, 0,1,1,1,1);
        cairo_pattern_add_color_stop_rgba(pattern, 1,0.788235,0.788235,0.788235,1);
        cairo_matrix_init(&matrix, 0.0030724,-1.71592,0.148071,0.0556318,-208.806464,562.33495);
        cairo_pattern_set_matrix(pattern, &matrix);
        cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
        cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 4.988281, 0.726562);
        cairo_line_to(cr, 5.558594, 0.726562);
        cairo_curve_to(cr, 7.917969, 0.726562, 10.042969, 2.257812, 9.816406, 4.132812);
        cairo_line_to(cr, 8.054688, 18.574219);
        cairo_curve_to(cr, 7.828125, 20.449219, 7.917969, 21.070312, 5.558594, 21.070312);
        cairo_line_to(cr, 4.988281, 21.070312);
        cairo_curve_to(cr, 2.628906, 21.070312, 2.976562, 20.445312, 2.71875, 18.574219);
        cairo_line_to(cr, 0.730469, 4.132812);
        cairo_curve_to(cr, 0.472656, 2.261719, 2.628906, 0.726562, 4.988281, 0.726562);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
        /********************/
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        cairo_set_line_width(cr, 1.42198);
        cairo_set_miter_limit(cr, 4);
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
        pattern = cairo_pattern_create_rgba(0.8,0.8,0.8,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 4.988281, 0.726562);
        cairo_line_to(cr, 5.558594, 0.726562);
        cairo_curve_to(cr, 7.917969, 0.726562, 10.042969, 2.257812, 9.816406, 4.132812);
        cairo_line_to(cr, 8.054688, 18.574219);
        cairo_curve_to(cr, 7.828125, 20.449219, 7.917969, 21.070312, 5.558594, 21.070312);
        cairo_line_to(cr, 4.988281, 21.070312);
        cairo_curve_to(cr, 2.628906, 21.070312, 2.976562, 20.445312, 2.71875, 18.574219);
        cairo_line_to(cr, 0.730469, 4.132812);
        cairo_curve_to(cr, 0.472656, 2.261719, 2.628906, 0.726562, 4.988281, 0.726562);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_stroke_preserve(cr);
    }
    else
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_radial(-209.03572, 554.65656, 0, -209.03572, 554.65656, 6.726976);
        cairo_pattern_add_color_stop_rgba(pattern, 0,1,1,1,1);
        cairo_pattern_add_color_stop_rgba(pattern, 1,0.788235,0.788235,0.788235,1);
        cairo_matrix_init(&matrix, 0.0030724,-1.71592,-0.148071,-0.0556318,-203.505878,564.326439);
        cairo_pattern_set_matrix(pattern, &matrix);
        cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
        cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 4.988281, 35.070312);
        cairo_line_to(cr, 5.558594, 35.070312);
        cairo_curve_to(cr, 7.917969, 35.070312, 10.042969, 33.539062, 9.816406, 31.664062);
        cairo_line_to(cr, 8.054688, 17.222656);
        cairo_curve_to(cr, 7.828125, 15.347656, 7.917969, 14.726562, 5.558594, 14.726562);
        cairo_line_to(cr, 4.988281, 14.726562);
        cairo_curve_to(cr, 2.628906, 14.726562, 2.976562, 15.351562, 2.71875, 17.222656);
        cairo_line_to(cr, 0.730469, 31.664062);
        cairo_curve_to(cr, 0.472656, 33.539062, 2.628906, 35.070312, 4.988281, 35.070312);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
        /********************/
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        cairo_set_line_width(cr, 1.42198);
        cairo_set_miter_limit(cr, 4);
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
        pattern = cairo_pattern_create_rgba(0.8,0.8,0.8,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 4.988281, 35.070312);
        cairo_line_to(cr, 5.558594, 35.070312);
        cairo_curve_to(cr, 7.917969, 35.070312, 10.042969, 33.539062, 9.816406, 31.664062);
        cairo_line_to(cr, 8.054688, 17.222656);
        cairo_curve_to(cr, 7.828125, 15.347656, 7.917969, 14.726562, 5.558594, 14.726562);
        cairo_line_to(cr, 4.988281, 14.726562);
        cairo_curve_to(cr, 2.628906, 14.726562, 2.976562, 15.351562, 2.71875, 17.222656);
        cairo_line_to(cr, 0.730469, 31.664062);
        cairo_curve_to(cr, 0.472656, 33.539062, 2.628906, 35.070312, 4.988281, 35.070312);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_stroke_preserve(cr);
    }//if on
}
#endif
