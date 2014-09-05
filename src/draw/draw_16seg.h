#ifndef DRAW_BLUE16SEG_H
#define DRAW_BLUE16SEG_H
#include"blur.h"
inline int cairo_code_draw_16seg_get_width() { return 30; }
inline int cairo_code_draw_16seg_get_height() { return 45; }
inline short char2seg(char c);
inline void cairo_code_draw_16seg_render(cairo_t *cr, char num, char color) {
//r = 0;
//o = 1;
//y = 2;
//g = 3;
//b = 4;
//i = 5;
//v = 6;
float r,g,b, rd,gd,bd;//lit and dark colors;
switch(color)
{
  case 0://red
    r = 1; g = 0; b = 0;
    rd = .3333; gd = 0; bd = 0;
    break;
  case 3://green
    r = 0; g = 1; b = 0;
    rd = 0; gd = .3333; bd = 0;
    break;
  case 4://blue
    r = 0; g = 0; b = 1;
    rd = 0; gd = 0; bd = .3333;
    break;
  default://red
    r = 1; g = 0; b = 0;
    rd = .3333; gd = 0; bd = 0;
    break;
}

unsigned short val = char2seg(num);

cairo_surface_t *temp_surface;
cairo_t *old_cr;
cairo_pattern_t *pattern;
cairo_matrix_t matrix;

cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(0.4,0.4,0.4,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 3.742188, 0.75);
cairo_line_to(cr, 26.476562, 0.75);
cairo_curve_to(cr, 28.132812, 0.75, 29.476562, 2.089844, 29.476562, 3.746094);
cairo_line_to(cr, 29.476562, 41.539062);
cairo_curve_to(cr, 29.476562, 43.195312, 28.132812, 44.539062, 26.476562, 44.539062);
cairo_line_to(cr, 3.742188, 44.539062);
cairo_curve_to(cr, 2.082031, 44.539062, 0.742188, 43.195312, 0.742188, 41.539062);
cairo_line_to(cr, 0.742188, 3.746094);
cairo_curve_to(cr, 0.742188, 2.089844, 2.082031, 0.75, 3.742188, 0.75);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
cairo_set_line_width(cr, 1.5);
cairo_set_miter_limit(cr, 4);
cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
pattern = cairo_pattern_create_rgba(0,0,0,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 3.742188, 0.75);
cairo_line_to(cr, 26.476562, 0.75);
cairo_curve_to(cr, 28.132812, 0.75, 29.476562, 2.089844, 29.476562, 3.746094);
cairo_line_to(cr, 29.476562, 41.539062);
cairo_curve_to(cr, 29.476562, 43.195312, 28.132812, 44.539062, 26.476562, 44.539062);
cairo_line_to(cr, 3.742188, 44.539062);
cairo_curve_to(cr, 2.082031, 44.539062, 0.742188, 43.195312, 0.742188, 41.539062);
cairo_line_to(cr, 0.742188, 3.746094);
cairo_curve_to(cr, 0.742188, 2.089844, 2.082031, 0.75, 3.742188, 0.75);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_matrix_init(&matrix, 1,r,g,b,-267.28903,-419.23204);
cairo_pattern_set_matrix(pattern, &matrix);
cairo_stroke_preserve(cr);
/********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 10.234375, 3.066406);
cairo_line_to(cr, 8.992188, 4.316406);
cairo_line_to(cr, 11.425781, 7.816406);
cairo_line_to(cr, 15.039062, 7.816406);
cairo_line_to(cr, 17.148438, 5.691406);
cairo_line_to(cr, 17.539062, 3.066406);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 18.382812, 3.066406);
cairo_line_to(cr, 17.992188, 5.691406);
cairo_line_to(cr, 19.46875, 7.816406);
cairo_line_to(cr, 23.054688, 7.816406);
cairo_line_to(cr, 26.558594, 4.285156);
cairo_line_to(cr, 25.710938, 3.066406);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 27.058594, 5.003906);
cairo_line_to(cr, 23.554688, 8.535156);
cairo_line_to(cr, 22.941406, 12.660156);
cairo_line_to(cr, 22.539062, 15.347656);
cairo_line_to(cr, 22.023438, 18.816406);
cairo_line_to(cr, 23.871094, 21.472656);
cairo_line_to(cr, 25.980469, 19.347656);
cairo_line_to(cr, 27.285156, 10.566406);
cairo_line_to(cr, 27.925781, 6.253906);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 8.28125, 5.035156);
cairo_line_to(cr, 7.070312, 6.253906);
cairo_line_to(cr, 6.429688, 10.566406);
cairo_line_to(cr, 6.402344, 10.566406);
cairo_curve_to(cr, 5.949219, 13.617188, 5.53125, 16.421875, 5.09375, 19.347656);
cairo_line_to(cr, 6.574219, 21.472656);
cairo_line_to(cr, 9.179688, 18.847656);
cairo_line_to(cr, 9.699219, 15.347656);
cairo_line_to(cr, 10.097656, 12.660156);
cairo_line_to(cr, 10.71875, 8.503906);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 17.429688, 6.628906);
cairo_line_to(cr, 15.476562, 8.597656);
cairo_line_to(cr, 14.964844, 12.035156);
cairo_line_to(cr, 14.566406, 14.722656);
cairo_line_to(cr, 13.949219, 18.847656);
cairo_line_to(cr, 15.242188, 21.160156);
cairo_line_to(cr, 17.246094, 18.847656);
cairo_line_to(cr, 17.871094, 14.660156);
cairo_line_to(cr, 18.261719, 12.035156);
cairo_line_to(cr, 18.777344, 8.566406);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 11.515625, 8.816406);
cairo_line_to(cr, 10.6875, 14.378906);
cairo_line_to(cr, 12.117188, 18.597656);
cairo_line_to(cr, 13.144531, 18.597656);
cairo_line_to(cr, 13.976562, 13.003906);
cairo_line_to(cr, 12.570312, 8.816406);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 21.585938, 8.816406);
cairo_line_to(cr, 18.96875, 12.941406);
cairo_line_to(cr, 18.128906, 18.597656);
cairo_line_to(cr, 19.15625, 18.597656);
cairo_line_to(cr, 21.839844, 14.378906);
cairo_line_to(cr, 22.667969, 8.816406);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 9.648438, 19.597656);
cairo_line_to(cr, 7.289062, 21.972656);
cairo_line_to(cr, 8.941406, 24.347656);
cairo_line_to(cr, 12.527344, 24.347656);
cairo_line_to(cr, 14.566406, 21.972656);
cairo_line_to(cr, 13.234375, 19.597656);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 21.980469, 38.910156);
cairo_line_to(cr, 23.191406, 37.691406);
cairo_line_to(cr, 23.832031, 33.378906);
cairo_line_to(cr, 23.859375, 33.378906);
cairo_curve_to(cr, 24.3125, 30.324219, 24.730469, 27.519531, 25.164062, 24.597656);
cairo_line_to(cr, 23.6875, 22.472656);
cairo_line_to(cr, 21.082031, 25.097656);
cairo_line_to(cr, 20.5625, 28.597656);
cairo_line_to(cr, 20.160156, 31.285156);
cairo_line_to(cr, 19.542969, 35.441406);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 17.742188, 19.597656);
cairo_line_to(cr, 15.699219, 21.972656);
cairo_line_to(cr, 17.035156, 24.347656);
cairo_line_to(cr, 20.648438, 24.347656);
cairo_line_to(cr, 23.003906, 21.972656);
cairo_line_to(cr, 21.355469, 19.597656);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 11.085938, 25.347656);
cairo_line_to(cr, 8.433594, 29.535156);
cairo_line_to(cr, 7.597656, 35.128906);
cairo_line_to(cr, 8.652344, 35.128906);
cairo_line_to(cr, 11.304688, 30.972656);
cairo_line_to(cr, 12.140625, 25.347656);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 4.609375, 40.878906);
cairo_line_to(cr, 3.738281, 39.628906);
cairo_line_to(cr, 7.214844, 36.128906);
cairo_line_to(cr, 10.824219, 36.128906);
cairo_line_to(cr, 12.304688, 38.253906);
cairo_line_to(cr, 11.914062, 40.878906);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 12.757812, 40.878906);
cairo_line_to(cr, 13.148438, 38.253906);
cairo_line_to(cr, 15.253906, 36.128906);
cairo_line_to(cr, 18.84375, 36.128906);
cairo_line_to(cr, 21.296875, 39.660156);
cairo_line_to(cr, 20.085938, 40.878906);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 3.238281, 38.910156);
cairo_line_to(cr, 2.394531, 37.691406);
cairo_line_to(cr, 3.035156, 33.378906);
cairo_line_to(cr, 3.007812, 33.378906);
cairo_curve_to(cr, 3.460938, 30.324219, 3.878906, 27.519531, 4.316406, 24.597656);
cairo_line_to(cr, 6.421875, 22.472656);
cairo_line_to(cr, 8.25, 25.097656);
cairo_line_to(cr, 7.726562, 28.597656);
cairo_line_to(cr, 7.328125, 31.285156);
cairo_line_to(cr, 6.710938, 35.441406);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 12.863281, 37.316406);
cairo_line_to(cr, 11.496094, 35.347656);
cairo_line_to(cr, 12.007812, 31.910156);
cairo_line_to(cr, 12.40625, 29.222656);
cairo_line_to(cr, 13.019531, 25.097656);
cairo_line_to(cr, 15, 22.785156);
cairo_line_to(cr, 16.316406, 25.097656);
cairo_line_to(cr, 15.695312, 29.285156);
cairo_line_to(cr, 15.304688, 31.910156);
cairo_line_to(cr, 14.789062, 35.378906);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 17.671875, 35.128906);
cairo_line_to(cr, 16.28125, 31.003906);
cairo_line_to(cr, 17.125, 25.347656);
cairo_line_to(cr, 18.152344, 25.347656);
cairo_line_to(cr, 19.582031, 29.566406);
cairo_line_to(cr, 18.753906, 35.128906);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /******** dot ************/
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 27.921875, 38.828125);
cairo_curve_to(cr, 27.921875, 39.96875, 26.996094, 40.898438, 25.851562, 40.898438);
cairo_curve_to(cr, 24.710938, 40.898438, 23.78125, 39.96875, 23.785156, 38.828125);
cairo_curve_to(cr, 23.78125, 37.683594, 24.710938, 36.757812, 25.851562, 36.757812);
cairo_curve_to(cr, 26.996094, 36.757812, 27.921875, 37.683594, 27.921875, 38.828125);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
 /********************/

