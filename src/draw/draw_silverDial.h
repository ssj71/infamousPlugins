#ifndef DRAW_SILVERDIAL_H
#define DRAW_SILVERDIAL_H
#define PI 3.1415926535897932384626433832795
inline int cairo_code_draw_silverDial_get_width() { return 77; }
inline int cairo_code_draw_silverDial_get_height() { return 77; }
inline void cairo_code_draw_silverDial_render(cairo_t *cr, float val) {
cairo_surface_t *temp_surface;
cairo_t *old_cr;
cairo_pattern_t *pattern;
cairo_matrix_t matrix;

cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_radial(78.072823, 172.32506, 0, 78.072823, 172.32506, 20.063856);
cairo_pattern_add_color_stop_rgba(pattern, 0,0,0,0,1);
cairo_pattern_add_color_stop_rgba(pattern, 0.892578,1,1,1,1);
cairo_pattern_add_color_stop_rgba(pattern, 1,0,0,0,0);
cairo_matrix_init(&matrix, -0.0149068,0.110392,-0.124934,-0.0131716,85.376704,167.709986);
cairo_pattern_set_matrix(pattern, &matrix);
cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 75.730469, 38.265625);
cairo_curve_to(cr, 75.734375, 58.960938, 58.960938, 75.738281, 38.265625, 75.738281);
cairo_curve_to(cr, 17.574219, 75.738281, 0.800781, 58.960938, 0.804688, 38.265625);
cairo_curve_to(cr, 0.800781, 17.574219, 17.574219, 0.796875, 38.265625, 0.796875);
cairo_curve_to(cr, 58.960938, 0.796875, 75.734375, 17.574219, 75.730469, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 1.605914);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(0,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 75.730469, 38.265625);
cairo_curve_to(cr, 75.734375, 58.960938, 58.960938, 75.738281, 38.265625, 75.738281);
cairo_curve_to(cr, 17.574219, 75.738281, 0.800781, 58.960938, 0.804688, 38.265625);
cairo_curve_to(cr, 0.800781, 17.574219, 17.574219, 0.796875, 38.265625, 0.796875);
cairo_curve_to(cr, 58.960938, 0.796875, 75.734375, 17.574219, 75.730469, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_stroke_preserve(cr);
/********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(0.94902,0.94902,0.94902,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 70.070312, 38.265625);
cairo_curve_to(cr, 70.074219, 55.832031, 55.832031, 70.078125, 38.265625, 70.078125);
cairo_curve_to(cr, 20.699219, 70.078125, 6.460938, 55.832031, 6.464844, 38.265625);
cairo_curve_to(cr, 6.460938, 20.699219, 20.699219, 6.457031, 38.265625, 6.457031);
cairo_curve_to(cr, 55.832031, 6.457031, 70.074219, 20.699219, 70.070312, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 1.363251);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(0,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 70.070312, 38.265625);
cairo_curve_to(cr, 70.074219, 55.832031, 55.832031, 70.078125, 38.265625, 70.078125);
cairo_curve_to(cr, 20.699219, 70.078125, 6.460938, 55.832031, 6.464844, 38.265625);
cairo_curve_to(cr, 6.460938, 20.699219, 20.699219, 6.457031, 38.265625, 6.457031);
cairo_curve_to(cr, 55.832031, 6.457031, 70.074219, 20.699219, 70.070312, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_stroke_preserve(cr);
/********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(0.94902,0.94902,0.94902,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 66.671875, 38.265625);
cairo_curve_to(cr, 66.675781, 53.957031, 53.957031, 66.679688, 38.265625, 66.679688);
cairo_curve_to(cr, 22.574219, 66.679688, 9.855469, 53.957031, 9.859375, 38.265625);
cairo_curve_to(cr, 9.855469, 22.574219, 22.574219, 9.855469, 38.265625, 9.855469);
cairo_curve_to(cr, 53.957031, 9.855469, 66.675781, 22.574219, 66.671875, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 1.217653);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(0,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 66.671875, 38.265625);
cairo_curve_to(cr, 66.675781, 53.957031, 53.957031, 66.679688, 38.265625, 66.679688);
cairo_curve_to(cr, 22.574219, 66.679688, 9.855469, 53.957031, 9.859375, 38.265625);
cairo_curve_to(cr, 9.855469, 22.574219, 22.574219, 9.855469, 38.265625, 9.855469);
cairo_curve_to(cr, 53.957031, 9.855469, 66.675781, 22.574219, 66.671875, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_stroke_preserve(cr);
/********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(0.94902,0.94902,0.94902,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 63.277344, 38.265625);
cairo_curve_to(cr, 63.28125, 52.082031, 52.082031, 63.285156, 38.265625, 63.285156);
cairo_curve_to(cr, 24.453125, 63.285156, 13.253906, 52.082031, 13.257812, 38.265625);
cairo_curve_to(cr, 13.253906, 24.453125, 24.453125, 13.25, 38.265625, 13.25);
cairo_curve_to(cr, 52.082031, 13.25, 63.28125, 24.453125, 63.277344, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 1.072056);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(0,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 63.277344, 38.265625);
cairo_curve_to(cr, 63.28125, 52.082031, 52.082031, 63.285156, 38.265625, 63.285156);
cairo_curve_to(cr, 24.453125, 63.285156, 13.253906, 52.082031, 13.257812, 38.265625);
cairo_curve_to(cr, 13.253906, 24.453125, 24.453125, 13.25, 38.265625, 13.25);
cairo_curve_to(cr, 52.082031, 13.25, 63.28125, 24.453125, 63.277344, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_stroke_preserve(cr);
/********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(0.94902,0.94902,0.94902,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 60.605469, 38.265625);
cairo_curve_to(cr, 60.609375, 50.609375, 50.609375, 60.613281, 38.265625, 60.613281);
cairo_curve_to(cr, 25.925781, 60.613281, 15.921875, 50.609375, 15.929688, 38.265625);
cairo_curve_to(cr, 15.921875, 25.925781, 25.925781, 15.921875, 38.265625, 15.921875);
cairo_curve_to(cr, 50.609375, 15.921875, 60.609375, 25.925781, 60.605469, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 0.957558);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(0,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 60.605469, 38.265625);
cairo_curve_to(cr, 60.609375, 50.609375, 50.609375, 60.613281, 38.265625, 60.613281);
cairo_curve_to(cr, 25.925781, 60.613281, 15.921875, 50.609375, 15.929688, 38.265625);
cairo_curve_to(cr, 15.921875, 25.925781, 25.925781, 15.921875, 38.265625, 15.921875);
cairo_curve_to(cr, 50.609375, 15.921875, 60.609375, 25.925781, 60.605469, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_stroke_preserve(cr);
/********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(0.94902,0.94902,0.94902,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 70.070312, 38.265625);
cairo_curve_to(cr, 70.074219, 55.832031, 55.832031, 70.078125, 38.265625, 70.078125);
cairo_curve_to(cr, 20.699219, 70.078125, 6.460938, 55.832031, 6.464844, 38.265625);
cairo_curve_to(cr, 6.460938, 20.699219, 20.699219, 6.457031, 38.265625, 6.457031);
cairo_curve_to(cr, 55.832031, 6.457031, 70.074219, 20.699219, 70.070312, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 1.363251);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(0,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 70.070312, 38.265625);
cairo_curve_to(cr, 70.074219, 55.832031, 55.832031, 70.078125, 38.265625, 70.078125);
cairo_curve_to(cr, 20.699219, 70.078125, 6.460938, 55.832031, 6.464844, 38.265625);
cairo_curve_to(cr, 6.460938, 20.699219, 20.699219, 6.457031, 38.265625, 6.457031);
cairo_curve_to(cr, 55.832031, 6.457031, 70.074219, 20.699219, 70.070312, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_stroke_preserve(cr);
/********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(0.94902,0.94902,0.94902,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 66.671875, 38.265625);
cairo_curve_to(cr, 66.675781, 53.957031, 53.957031, 66.679688, 38.265625, 66.679688);
cairo_curve_to(cr, 22.574219, 66.679688, 9.855469, 53.957031, 9.859375, 38.265625);
cairo_curve_to(cr, 9.855469, 22.574219, 22.574219, 9.855469, 38.265625, 9.855469);
cairo_curve_to(cr, 53.957031, 9.855469, 66.675781, 22.574219, 66.671875, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 1.217653);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(0,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 66.671875, 38.265625);
cairo_curve_to(cr, 66.675781, 53.957031, 53.957031, 66.679688, 38.265625, 66.679688);
cairo_curve_to(cr, 22.574219, 66.679688, 9.855469, 53.957031, 9.859375, 38.265625);
cairo_curve_to(cr, 9.855469, 22.574219, 22.574219, 9.855469, 38.265625, 9.855469);
cairo_curve_to(cr, 53.957031, 9.855469, 66.675781, 22.574219, 66.671875, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_stroke_preserve(cr);
/********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(0.94902,0.94902,0.94902,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 63.277344, 38.265625);
cairo_curve_to(cr, 63.28125, 52.082031, 52.082031, 63.285156, 38.265625, 63.285156);
cairo_curve_to(cr, 24.453125, 63.285156, 13.253906, 52.082031, 13.257812, 38.265625);
cairo_curve_to(cr, 13.253906, 24.453125, 24.453125, 13.25, 38.265625, 13.25);
cairo_curve_to(cr, 52.082031, 13.25, 63.28125, 24.453125, 63.277344, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 1.072056);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(0,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 63.277344, 38.265625);
cairo_curve_to(cr, 63.28125, 52.082031, 52.082031, 63.285156, 38.265625, 63.285156);
cairo_curve_to(cr, 24.453125, 63.285156, 13.253906, 52.082031, 13.257812, 38.265625);
cairo_curve_to(cr, 13.253906, 24.453125, 24.453125, 13.25, 38.265625, 13.25);
cairo_curve_to(cr, 52.082031, 13.25, 63.28125, 24.453125, 63.277344, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_stroke_preserve(cr);
/********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(0.94902,0.94902,0.94902,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 60.289062, 38.265625);
cairo_curve_to(cr, 60.292969, 50.429688, 50.429688, 60.296875, 38.265625, 60.296875);
cairo_curve_to(cr, 26.101562, 60.296875, 16.242188, 50.429688, 16.246094, 38.265625);
cairo_curve_to(cr, 16.242188, 26.101562, 26.101562, 16.238281, 38.265625, 16.238281);
cairo_curve_to(cr, 50.429688, 16.238281, 60.292969, 26.101562, 60.289062, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 1);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(0,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 60.289062, 38.265625);
cairo_curve_to(cr, 60.292969, 50.429688, 50.429688, 60.296875, 38.265625, 60.296875);
cairo_curve_to(cr, 26.101562, 60.296875, 16.242188, 50.429688, 16.246094, 38.265625);
cairo_curve_to(cr, 16.242188, 26.101562, 26.101562, 16.238281, 38.265625, 16.238281);
cairo_curve_to(cr, 50.429688, 16.238281, 60.292969, 26.101562, 60.289062, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_stroke_preserve(cr);
/********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(0.94902,0.94902,0.94902,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 56.890625, 38.265625);
cairo_curve_to(cr, 56.890625, 48.554688, 48.554688, 56.894531, 38.265625, 56.894531);
cairo_curve_to(cr, 27.980469, 56.894531, 19.640625, 48.554688, 19.644531, 38.265625);
cairo_curve_to(cr, 19.640625, 27.980469, 27.980469, 19.640625, 38.265625, 19.640625);
cairo_curve_to(cr, 48.554688, 19.640625, 56.890625, 27.980469, 56.890625, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 1);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(0,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 56.890625, 38.265625);
cairo_curve_to(cr, 56.890625, 48.554688, 48.554688, 56.894531, 38.265625, 56.894531);
cairo_curve_to(cr, 27.980469, 56.894531, 19.640625, 48.554688, 19.644531, 38.265625);
cairo_curve_to(cr, 19.640625, 27.980469, 27.980469, 19.640625, 38.265625, 19.640625);
cairo_curve_to(cr, 48.554688, 19.640625, 56.890625, 27.980469, 56.890625, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_stroke_preserve(cr);
/********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(0.94902,0.94902,0.94902,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 53.839844, 38.265625);
cairo_curve_to(cr, 53.839844, 46.867188, 46.867188, 53.839844, 38.265625, 53.839844);
cairo_curve_to(cr, 29.664062, 53.839844, 22.695312, 46.867188, 22.695312, 38.265625);
cairo_curve_to(cr, 22.695312, 29.667969, 29.664062, 22.695312, 38.265625, 22.695312);
cairo_curve_to(cr, 46.867188, 22.695312, 53.839844, 29.667969, 53.839844, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 0.941438);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(0,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 53.839844, 38.265625);
cairo_curve_to(cr, 53.839844, 46.867188, 46.867188, 53.839844, 38.265625, 53.839844);
cairo_curve_to(cr, 29.664062, 53.839844, 22.695312, 46.867188, 22.695312, 38.265625);
cairo_curve_to(cr, 22.695312, 29.667969, 29.664062, 22.695312, 38.265625, 22.695312);
cairo_curve_to(cr, 46.867188, 22.695312, 53.839844, 29.667969, 53.839844, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_stroke_preserve(cr);
/********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(0.94902,0.94902,0.94902,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 51.234375, 38.265625);
cairo_curve_to(cr, 51.234375, 45.429688, 45.429688, 51.234375, 38.265625, 51.234375);
cairo_curve_to(cr, 31.105469, 51.234375, 25.300781, 45.429688, 25.300781, 38.265625);
cairo_curve_to(cr, 25.300781, 31.105469, 31.105469, 25.300781, 38.265625, 25.300781);
cairo_curve_to(cr, 45.429688, 25.300781, 51.234375, 31.105469, 51.234375, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 0.873399);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(0,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 51.234375, 38.265625);
cairo_curve_to(cr, 51.234375, 45.429688, 45.429688, 51.234375, 38.265625, 51.234375);
cairo_curve_to(cr, 31.105469, 51.234375, 25.300781, 45.429688, 25.300781, 38.265625);
cairo_curve_to(cr, 25.300781, 31.105469, 31.105469, 25.300781, 38.265625, 25.300781);
cairo_curve_to(cr, 45.429688, 25.300781, 51.234375, 31.105469, 51.234375, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_stroke_preserve(cr);
/********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(0.94902,0.94902,0.94902,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 48.269531, 38.265625);
cairo_curve_to(cr, 48.269531, 43.792969, 43.792969, 48.269531, 38.265625, 48.269531);
cairo_curve_to(cr, 32.742188, 48.269531, 28.265625, 43.792969, 28.265625, 38.265625);
cairo_curve_to(cr, 28.265625, 32.742188, 32.742188, 28.265625, 38.265625, 28.265625);
cairo_curve_to(cr, 43.792969, 28.265625, 48.269531, 32.742188, 48.269531, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 0.873399);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(0,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 48.269531, 38.265625);
cairo_curve_to(cr, 48.269531, 43.792969, 43.792969, 48.269531, 38.265625, 48.269531);
cairo_curve_to(cr, 32.742188, 48.269531, 28.265625, 43.792969, 28.265625, 38.265625);
cairo_curve_to(cr, 28.265625, 32.742188, 32.742188, 28.265625, 38.265625, 28.265625);
cairo_curve_to(cr, 43.792969, 28.265625, 48.269531, 32.742188, 48.269531, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_stroke_preserve(cr);
/********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(0.94902,0.94902,0.94902,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 44.933594, 38.265625);
cairo_curve_to(cr, 44.9375, 41.949219, 41.949219, 44.9375, 38.265625, 44.9375);
cairo_curve_to(cr, 34.582031, 44.9375, 31.597656, 41.949219, 31.597656, 38.265625);
cairo_curve_to(cr, 31.597656, 34.582031, 34.582031, 31.597656, 38.265625, 31.597656);
cairo_curve_to(cr, 41.949219, 31.597656, 44.9375, 34.582031, 44.933594, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 0.873399);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(0,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 44.933594, 38.265625);
cairo_curve_to(cr, 44.9375, 41.949219, 41.949219, 44.9375, 38.265625, 44.9375);
cairo_curve_to(cr, 34.582031, 44.9375, 31.597656, 41.949219, 31.597656, 38.265625);
cairo_curve_to(cr, 31.597656, 34.582031, 34.582031, 31.597656, 38.265625, 31.597656);
cairo_curve_to(cr, 41.949219, 31.597656, 44.9375, 34.582031, 44.933594, 38.265625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_stroke_preserve(cr);
/********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_linear(312.13715, 443.2402, 329.30975, 426.57266);
cairo_pattern_add_color_stop_rgba(pattern, 0,1,1,1,0.486275);
cairo_pattern_add_color_stop_rgba(pattern, 0.512333,1,1,1,0.803922);
cairo_pattern_add_color_stop_rgba(pattern, 1,1,1,1,0.486275);
cairo_matrix_init(&matrix, 0.617641,0,0,0.617641,297.761798,408.242033);
cairo_pattern_set_matrix(pattern, &matrix);
cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 24.507812, 28.515625);
cairo_curve_to(cr, 19.691406, 25.445312, 15.339844, 22.527344, 14.839844, 22.023438);
cairo_curve_to(cr, 12.953125, 20.140625, 25.632812, 9.644531, 29.792969, 9.644531);
cairo_curve_to(cr, 30.226562, 9.644531, 31.417969, 13.878906, 32.441406, 19.050781);
cairo_curve_to(cr, 33.464844, 24.222656, 34.671875, 29.742188, 35.121094, 31.316406);
cairo_curve_to(cr, 36.269531, 35.347656, 34.488281, 34.875, 24.507812, 28.515625);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_linear(312.13715, 443.2402, 329.30975, 426.57266);
cairo_pattern_add_color_stop_rgba(pattern, 0,1,1,1,0.486275);
cairo_pattern_add_color_stop_rgba(pattern, 0.59839,1,1,1,0.803922);
cairo_pattern_add_color_stop_rgba(pattern, 1,1,1,1,0.486275);
cairo_matrix_init(&matrix, 0.617641,0,0,0.617641,297.761798,408.242033);
cairo_pattern_set_matrix(pattern, &matrix);
cairo_pattern_set_extend(pattern, CAIRO_EXTEND_PAD);
cairo_pattern_set_filter(pattern, CAIRO_FILTER_GOOD);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 43.898438, 57.484375);
cairo_curve_to(cr, 42.871094, 52.3125, 41.664062, 46.785156, 41.214844, 45.207031);
cairo_curve_to(cr, 40.605469, 43.078125, 43.179688, 44.078125, 51.140625, 49.066406);
cairo_curve_to(cr, 57.046875, 52.773438, 61.882812, 56.359375, 61.882812, 57.035156);
cairo_curve_to(cr, 61.882812, 58.664062, 49.960938, 66.886719, 47.601562, 66.886719);
cairo_curve_to(cr, 46.589844, 66.886719, 44.921875, 62.65625, 43.898438, 57.484375);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/

cairo_translate(cr,45.5,45.5);
cairo_rotate(cr,3*PI/2*val - 3*PI/4);
cairo_translate(cr,-45.5,-45.5);

cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(0,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 36.828125, 7.128906);
cairo_line_to(cr, 39.703125, 7.128906);
cairo_line_to(cr, 39.703125, 17.976562);
cairo_line_to(cr, 36.828125, 17.976562);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 0.745483);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(0,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 36.828125, 7.128906);
cairo_line_to(cr, 39.703125, 7.128906);
cairo_line_to(cr, 39.703125, 17.976562);
cairo_line_to(cr, 36.828125, 17.976562);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_stroke_preserve(cr);
/********************/
}
#endif
