#ifndef DRAW_16SEG_H
#define DRAW_16SEG_H
#include"blur.h"
inline int cairo_code_draw_16seg_get_width()
{
    return 30;
}
inline int cairo_code_draw_16seg_get_height()
{
    return 45;
}
inline int16_t char2seg(char c);
inline void cairo_code_draw_16seg_render(cairo_t *cr, char num, uint8_t color)
{
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
        r = 1;
        g = 0;
        b = 0;
        rd = .3;
        gd = 0;
        bd = 0;
        break;
    case 3://green
        r = 0;
        g = 1;
        b = 0;
        rd = 0;
        gd = .3333;
        bd = 0;
        break;
    case 4://blue
        r = 0.3;
        g = 0.6;
        b = 1;
        rd = 0;
        gd = 0;
        bd = .2;
        break;
    default://red
        r = 1;
        g = 0;
        b = 0;
        rd = .3333;
        gd = 0;
        bd = 0;
        break;
    }

    uint16_t val = char2seg(num);

    cairo_surface_t *temp_surface;
    cairo_t *old_cr;
    cairo_pattern_t *pattern;
    cairo_matrix_t matrix;


    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_rgba(0.2,0.2,0.2,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 3.753906, 0.761719);
    cairo_line_to(cr, 26.492188, 0.761719);
    cairo_curve_to(cr, 28.148438, 0.761719, 29.492188, 2.101562, 29.492188, 3.757812);
    cairo_line_to(cr, 29.492188, 41.550781);
    cairo_curve_to(cr, 29.492188, 43.207031, 28.148438, 44.550781, 26.492188, 44.550781);
    cairo_line_to(cr, 3.753906, 44.550781);
    cairo_curve_to(cr, 2.097656, 44.550781, 0.757812, 43.207031, 0.757812, 41.550781);
    cairo_line_to(cr, 0.757812, 3.757812);
    cairo_curve_to(cr, 0.757812, 2.101562, 2.097656, 0.761719, 3.753906, 0.761719);
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
    /*cairo_new_path(cr);
    cairo_move_to(cr, 3.753906, 0.761719);
    cairo_line_to(cr, 26.492188, 0.761719);
    cairo_curve_to(cr, 28.148438, 0.761719, 29.492188, 2.101562, 29.492188, 3.757812);
    cairo_line_to(cr, 29.492188, 41.550781);
    cairo_curve_to(cr, 29.492188, 43.207031, 28.148438, 44.550781, 26.492188, 44.550781);
    cairo_line_to(cr, 3.753906, 44.550781);
    cairo_curve_to(cr, 2.097656, 44.550781, 0.757812, 43.207031, 0.757812, 41.550781);
    cairo_line_to(cr, 0.757812, 3.757812);
    cairo_curve_to(cr, 0.757812, 2.101562, 2.097656, 0.761719, 3.753906, 0.761719);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_matrix_init(&matrix, 1,0,0,1,-267,-418.09375);
    cairo_pattern_set_matrix(pattern, &matrix);*/