//blur
temp_surface = cairo_image_surface_create( CAIRO_FORMAT_ARGB32,30,45);
old_cr = cr;
cr = cairo_create(temp_surface);

if(val&0x8000){
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(r,g,b,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 10.234375, 3.066406);
cairo_line_to(cr, 8.992188, 4.316406);
cairo_line_to(cr, 11.425781, 7.816406);
cairo_line_to(cr, 15.039062, 7.816406);
cairo_line_to(cr, 17.148438, 5.691406);
cairo_line_to(cr, 17.539062, 3.066406);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
}
 /********************/
if(val&0x4000){
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(r,g,b,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 18.382812, 3.066406);
cairo_line_to(cr, 17.992188, 5.691406);
cairo_line_to(cr, 19.46875, 7.816406);
cairo_line_to(cr, 23.054688, 7.816406);
cairo_line_to(cr, 26.558594, 4.285156);
cairo_line_to(cr, 25.710938, 3.066406);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
}
 /********************/
if(val&0x2000){
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(r,g,b,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 27.058594, 5.003906);
cairo_line_to(cr, 23.554688, 8.535156);
cairo_line_to(cr, 22.941406, 12.660156);
cairo_line_to(cr, 22.539062, 15.347656);
cairo_line_to(cr, 22.023438, 18.816406);
cairo_line_to(cr, 23.871094, 21.472656);
cairo_line_to(cr, 25.980469, 19.347656);
cairo_line_to(cr, 27.285156, 10.566406);
cairo_line_to(cr, 27.925781, 6.253906);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
}
 /********************/
