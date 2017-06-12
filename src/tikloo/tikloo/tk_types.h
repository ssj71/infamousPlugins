//spencer jackson
//tikloo toolkit

//tk_types.h

//this header describes the main type and what is available within the struct as well as supporting types
//go to the bottom of the file for the primary table

#ifndef TK_TYPES_H
#define TK_TYPES_H
#include<stdint.h>
#include<cairo/cairo.h>
#include<cairo/cairo-ft.h>
#include<ft2build.h> 
#include FT_FREETYPE_H
#include "pugl/pugl.h"
#include "timer.h"

//text stuff
typedef struct
{
    uint16_t fontsize;
    uint16_t base;//distance distance to font baseline

    FT_Library library;
    FT_Face face;
    cairo_font_face_t* fontface;
    cairo_scaled_font_t* scaledfont;
}tk_font_stuff;

typedef struct tk_text_table
{
    ////// main text table
    char** str;//pointer to text
    uint8_t* strchange;
    uint16_t* n;//item in main table
    uint16_t* cursor;//cursor location in string
    uint16_t* select;//selection length
    uint16_t* ln;//viewport line
    uint16_t* col;//veiwport column
    uint16_t* brklen;
    uint16_t** brk;//linebreak/wrap indices

    tk_font_stuff** tkf;
    cairo_glyph_t** glyphs;
    cairo_text_cluster_t** clusters;
    cairo_text_extents_t** extents;
    uint16_t* glyph_count;
    uint16_t* cluster_count;
    uint16_t* extents_count;//length of extents array

    ////// text global
    float scale;
    uint8_t cursorstate;
    uint16_t nitems,tablesize;
    uint16_t dff;//default font
}tk_text_table;

typedef struct
{
    tk_text_table* tkt;
    uint16_t n;//index
}tk_text_stuff;

// dial
typedef struct
{
    float min, max;
    float x0, y0, v0;//drag initiation point
    char* units;
}tk_dial_stuff;


// main properties and table
typedef enum
{
    //NOTE that some of these values are not unique, because the properties only apply in certain contexts. Pay attention 
    //Main Window Properties
    TK_HOLD_RATIO = 0x1,
    
    //Any Item Properties
    TK_NO_DAMAGE = 0x1,//if the item is redrawn, it doesn't affect items behind it

    //Button Properties
    TK_BUTTON_MOMENTARY = 0x2,

    //Dial Properties
    TK_VALUE_PARABOLIC = 0x2,//TODO: what about for xy points?

    //Text Properties
    TK_TEXT_WRAP = 0x2,
    
}TK_PROPERTIES;

typedef struct tk_table
{
    //////primary table, each index correlates across arrays
    //size and position
    float *x,*y,*w,*h;
    //items on higher layers recieve callbacks, layer 0 is not drawn
    uint8_t *layer;
    //value could be any type so be careful here
    void **value;
    //a string pointer for tooltips
    char **tip;
    //property flags
    uint16_t *props;
    //draw function
    void (**draw_f)(cairo_t*, float, float, void*); //surface, w, h, value
    //built in callback, must not be 0
    void (**cb_f)(struct tk_table*, const PuglEvent*, uint16_t); 
    //user callback, runs after the cb_f
    void (**callback_f)(struct tk_table*, const PuglEvent*, uint16_t);
    //item specific data of any type, take care
    void **extras;
    //opaque data set by user
    void **user;

    //////there is also a text specific table
    tk_text_table tkt;

    //////lists, values are indices of items with common properties
    uint16_t *hold_ratio; //items that don't change aspect ratio when scaling
    uint16_t *draw; //full list of items that are drawn
    uint16_t *redraw; //list of items that have changed and need redraw
    uint16_t *timer; //list of active timers

    //////global stuff
    float w0,h0;
    uint16_t nitems,tablesize;
    uint16_t drag;//index of item being dragged
    uint16_t focus;//index of item last clicked (focused)
    uint16_t ttip,tover;//index of tooltip widget, and current tip

    timer_lib_handle_t tlibh;
    PuglView* view;
    cairo_t* cr;
    uint8_t quit; 
}tk_table;

typedef tk_table* tk_t;
#endif