//cairo_pattern_set_matrix(pattern, &matrix);
    cairo_stroke(cr);
    /********dot************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
//cairo_move_to(cr, 29.773438, 39.507812);//top right corner, lower part of curve
//cairo_curve_to(cr, 29.773438, 40.652344, 28.847656, 41.578125, 27.707031, 41.578125);
//cairo_curve_to(cr, 24.5625, 41.578125, 23.636719, 40.652344, 23.636719, 39.507812);
//cairo_curve_to(cr, 23.636719, 38.367188, 24.5625, 37.441406, 27.707031, 37.441406);
//cairo_curve_to(cr, 28.847656, 37.441406, 29.773438, 38.367188, 29.773438, 39.507812);
    cairo_move_to(cr, 28.667969, 38.480469);
    cairo_curve_to(cr, 28.667969, 40.191406, 27.542969, 41.578125, 26.152344, 41.578125);
    cairo_curve_to(cr, 24.761719, 41.578125, 23.636719, 40.191406, 23.636719, 38.480469);
    cairo_curve_to(cr, 23.636719, 36.773438, 24.761719, 35.386719, 26.152344, 35.386719);
    cairo_curve_to(cr, 27.542969, 35.386719, 28.667969, 36.773438, 28.667969, 38.480469);
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
    cairo_move_to(cr, 18.671875, 3.734375);
    cairo_line_to(cr, 18.234375, 6.359375);
    cairo_line_to(cr, 19.601562, 8.484375);
    cairo_line_to(cr, 23.050781, 8.484375);
    cairo_line_to(cr, 26.503906, 4.953125);
    cairo_line_to(cr, 25.71875, 3.734375);
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
    cairo_move_to(cr, 10.835938, 3.734375);
    cairo_line_to(cr, 9.613281, 4.984375);
    cairo_line_to(cr, 11.871094, 8.484375);
    cairo_line_to(cr, 15.34375, 8.484375);
    cairo_line_to(cr, 17.421875, 6.359375);
    cairo_line_to(cr, 17.859375, 3.734375);
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
    cairo_move_to(cr, 8.910156, 5.703125);
    cairo_line_to(cr, 7.71875, 6.921875);
    cairo_line_to(cr, 5.507812, 20.015625);
    cairo_line_to(cr, 6.878906, 22.140625);
    cairo_line_to(cr, 9.445312, 19.515625);
    cairo_line_to(cr, 10.03125, 16.015625);
    cairo_line_to(cr, 10.476562, 13.328125);
    cairo_line_to(cr, 11.167969, 9.203125);
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
    cairo_move_to(cr, 11.929688, 9.484375);
    cairo_line_to(cr, 11.003906, 15.046875);
    cairo_line_to(cr, 12.421875, 19.765625);
    cairo_line_to(cr, 14.835938, 22.015625);
    cairo_line_to(cr, 14.464844, 14.515625);
    cairo_line_to(cr, 12.945312, 9.484375);
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
    cairo_move_to(cr, 17.671875, 7.296875);
    cairo_line_to(cr, 15.746094, 9.265625);
    cairo_line_to(cr, 14.886719, 14.421875);
    cairo_line_to(cr, 15.246094, 21.671875);
    cairo_line_to(cr, 18.074219, 14.296875);
    cairo_line_to(cr, 18.921875, 9.234375);
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
    cairo_move_to(cr, 21.617188, 9.484375);
    cairo_line_to(cr, 18.425781, 14.484375);
    cairo_line_to(cr, 15.527344, 22.109375);
    cairo_line_to(cr, 18.667969, 19.859375);
    cairo_line_to(cr, 21.726562, 15.046875);
    cairo_line_to(cr, 22.65625, 9.484375);
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
    cairo_move_to(cr, 26.96875, 5.671875);
    cairo_line_to(cr, 23.515625, 9.203125);
    cairo_line_to(cr, 21.796875, 19.484375);
    cairo_line_to(cr, 23.511719, 22.140625);
    cairo_line_to(cr, 25.589844, 20.015625);
    cairo_line_to(cr, 27.773438, 6.921875);
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
    cairo_move_to(cr, 18.855469, 20.265625);
    cairo_line_to(cr, 15.492188, 22.640625);
    cairo_line_to(cr, 18.105469, 25.046875);
    cairo_line_to(cr, 20.3125, 25.046875);
    cairo_line_to(cr, 22.667969, 22.640625);
    cairo_line_to(cr, 21.136719, 20.265625);
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
    cairo_move_to(cr, 15.324219, 23.171875);
    cairo_line_to(cr, 15.710938, 30.734375);
    cairo_line_to(cr, 17.25, 35.796875);
    cairo_line_to(cr, 18.265625, 35.796875);
    cairo_line_to(cr, 19.199219, 30.203125);
    cairo_line_to(cr, 17.765625, 25.421875);
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
    cairo_move_to(cr, 9.878906, 20.265625);
    cairo_line_to(cr, 7.554688, 22.640625);
    cairo_line_to(cr, 9.105469, 25.046875);
    cairo_line_to(cr, 11.363281, 25.046875);
    cairo_line_to(cr, 14.78125, 22.640625);
    cairo_line_to(cr, 12.210938, 20.265625);
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
    cairo_move_to(cr, 6.710938, 23.140625);
    cairo_line_to(cr, 4.632812, 25.265625);
    cairo_line_to(cr, 2.472656, 38.359375);
    cairo_line_to(cr, 3.257812, 39.578125);
    cairo_line_to(cr, 6.679688, 36.078125);
    cairo_line_to(cr, 8.402344, 25.765625);
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
    cairo_move_to(cr, 14.65625, 23.234375);
    cairo_line_to(cr, 11.4375, 25.515625);
    cairo_line_to(cr, 8.476562, 30.171875);
    cairo_line_to(cr, 7.539062, 35.796875);
    cairo_line_to(cr, 8.554688, 35.796875);
    cairo_line_to(cr, 11.789062, 30.703125);
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
    cairo_move_to(cr, 23.34375, 23.140625);
    cairo_line_to(cr, 20.746094, 25.796875);
    cairo_line_to(cr, 19.027344, 36.078125);
    cairo_line_to(cr, 21.304688, 39.609375);
    cairo_line_to(cr, 22.527344, 38.359375);
    cairo_line_to(cr, 24.710938, 25.265625);
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
    cairo_move_to(cr, 14.914062, 23.671875);
    cairo_line_to(cr, 12.117188, 31.015625);
    cairo_line_to(cr, 11.269531, 36.078125);
    cairo_line_to(cr, 12.539062, 38.046875);
    cairo_line_to(cr, 14.433594, 36.109375);
    cairo_line_to(cr, 15.285156, 31.015625);
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
    cairo_move_to(cr, 14.929688, 36.796875);
    cairo_line_to(cr, 12.789062, 38.984375);
    cairo_line_to(cr, 12.355469, 41.578125);
    cairo_line_to(cr, 19.410156, 41.546875);
    cairo_line_to(cr, 20.601562, 40.328125);
    cairo_line_to(cr, 18.324219, 36.796875);
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
    cairo_move_to(cr, 7.144531, 36.796875);
    cairo_line_to(cr, 3.71875, 40.296875);
    cairo_line_to(cr, 4.527344, 41.546875);
    cairo_line_to(cr, 11.542969, 41.578125);
    cairo_line_to(cr, 11.976562, 38.984375);
    cairo_line_to(cr, 10.566406, 36.796875);
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

    /********dot************/
    if(num < 0)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