if(val&0x1000){
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(r,g,b,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 8.28125, 5.035156);
cairo_line_to(cr, 7.070312, 6.253906);
cairo_line_to(cr, 6.429688, 10.566406);
cairo_line_to(cr, 6.402344, 10.566406);
cairo_curve_to(cr, 5.949219, 13.617188, 5.53125, 16.421875, 5.09375, 19.347656);
cairo_line_to(cr, 6.574219, 21.472656);
cairo_line_to(cr, 9.179688, 18.847656);
cairo_line_to(cr, 9.699219, 15.347656);
cairo_line_to(cr, 10.097656, 12.660156);
cairo_line_to(cr, 10.71875, 8.503906);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
}
 /********************/
if(val&0x0800){
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(r,g,b,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 17.429688, 6.628906);
cairo_line_to(cr, 15.476562, 8.597656);
cairo_line_to(cr, 14.964844, 12.035156);
cairo_line_to(cr, 14.566406, 14.722656);
cairo_line_to(cr, 13.949219, 18.847656);
cairo_line_to(cr, 15.242188, 21.160156);
cairo_line_to(cr, 17.246094, 18.847656);
cairo_line_to(cr, 17.871094, 14.660156);
cairo_line_to(cr, 18.261719, 12.035156);
cairo_line_to(cr, 18.777344, 8.566406);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
}
 /********************/
