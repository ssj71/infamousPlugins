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
    cairo_stroke(cr);
    /********dot************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
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

inline int16_t char2seg(char c)
{
    /* this function is for converting to a 16 bit value where each bit corresponds to a segment of the LCD character. The LCD sements are indexed from MSB top right, going left then down. The period will be an extra argument. The bits are (0 is LSB, 15 MSB)
     _ _      15    14
    |\|/|   13 12 11 10 9
     - -       8     7
    |/|\|    6 5  4  3  2
     - - .     1     0
    */
    c = c&0x7F;
    switch(c)
    {
    case 45://-
        return 0x0180;
    case 48://0
        return 0xe667;
    case 49://1
        return 0x0604;
    case 50://2
        return 0xc3c3;
    case 51://3
        return 0xc387;
    case 52://4
        return 0x2384;
    case 53://5
        return 0xd087;//0xe10b
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
        return 0xca97;
    case 67://C
        return 0xe043;
    case 68://D
        return 0xca17;
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
        return 0x25c4;
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
        return 0x2460;
    case 87://W
        return 0x226c;
    case 88://X
        return 0x1428;
    case 89://Y
        return 0x1410;
    case 90://Z
        return 0xc423;

    case 97://a
        return 0x4295;
    case 98://b
        return 0x0895;
    case 99://c
        return 0x0091;
    case 100://d
        return 0x0295;
    case 101://e
        return 0x4a91;
    case 102://f
        return 0x0590;
    case 103://g
        return 0x4a85;
    case 104://h
        return 0x0894;
    case 105://i
        return 0x0010;
    case 106://j
        return 0x0215;
    case 107://k
        return 0x0c94;
    case 108://l
        return 0x0204;
    case 109://m
        return 0x01d4;
    case 110://n
        return 0x0094;
    case 111://o
        return 0x0095;
    case 112://p
        return 0x4a90;
    case 113://q
        return 0xa911;
    case 114://r
        return 0x0090;
    case 115://s
        return 0x0485;
    case 116://t
        return 0x1190;
    case 117://u
        return 0x0015;
    case 118://v
        return 0x000c;
    case 119://w
        return 0x006c;
    case 120://x
        return 0x1428;
    case 121://y
        return 0x1420;
    case 122://z
        return 0xc423;
    default:
        return 0;
    }
}

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

    cairo_pattern_t *pattern;


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
    cairo_stroke(cr);
    /********dot************/
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
    pattern = cairo_pattern_create_rgba(rd,gd,bd,1);
    cairo_set_source(cr, pattern);
    cairo_pattern_destroy(pattern);
    cairo_new_path(cr);
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