//cairo_move_to(cr, 29.773438, 39.507812);//top right corner, lower part of curve
//cairo_curve_to(cr, 29.773438, 40.652344, 28.847656, 41.578125, 27.707031, 41.578125);
//cairo_curve_to(cr, 24.5625, 41.578125, 23.636719, 40.652344, 23.636719, 39.507812);
//cairo_curve_to(cr, 23.636719, 38.367188, 24.5625, 37.441406, 27.707031, 37.441406);
//cairo_curve_to(cr, 28.847656, 37.441406, 29.773438, 38.367188, 29.773438, 39.507812);
        cairo_move_to(cr, 28.667969, 38.480469);
        cairo_curve_to(cr, 28.667969, 40.191406, 27.542969, 41.578125, 26.152344, 41.578125);
        cairo_curve_to(cr, 24.761719, 41.578125, 23.636719, 40.191406, 23.636719, 38.480469);
        cairo_curve_to(cr, 23.636719, 36.773438, 24.761719, 35.386719, 26.152344, 35.386719);
        cairo_curve_to(cr, 27.542969, 35.386719, 28.667969, 36.773438, 28.667969, 38.480469);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x4000)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 18.671875, 3.734375);
        cairo_line_to(cr, 18.234375, 6.359375);
        cairo_line_to(cr, 19.601562, 8.484375);
        cairo_line_to(cr, 23.050781, 8.484375);
        cairo_line_to(cr, 26.503906, 4.953125);
        cairo_line_to(cr, 25.71875, 3.734375);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x8000)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 10.835938, 3.734375);
        cairo_line_to(cr, 9.613281, 4.984375);
        cairo_line_to(cr, 11.871094, 8.484375);
        cairo_line_to(cr, 15.34375, 8.484375);
        cairo_line_to(cr, 17.421875, 6.359375);
        cairo_line_to(cr, 17.859375, 3.734375);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x2000)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 8.910156, 5.703125);
        cairo_line_to(cr, 7.71875, 6.921875);
        cairo_line_to(cr, 5.507812, 20.015625);
        cairo_line_to(cr, 6.878906, 22.140625);
        cairo_line_to(cr, 9.445312, 19.515625);
        cairo_line_to(cr, 10.03125, 16.015625);
        cairo_line_to(cr, 10.476562, 13.328125);
        cairo_line_to(cr, 11.167969, 9.203125);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x1000)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 11.929688, 9.484375);
        cairo_line_to(cr, 11.003906, 15.046875);
        cairo_line_to(cr, 12.421875, 19.765625);
        cairo_line_to(cr, 14.835938, 22.015625);
        cairo_line_to(cr, 14.464844, 14.515625);
        cairo_line_to(cr, 12.945312, 9.484375);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0800)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 17.671875, 7.296875);
        cairo_line_to(cr, 15.746094, 9.265625);
        cairo_line_to(cr, 14.886719, 14.421875);
        cairo_line_to(cr, 15.246094, 21.671875);
        cairo_line_to(cr, 18.074219, 14.296875);
        cairo_line_to(cr, 18.921875, 9.234375);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0400)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 21.617188, 9.484375);
        cairo_line_to(cr, 18.425781, 14.484375);
        cairo_line_to(cr, 15.527344, 22.109375);
        cairo_line_to(cr, 18.667969, 19.859375);
        cairo_line_to(cr, 21.726562, 15.046875);
        cairo_line_to(cr, 22.65625, 9.484375);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0200)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 26.96875, 5.671875);
        cairo_line_to(cr, 23.515625, 9.203125);
        cairo_line_to(cr, 21.796875, 19.484375);
        cairo_line_to(cr, 23.511719, 22.140625);
        cairo_line_to(cr, 25.589844, 20.015625);
        cairo_line_to(cr, 27.773438, 6.921875);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0080)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 18.855469, 20.265625);
        cairo_line_to(cr, 15.492188, 22.640625);
        cairo_line_to(cr, 18.105469, 25.046875);
        cairo_line_to(cr, 20.3125, 25.046875);
        cairo_line_to(cr, 22.667969, 22.640625);
        cairo_line_to(cr, 21.136719, 20.265625);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0008)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 15.324219, 23.171875);
        cairo_line_to(cr, 15.710938, 30.734375);
        cairo_line_to(cr, 17.25, 35.796875);
        cairo_line_to(cr, 18.265625, 35.796875);
        cairo_line_to(cr, 19.199219, 30.203125);
        cairo_line_to(cr, 17.765625, 25.421875);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0100)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 9.878906, 20.265625);
        cairo_line_to(cr, 7.554688, 22.640625);
        cairo_line_to(cr, 9.105469, 25.046875);
        cairo_line_to(cr, 11.363281, 25.046875);
        cairo_line_to(cr, 14.78125, 22.640625);
        cairo_line_to(cr, 12.210938, 20.265625);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0040)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 6.710938, 23.140625);
        cairo_line_to(cr, 4.632812, 25.265625);
        cairo_line_to(cr, 2.472656, 38.359375);
        cairo_line_to(cr, 3.257812, 39.578125);
        cairo_line_to(cr, 6.679688, 36.078125);
        cairo_line_to(cr, 8.402344, 25.765625);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0020)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 14.65625, 23.234375);
        cairo_line_to(cr, 11.4375, 25.515625);
        cairo_line_to(cr, 8.476562, 30.171875);
        cairo_line_to(cr, 7.539062, 35.796875);
        cairo_line_to(cr, 8.554688, 35.796875);
        cairo_line_to(cr, 11.789062, 30.703125);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0004)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 23.34375, 23.140625);
        cairo_line_to(cr, 20.746094, 25.796875);
        cairo_line_to(cr, 19.027344, 36.078125);
        cairo_line_to(cr, 21.304688, 39.609375);
        cairo_line_to(cr, 22.527344, 38.359375);
        cairo_line_to(cr, 24.710938, 25.265625);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0010)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 14.914062, 23.671875);
        cairo_line_to(cr, 12.117188, 31.015625);
        cairo_line_to(cr, 11.269531, 36.078125);
        cairo_line_to(cr, 12.539062, 38.046875);
        cairo_line_to(cr, 14.433594, 36.109375);
        cairo_line_to(cr, 15.285156, 31.015625);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0001)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 14.929688, 36.796875);
        cairo_line_to(cr, 12.789062, 38.984375);
        cairo_line_to(cr, 12.355469, 41.578125);
        cairo_line_to(cr, 19.410156, 41.546875);
        cairo_line_to(cr, 20.601562, 40.328125);
        cairo_line_to(cr, 18.324219, 36.796875);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0002)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 7.144531, 36.796875);
        cairo_line_to(cr, 3.71875, 40.296875);
        cairo_line_to(cr, 4.527344, 41.546875);
        cairo_line_to(cr, 11.542969, 41.578125);
        cairo_line_to(cr, 11.976562, 38.984375);
        cairo_line_to(cr, 10.566406, 36.796875);
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