if(val&0x0400){
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(r,g,b,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 11.515625, 8.816406);
cairo_line_to(cr, 10.6875, 14.378906);
cairo_line_to(cr, 12.117188, 18.597656);
cairo_line_to(cr, 13.144531, 18.597656);
cairo_line_to(cr, 13.976562, 13.003906);
cairo_line_to(cr, 12.570312, 8.816406);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
}
 /********************/
if(val&0x0200){
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(r,g,b,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 21.585938, 8.816406);
cairo_line_to(cr, 18.96875, 12.941406);
cairo_line_to(cr, 18.128906, 18.597656);
cairo_line_to(cr, 19.15625, 18.597656);
cairo_line_to(cr, 21.839844, 14.378906);
cairo_line_to(cr, 22.667969, 8.816406);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
}
 /********************/
if(val&0x0100){
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(r,g,b,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 9.648438, 19.597656);
cairo_line_to(cr, 7.289062, 21.972656);
cairo_line_to(cr, 8.941406, 24.347656);
cairo_line_to(cr, 12.527344, 24.347656);
cairo_line_to(cr, 14.566406, 21.972656);
cairo_line_to(cr, 13.234375, 19.597656);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
}
 /********************/
if(val&0x0080){
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(r,g,b,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 21.980469, 38.910156);
cairo_line_to(cr, 23.191406, 37.691406);
cairo_line_to(cr, 23.832031, 33.378906);
cairo_line_to(cr, 23.859375, 33.378906);
cairo_curve_to(cr, 24.3125, 30.324219, 24.730469, 27.519531, 25.164062, 24.597656);
cairo_line_to(cr, 23.6875, 22.472656);
cairo_line_to(cr, 21.082031, 25.097656);
cairo_line_to(cr, 20.5625, 28.597656);
cairo_line_to(cr, 20.160156, 31.285156);
cairo_line_to(cr, 19.542969, 35.441406);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
}
 /********************/
if(val&0x0040){
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(r,g,b,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 17.742188, 19.597656);
cairo_line_to(cr, 15.699219, 21.972656);
cairo_line_to(cr, 17.035156, 24.347656);
cairo_line_to(cr, 20.648438, 24.347656);
cairo_line_to(cr, 23.003906, 21.972656);
cairo_line_to(cr, 21.355469, 19.597656);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
}
 /********************/
if(val&0x0020){
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(r,g,b,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 11.085938, 25.347656);
cairo_line_to(cr, 8.433594, 29.535156);
cairo_line_to(cr, 7.597656, 35.128906);
cairo_line_to(cr, 8.652344, 35.128906);
cairo_line_to(cr, 11.304688, 30.972656);
cairo_line_to(cr, 12.140625, 25.347656);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
}
 /********************/
if(val&0x0010){
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(r,g,b,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 4.609375, 40.878906);
cairo_line_to(cr, 3.738281, 39.628906);
cairo_line_to(cr, 7.214844, 36.128906);
cairo_line_to(cr, 10.824219, 36.128906);
cairo_line_to(cr, 12.304688, 38.253906);
cairo_line_to(cr, 11.914062, 40.878906);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
}
 /********************/
if(val&0x0008){
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(r,g,b,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 12.757812, 40.878906);
cairo_line_to(cr, 13.148438, 38.253906);
cairo_line_to(cr, 15.253906, 36.128906);
cairo_line_to(cr, 18.84375, 36.128906);
cairo_line_to(cr, 21.296875, 39.660156);
cairo_line_to(cr, 20.085938, 40.878906);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
}
 /********************/
if(val&0x0004){
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(r,g,b,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 3.238281, 38.910156);
cairo_line_to(cr, 2.394531, 37.691406);
cairo_line_to(cr, 3.035156, 33.378906);
cairo_line_to(cr, 3.007812, 33.378906);
cairo_curve_to(cr, 3.460938, 30.324219, 3.878906, 27.519531, 4.316406, 24.597656);
cairo_line_to(cr, 6.421875, 22.472656);
cairo_line_to(cr, 8.25, 25.097656);
cairo_line_to(cr, 7.726562, 28.597656);
cairo_line_to(cr, 7.328125, 31.285156);
cairo_line_to(cr, 6.710938, 35.441406);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
}
 /********************/