inline void   cairo_code_draw_red16seg_render(cairo_t *cr, char num)
{
    cairo_code_draw_16seg_render(cr, num, 0);
}
inline void cairo_code_draw_green16seg_render(cairo_t *cr, char num)
{
    cairo_code_draw_16seg_render(cr, num, 3);
}
inline void  cairo_code_draw_blue16seg_render(cairo_t *cr, char num)
{
    cairo_code_draw_16seg_render(cr, num, 4);
}

static uint8_t Font5x7[][5]  =
{
    {0x00, 0x00, 0x00, 0x00, 0x00},// (space)
    {0x00, 0x00, 0x5F, 0x00, 0x00},// !
    {0x00, 0x07, 0x00, 0x07, 0x00},// "
    {0x14, 0x7F, 0x14, 0x7F, 0x14},// #
    {0x24, 0x2A, 0x7F, 0x2A, 0x12},// $
    {0x23, 0x13, 0x08, 0x64, 0x62},// %
    {0x36, 0x49, 0x55, 0x22, 0x50},// &
    {0x00, 0x05, 0x03, 0x00, 0x00},// '
    {0x00, 0x1C, 0x22, 0x41, 0x00},// (
    {0x00, 0x41, 0x22, 0x1C, 0x00},// )
    {0x08, 0x2A, 0x1C, 0x2A, 0x08},// *
    {0x08, 0x08, 0x3E, 0x08, 0x08},// +
    {0x00, 0x50, 0x30, 0x00, 0x00},// ,
    {0x08, 0x08, 0x08, 0x08, 0x08},// -
    {0x00, 0x60, 0x60, 0x00, 0x00},// .
    {0x20, 0x10, 0x08, 0x04, 0x02},// /
    {0x3E, 0x51, 0x49, 0x45, 0x3E},// 0
    {0x00, 0x42, 0x7F, 0x40, 0x00},// 1
    {0x42, 0x61, 0x51, 0x49, 0x46},// 2
    {0x21, 0x41, 0x45, 0x4B, 0x31},// 3
    {0x18, 0x14, 0x12, 0x7F, 0x10},// 4
    {0x27, 0x45, 0x45, 0x45, 0x39},// 5
    {0x3C, 0x4A, 0x49, 0x49, 0x30},// 6
    {0x01, 0x71, 0x09, 0x05, 0x03},// 7
    {0x36, 0x49, 0x49, 0x49, 0x36},// 8
    {0x06, 0x49, 0x49, 0x29, 0x1E},// 9
    {0x00, 0x36, 0x36, 0x00, 0x00},// :
    {0x00, 0x56, 0x36, 0x00, 0x00},// ;
    {0x00, 0x08, 0x14, 0x22, 0x41},// <
    {0x14, 0x14, 0x14, 0x14, 0x14},// =
    {0x41, 0x22, 0x14, 0x08, 0x00},// >
    {0x02, 0x01, 0x51, 0x09, 0x06},// ?
    {0x32, 0x49, 0x79, 0x41, 0x3E},// @
    {0x7E, 0x11, 0x11, 0x11, 0x7E},// A
    {0x7F, 0x49, 0x49, 0x49, 0x36},// B
    {0x3E, 0x41, 0x41, 0x41, 0x22},// C
    {0x7F, 0x41, 0x41, 0x22, 0x1C},// D
    {0x7F, 0x49, 0x49, 0x49, 0x41},// E
    {0x7F, 0x09, 0x09, 0x01, 0x01},// F
    {0x3E, 0x41, 0x41, 0x51, 0x32},// G
    {0x7F, 0x08, 0x08, 0x08, 0x7F},// H
    {0x00, 0x41, 0x7F, 0x41, 0x00},// I
    {0x20, 0x40, 0x41, 0x3F, 0x01},// J
    {0x7F, 0x08, 0x14, 0x22, 0x41},// K
    {0x7F, 0x40, 0x40, 0x40, 0x40},// L
    {0x7F, 0x02, 0x04, 0x02, 0x7F},// M
    {0x7F, 0x04, 0x08, 0x10, 0x7F},// N
    {0x3E, 0x41, 0x41, 0x41, 0x3E},// O
    {0x7F, 0x09, 0x09, 0x09, 0x06},// P
    {0x3E, 0x41, 0x51, 0x21, 0x5E},// Q
    {0x7F, 0x09, 0x19, 0x29, 0x46},// R
    {0x46, 0x49, 0x49, 0x49, 0x31},// S
    {0x01, 0x01, 0x7F, 0x01, 0x01},// T
    {0x3F, 0x40, 0x40, 0x40, 0x3F},// U
    {0x1F, 0x20, 0x40, 0x20, 0x1F},// V
    {0x7F, 0x20, 0x18, 0x20, 0x7F},// W
    {0x63, 0x14, 0x08, 0x14, 0x63},// X
    {0x03, 0x04, 0x78, 0x04, 0x03},// Y
    {0x61, 0x51, 0x49, 0x45, 0x43},// Z
    {0x00, 0x00, 0x7F, 0x41, 0x41},// [
    {0x02, 0x04, 0x08, 0x10, 0x20},// "\"
    {0x41, 0x41, 0x7F, 0x00, 0x00},// ]
    {0x04, 0x02, 0x01, 0x02, 0x04},// ^
    {0x40, 0x40, 0x40, 0x40, 0x40},// _
    {0x00, 0x01, 0x02, 0x04, 0x00},// `
    {0x20, 0x54, 0x54, 0x54, 0x78},// a
    {0x7F, 0x48, 0x44, 0x44, 0x38},// b
    {0x38, 0x44, 0x44, 0x44, 0x20},// c
    {0x38, 0x44, 0x44, 0x48, 0x7F},// d
    {0x38, 0x54, 0x54, 0x54, 0x18},// e
    {0x08, 0x7E, 0x09, 0x01, 0x02},// f
    {0x08, 0x14, 0x54, 0x54, 0x3C},// g
    {0x7F, 0x08, 0x04, 0x04, 0x78},// h
    {0x00, 0x44, 0x7D, 0x40, 0x00},// i
    {0x20, 0x40, 0x44, 0x3D, 0x00},// j
    {0x00, 0x7F, 0x10, 0x28, 0x44},// k
    {0x00, 0x41, 0x7F, 0x40, 0x00},// l
    {0x7C, 0x04, 0x18, 0x04, 0x78},// m
    {0x7C, 0x08, 0x04, 0x04, 0x78},// n
    {0x38, 0x44, 0x44, 0x44, 0x38},// o
    {0x7C, 0x14, 0x14, 0x14, 0x08},// p
    {0x08, 0x14, 0x14, 0x18, 0x7C},// q
    {0x7C, 0x08, 0x04, 0x04, 0x08},// r
    {0x48, 0x54, 0x54, 0x54, 0x20},// s
    {0x04, 0x3F, 0x44, 0x40, 0x20},// t
    {0x3C, 0x40, 0x40, 0x20, 0x7C},// u
    {0x1C, 0x20, 0x40, 0x20, 0x1C},// v
    {0x3C, 0x40, 0x30, 0x40, 0x3C},// w
    {0x44, 0x28, 0x10, 0x28, 0x44},// x
    {0x0C, 0x50, 0x50, 0x50, 0x3C},// y
    {0x44, 0x64, 0x54, 0x4C, 0x44},// z
    {0x00, 0x08, 0x36, 0x41, 0x00},// {
    {0x00, 0x00, 0x7F, 0x00, 0x00},// |
    {0x00, 0x41, 0x36, 0x08, 0x00},// }
    {0x08, 0x08, 0x2A, 0x1C, 0x08},// ->
    {0x08, 0x1C, 0x2A, 0x08, 0x08} // <-
};

//light versions require custom widget

inline void cairo_code_draw_16segbg_render(cairo_t *cr, uint8_t color)
{
//r = 0;
//o = 1;
//y = 2;
//g = 3;
//b = 4;
//i = 5;
//v = 6;
    float  rd,gd,bd;//lit and dark colors;
    switch(color)
    {
    case 0://red
        rd = .3;
        gd = 0;
        bd = 0;
        break;
    case 3://green
        rd = 0;
        gd = .3333;
        bd = 0;
        break;
    case 4://blue
        rd = 0;
        gd = 0;
        bd = .2;
        break;
    default://red
        rd = .3333;
        gd = 0;
        bd = 0;
        break;
    }

    cairo_surface_t *temp_surface;
    cairo_t *old_cr;
    cairo_pattern_t *pattern;
    cairo_matrix_t matrix;


    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_rgba(0.2,0.2,0.2,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
    cairo_move_to(cr, 3.753906, 0.761719);
    cairo_line_to(cr, 26.492188, 0.761719);
    cairo_curve_to(cr, 28.148438, 0.761719, 29.492188, 2.101562, 29.492188, 3.757812);
    cairo_line_to(cr, 29.492188, 41.550781);
    cairo_curve_to(cr, 29.492188, 43.207031, 28.148438, 44.550781, 26.492188, 44.550781);
    cairo_line_to(cr, 3.753906, 44.550781);
    cairo_curve_to(cr, 2.097656, 44.550781, 0.757812, 43.207031, 0.757812, 41.550781);
    cairo_line_to(cr, 0.757812, 3.757812);
    cairo_curve_to(cr, 0.757812, 2.101562, 2.097656, 0.761719, 3.753906, 0.761719);
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
    /*
    cairo_new_path(cr);
    cairo_move_to(cr, 3.753906, 0.761719);
    cairo_line_to(cr, 26.492188, 0.761719);
    cairo_curve_to(cr, 28.148438, 0.761719, 29.492188, 2.101562, 29.492188, 3.757812);
    cairo_line_to(cr, 29.492188, 41.550781);
    cairo_curve_to(cr, 29.492188, 43.207031, 28.148438, 44.550781, 26.492188, 44.550781);
    cairo_line_to(cr, 3.753906, 44.550781);
    cairo_curve_to(cr, 2.097656, 44.550781, 0.757812, 43.207031, 0.757812, 41.550781);
    cairo_line_to(cr, 0.757812, 3.757812);
    cairo_curve_to(cr, 0.757812, 2.101562, 2.097656, 0.761719, 3.753906, 0.761719);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    //cairo_matrix_init(&matrix, 1,0,0,1,-267,-418.09375);
    //cairo_pattern_set_matrix(pattern, &matrix);
    */
    cairo_stroke(cr);
    /********dot************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
//cairo_move_to(cr, 29.773438, 39.507812);//top right corner, lower part of curve
//cairo_curve_to(cr, 29.773438, 40.652344, 28.847656, 41.578125, 27.707031, 41.578125);
//cairo_curve_to(cr, 24.5625, 41.578125, 23.636719, 40.652344, 23.636719, 39.507812);
//cairo_curve_to(cr, 23.636719, 38.367188, 24.5625, 37.441406, 27.707031, 37.441406);
//cairo_curve_to(cr, 28.847656, 37.441406, 29.773438, 38.367188, 29.773438, 39.507812);
    cairo_move_to(cr, 28.667969, 38.480469);
    cairo_curve_to(cr, 28.667969, 40.191406, 27.542969, 41.578125, 26.152344, 41.578125);
    cairo_curve_to(cr, 24.761719, 41.578125, 23.636719, 40.191406, 23.636719, 38.480469);
    cairo_curve_to(cr, 23.636719, 36.773438, 24.761719, 35.386719, 26.152344, 35.386719);
    cairo_curve_to(cr, 27.542969, 35.386719, 28.667969, 36.773438, 28.667969, 38.480469);
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
    cairo_move_to(cr, 18.671875, 3.734375);
    cairo_line_to(cr, 18.234375, 6.359375);
    cairo_line_to(cr, 19.601562, 8.484375);
    cairo_line_to(cr, 23.050781, 8.484375);
    cairo_line_to(cr, 26.503906, 4.953125);
    cairo_line_to(cr, 25.71875, 3.734375);
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
    cairo_move_to(cr, 10.835938, 3.734375);
    cairo_line_to(cr, 9.613281, 4.984375);
    cairo_line_to(cr, 11.871094, 8.484375);
    cairo_line_to(cr, 15.34375, 8.484375);
    cairo_line_to(cr, 17.421875, 6.359375);
    cairo_line_to(cr, 17.859375, 3.734375);
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
    cairo_move_to(cr, 8.910156, 5.703125);
    cairo_line_to(cr, 7.71875, 6.921875);
    cairo_line_to(cr, 5.507812, 20.015625);
    cairo_line_to(cr, 6.878906, 22.140625);
    cairo_line_to(cr, 9.445312, 19.515625);
    cairo_line_to(cr, 10.03125, 16.015625);
    cairo_line_to(cr, 10.476562, 13.328125);
    cairo_line_to(cr, 11.167969, 9.203125);
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
    cairo_move_to(cr, 11.929688, 9.484375);
    cairo_line_to(cr, 11.003906, 15.046875);
    cairo_line_to(cr, 12.421875, 19.765625);
    cairo_line_to(cr, 14.835938, 22.015625);
    cairo_line_to(cr, 14.464844, 14.515625);
    cairo_line_to(cr, 12.945312, 9.484375);
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
    cairo_move_to(cr, 17.671875, 7.296875);
    cairo_line_to(cr, 15.746094, 9.265625);
    cairo_line_to(cr, 14.886719, 14.421875);
    cairo_line_to(cr, 15.246094, 21.671875);
    cairo_line_to(cr, 18.074219, 14.296875);
    cairo_line_to(cr, 18.921875, 9.234375);
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
    cairo_move_to(cr, 21.617188, 9.484375);
    cairo_line_to(cr, 18.425781, 14.484375);
    cairo_line_to(cr, 15.527344, 22.109375);
    cairo_line_to(cr, 18.667969, 19.859375);
    cairo_line_to(cr, 21.726562, 15.046875);
    cairo_line_to(cr, 22.65625, 9.484375);
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
    cairo_move_to(cr, 26.96875, 5.671875);
    cairo_line_to(cr, 23.515625, 9.203125);
    cairo_line_to(cr, 21.796875, 19.484375);
    cairo_line_to(cr, 23.511719, 22.140625);
    cairo_line_to(cr, 25.589844, 20.015625);
    cairo_line_to(cr, 27.773438, 6.921875);
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
    cairo_move_to(cr, 18.855469, 20.265625);
    cairo_line_to(cr, 15.492188, 22.640625);
    cairo_line_to(cr, 18.105469, 25.046875);
    cairo_line_to(cr, 20.3125, 25.046875);
    cairo_line_to(cr, 22.667969, 22.640625);
    cairo_line_to(cr, 21.136719, 20.265625);
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
    cairo_move_to(cr, 15.324219, 23.171875);
    cairo_line_to(cr, 15.710938, 30.734375);
    cairo_line_to(cr, 17.25, 35.796875);
    cairo_line_to(cr, 18.265625, 35.796875);
    cairo_line_to(cr, 19.199219, 30.203125);
    cairo_line_to(cr, 17.765625, 25.421875);
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
    cairo_move_to(cr, 9.878906, 20.265625);
    cairo_line_to(cr, 7.554688, 22.640625);
    cairo_line_to(cr, 9.105469, 25.046875);
    cairo_line_to(cr, 11.363281, 25.046875);
    cairo_line_to(cr, 14.78125, 22.640625);
    cairo_line_to(cr, 12.210938, 20.265625);
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
    cairo_move_to(cr, 6.710938, 23.140625);
    cairo_line_to(cr, 4.632812, 25.265625);
    cairo_line_to(cr, 2.472656, 38.359375);
    cairo_line_to(cr, 3.257812, 39.578125);
    cairo_line_to(cr, 6.679688, 36.078125);
    cairo_line_to(cr, 8.402344, 25.765625);
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
    cairo_move_to(cr, 14.65625, 23.234375);
    cairo_line_to(cr, 11.4375, 25.515625);
    cairo_line_to(cr, 8.476562, 30.171875);
    cairo_line_to(cr, 7.539062, 35.796875);
    cairo_line_to(cr, 8.554688, 35.796875);
    cairo_line_to(cr, 11.789062, 30.703125);
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
    cairo_move_to(cr, 23.34375, 23.140625);
    cairo_line_to(cr, 20.746094, 25.796875);
    cairo_line_to(cr, 19.027344, 36.078125);
    cairo_line_to(cr, 21.304688, 39.609375);
    cairo_line_to(cr, 22.527344, 38.359375);
    cairo_line_to(cr, 24.710938, 25.265625);
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
    cairo_move_to(cr, 14.914062, 23.671875);
    cairo_line_to(cr, 12.117188, 31.015625);
    cairo_line_to(cr, 11.269531, 36.078125);
    cairo_line_to(cr, 12.539062, 38.046875);
    cairo_line_to(cr, 14.433594, 36.109375);
    cairo_line_to(cr, 15.285156, 31.015625);
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
    cairo_move_to(cr, 14.929688, 36.796875);
    cairo_line_to(cr, 12.789062, 38.984375);
    cairo_line_to(cr, 12.355469, 41.578125);
    cairo_line_to(cr, 19.410156, 41.546875);
    cairo_line_to(cr, 20.601562, 40.328125);
    cairo_line_to(cr, 18.324219, 36.796875);
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
    cairo_move_to(cr, 7.144531, 36.796875);
    cairo_line_to(cr, 3.71875, 40.296875);
    cairo_line_to(cr, 4.527344, 41.546875);
    cairo_line_to(cr, 11.542969, 41.578125);
    cairo_line_to(cr, 11.976562, 38.984375);
    cairo_line_to(cr, 10.566406, 36.796875);
    cairo_close_path(cr);
    cairo_set_tolerance(cr, 0.1);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
    cairo_fill_preserve(cr);
    /********************/
}

inline void cairo_code_draw_16seglt_render(cairo_t *cr, char num, uint8_t color)
{
    cairo_surface_t *temp_surface;
    cairo_t *old_cr;
    cairo_pattern_t *pattern;
    cairo_matrix_t matrix;

    float r,g,b;//lit and dark colors;
    switch(color)
    {
    case 0://red
        r = 1;
        g = 0;
        b = 0;
        break;
    case 3://green
        r = 0;
        g = 1;
        b = 0;
        break;
    case 4://blue
        r = 0.3;
        g = 0.6;
        b = 1;
        break;
    default://red
        r = 1;
        g = 0;
        b = 0;
        break;
    }

    uint16_t val = char2seg(num);

//blur
    temp_surface = cairo_image_surface_create( CAIRO_FORMAT_ARGB32,30,45);
    old_cr = cr;
    cr = cairo_create(temp_surface);

    /********dot************/
    if(num < 0)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
//cairo_move_to(cr, 29.773438, 39.507812);//top right corner, lower part of curve
//cairo_curve_to(cr, 29.773438, 40.652344, 28.847656, 41.578125, 27.707031, 41.578125);
//cairo_curve_to(cr, 24.5625, 41.578125, 23.636719, 40.652344, 23.636719, 39.507812);
//cairo_curve_to(cr, 23.636719, 38.367188, 24.5625, 37.441406, 27.707031, 37.441406);
//cairo_curve_to(cr, 28.847656, 37.441406, 29.773438, 38.367188, 29.773438, 39.507812);
        cairo_move_to(cr, 28.667969, 38.480469);
        cairo_curve_to(cr, 28.667969, 40.191406, 27.542969, 41.578125, 26.152344, 41.578125);
        cairo_curve_to(cr, 24.761719, 41.578125, 23.636719, 40.191406, 23.636719, 38.480469);
        cairo_curve_to(cr, 23.636719, 36.773438, 24.761719, 35.386719, 26.152344, 35.386719);
        cairo_curve_to(cr, 27.542969, 35.386719, 28.667969, 36.773438, 28.667969, 38.480469);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x4000)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 18.671875, 3.734375);
        cairo_line_to(cr, 18.234375, 6.359375);
        cairo_line_to(cr, 19.601562, 8.484375);
        cairo_line_to(cr, 23.050781, 8.484375);
        cairo_line_to(cr, 26.503906, 4.953125);
        cairo_line_to(cr, 25.71875, 3.734375);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x8000)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 10.835938, 3.734375);
        cairo_line_to(cr, 9.613281, 4.984375);
        cairo_line_to(cr, 11.871094, 8.484375);
        cairo_line_to(cr, 15.34375, 8.484375);
        cairo_line_to(cr, 17.421875, 6.359375);
        cairo_line_to(cr, 17.859375, 3.734375);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x2000)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 8.910156, 5.703125);
        cairo_line_to(cr, 7.71875, 6.921875);
        cairo_line_to(cr, 5.507812, 20.015625);
        cairo_line_to(cr, 6.878906, 22.140625);
        cairo_line_to(cr, 9.445312, 19.515625);
        cairo_line_to(cr, 10.03125, 16.015625);
        cairo_line_to(cr, 10.476562, 13.328125);
        cairo_line_to(cr, 11.167969, 9.203125);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x1000)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 11.929688, 9.484375);
        cairo_line_to(cr, 11.003906, 15.046875);
        cairo_line_to(cr, 12.421875, 19.765625);
        cairo_line_to(cr, 14.835938, 22.015625);
        cairo_line_to(cr, 14.464844, 14.515625);
        cairo_line_to(cr, 12.945312, 9.484375);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0800)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 17.671875, 7.296875);
        cairo_line_to(cr, 15.746094, 9.265625);
        cairo_line_to(cr, 14.886719, 14.421875);
        cairo_line_to(cr, 15.246094, 21.671875);
        cairo_line_to(cr, 18.074219, 14.296875);
        cairo_line_to(cr, 18.921875, 9.234375);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0400)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 21.617188, 9.484375);
        cairo_line_to(cr, 18.425781, 14.484375);
        cairo_line_to(cr, 15.527344, 22.109375);
        cairo_line_to(cr, 18.667969, 19.859375);
        cairo_line_to(cr, 21.726562, 15.046875);
        cairo_line_to(cr, 22.65625, 9.484375);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0200)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 26.96875, 5.671875);
        cairo_line_to(cr, 23.515625, 9.203125);
        cairo_line_to(cr, 21.796875, 19.484375);
        cairo_line_to(cr, 23.511719, 22.140625);
        cairo_line_to(cr, 25.589844, 20.015625);
        cairo_line_to(cr, 27.773438, 6.921875);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0080)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 18.855469, 20.265625);
        cairo_line_to(cr, 15.492188, 22.640625);
        cairo_line_to(cr, 18.105469, 25.046875);
        cairo_line_to(cr, 20.3125, 25.046875);
        cairo_line_to(cr, 22.667969, 22.640625);
        cairo_line_to(cr, 21.136719, 20.265625);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0008)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 15.324219, 23.171875);
        cairo_line_to(cr, 15.710938, 30.734375);
        cairo_line_to(cr, 17.25, 35.796875);
        cairo_line_to(cr, 18.265625, 35.796875);
        cairo_line_to(cr, 19.199219, 30.203125);
        cairo_line_to(cr, 17.765625, 25.421875);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0100)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 9.878906, 20.265625);
        cairo_line_to(cr, 7.554688, 22.640625);
        cairo_line_to(cr, 9.105469, 25.046875);
        cairo_line_to(cr, 11.363281, 25.046875);
        cairo_line_to(cr, 14.78125, 22.640625);
        cairo_line_to(cr, 12.210938, 20.265625);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0040)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 6.710938, 23.140625);
        cairo_line_to(cr, 4.632812, 25.265625);
        cairo_line_to(cr, 2.472656, 38.359375);
        cairo_line_to(cr, 3.257812, 39.578125);
        cairo_line_to(cr, 6.679688, 36.078125);
        cairo_line_to(cr, 8.402344, 25.765625);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0020)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 14.65625, 23.234375);
        cairo_line_to(cr, 11.4375, 25.515625);
        cairo_line_to(cr, 8.476562, 30.171875);
        cairo_line_to(cr, 7.539062, 35.796875);
        cairo_line_to(cr, 8.554688, 35.796875);
        cairo_line_to(cr, 11.789062, 30.703125);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0004)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 23.34375, 23.140625);
        cairo_line_to(cr, 20.746094, 25.796875);
        cairo_line_to(cr, 19.027344, 36.078125);
        cairo_line_to(cr, 21.304688, 39.609375);
        cairo_line_to(cr, 22.527344, 38.359375);
        cairo_line_to(cr, 24.710938, 25.265625);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0010)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 14.914062, 23.671875);
        cairo_line_to(cr, 12.117188, 31.015625);
        cairo_line_to(cr, 11.269531, 36.078125);
        cairo_line_to(cr, 12.539062, 38.046875);
        cairo_line_to(cr, 14.433594, 36.109375);
        cairo_line_to(cr, 15.285156, 31.015625);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0001)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 14.929688, 36.796875);
        cairo_line_to(cr, 12.789062, 38.984375);
        cairo_line_to(cr, 12.355469, 41.578125);
        cairo_line_to(cr, 19.410156, 41.546875);
        cairo_line_to(cr, 20.601562, 40.328125);
        cairo_line_to(cr, 18.324219, 36.796875);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/
    if(val&0x0002)
    {
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        pattern = cairo_pattern_create_rgba(r,g,b,1);
        cairo_set_source(cr, pattern);
        cairo_pattern_destroy(pattern);
        cairo_new_path(cr);
        cairo_move_to(cr, 7.144531, 36.796875);
        cairo_line_to(cr, 3.71875, 40.296875);
        cairo_line_to(cr, 4.527344, 41.546875);
        cairo_line_to(cr, 11.542969, 41.578125);
        cairo_line_to(cr, 11.976562, 38.984375);
        cairo_line_to(cr, 10.566406, 36.796875);
        cairo_close_path(cr);
        cairo_set_tolerance(cr, 0.1);
        cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
        cairo_set_fill_rule(cr, CAIRO_FILL_RULE_WINDING);
        cairo_fill_preserve(cr);
    }
    /********************/

    blur_image_surface(temp_surface,1);
    cairo_set_source_surface(old_cr,temp_surface,0,0);
    cairo_paint(old_cr);
    cairo_surface_destroy(temp_surface);
    cairo_destroy(cr);
}

inline void   cairo_code_draw_red16seg_lightbg_render(cairo_t *cr)
{
    cairo_code_draw_16segbg_render(cr, 0);
}
inline void cairo_code_draw_green16seg_lightbg_render(cairo_t *cr)
{
    cairo_code_draw_16segbg_render(cr, 3);
}
inline void  cairo_code_draw_blue16seg_lightbg_render(cairo_t *cr)
{
    cairo_code_draw_16segbg_render(cr, 4);
}
inline void   cairo_code_draw_red16seg_light_render(cairo_t *cr, char num)
{
    cairo_code_draw_16seglt_render(cr, num, 0);
}
inline void cairo_code_draw_green16seg_light_render(cairo_t *cr, char num)
{
    cairo_code_draw_16seglt_render(cr, num, 3);
}
inline void  cairo_code_draw_blue16seg_light_render(cairo_t *cr, char num)
{
    cairo_code_draw_16seglt_render(cr, num, 4);
}
#endif