if(val&0x0002){
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(r,g,b,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 12.863281, 37.316406);
cairo_line_to(cr, 11.496094, 35.347656);
cairo_line_to(cr, 12.007812, 31.910156);
cairo_line_to(cr, 12.40625, 29.222656);
cairo_line_to(cr, 13.019531, 25.097656);
cairo_line_to(cr, 15, 22.785156);
cairo_line_to(cr, 16.316406, 25.097656);
cairo_line_to(cr, 15.695312, 29.285156);
cairo_line_to(cr, 15.304688, 31.910156);
cairo_line_to(cr, 14.789062, 35.378906);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
}
 /********************/
if(val&0x0001){
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(r,g,b,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 17.671875, 35.128906);
cairo_line_to(cr, 16.28125, 31.003906);
cairo_line_to(cr, 17.125, 25.347656);
cairo_line_to(cr, 18.152344, 25.347656);
cairo_line_to(cr, 19.582031, 29.566406);
cairo_line_to(cr, 18.753906, 35.128906);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
}
 /********* dot ***********/
 if(num > 127){
cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
pattern = cairo_pattern_create_rgba(r,g,b,1);
cairo_set_source(cr, pattern);
cairo_pattern_destroy(pattern);
cairo_new_path(cr);
cairo_move_to(cr, 27.921875, 38.828125);
cairo_curve_to(cr, 27.921875, 39.96875, 26.996094, 40.898438, 25.851562, 40.898438);
cairo_curve_to(cr, 24.710938, 40.898438, 23.78125, 39.96875, 23.785156, 38.828125);
cairo_curve_to(cr, 23.78125, 37.683594, 24.710938, 36.757812, 25.851562, 36.757812);
cairo_curve_to(cr, 26.996094, 36.757812, 27.921875, 37.683594, 27.921875, 38.828125);
cairo_close_path(cr);
cairo_set_tolerance(cr, 0.1);
cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
cairo_fill_preserve(cr);
}
 /********************/

blur_image_surface(temp_surface,2);
cairo_set_source_surface(old_cr,temp_surface,0,0);
cairo_paint(old_cr);
cairo_surface_destroy(temp_surface);
cairo_destroy(cr);
}

inline void cairo_code_draw_red16seg_render(cairo_t *cr, char num){cairo_code_draw_16seg_render(cr, num, 0);}
inline void cairo_code_draw_green16seg_render(cairo_t *cr, char num){cairo_code_draw_16seg_render(cr, num, 3);}
inline void cairo_code_draw_blue16seg_render(cairo_t *cr, char num){cairo_code_draw_16seg_render(cr, num, 4);}

inline short char2seg(char c){
/* this function is for converting to a 16 bit value where each bit corresponds to a segment of the LCD character. The LCD sements are indexed from MSB top right, going left then down. The period will be an extra argument. The bits are (0 is LSB, 15 MSB)
 _ _      15    14
|\|/|   13 12 11 10 9
 - -       8     7
|/|\|    6 5  4  3  2
 - - .     1     0
*/
c = c&0x7F;
switch(c){
  case 48://0
    return 0xe557;
  case 49://1
    return 0x0604;
  case 50://2
    return 0xc3c3;
  case 51://3
    return 0xc387;
  case 52://4
    return 0x2384;
  case 53://5
    return 0xe10b;
  case 54://6
    return 0xe1c7;
  case 55://7
    return 0xc204;
  case 56://8
    return 0xe3c7;
  case 57://9
    return 0xe387;
 
  case 65://A
    return 0xe3c4;
  case 66://B
    return 0xcb97;
  case 67://C
    return 0xe043;
  case 68://D
    return 0xcb17;
  case 69://E
    return 0xe1c3;
  case 70://F
    return 0xe1c0;
  case 71://G
    return 0xe0c7;
  case 72://H
    return 0x23c4;
  case 73://I
    return 0xc813;
  case 74://J
    return 0x0247;
  case 75://K
    return 0x0c18;
  case 76://L
    return 0x2043;
  case 77://M
    return 0x3644;
  case 78://N
    return 0x324c;
  case 79://O
    return 0xe247;
  case 80://P
    return 0xe3c0;
  case 81://Q
    return 0xe24f;
  case 82://R
    return 0xe3c8;
  case 83://S
    return 0xe187;
  case 84://T
    return 0xc810;
  case 85://U
    return 0x2247;
  case 86://V
    return 0x120c;
  case 87://W
    return 0x226c;
  case 88://X
    return 0x1428;
  case 89://Y
    return 0x1410;
  case 90://Z
    return 0xc423;

  default:
    return 0;
}
}

#endif
