//spencer jackson
//tikloo toolkit

//tk_types.h

//this header describes the main type and what is available within the struct as well as supporting types
//go to the bottom of the file for the primary table

#ifndef TK_TYPES_H
#define TK_TYPES_H
#include<stdint.h>
#include<stdbool.h>
#include<cairo/cairo.h>
#include<cairo/cairo-ft.h>
#include<ft2build.h> 
#include FT_FREETYPE_H
#include<harfbuzz/hb.h>
#include"pugl/pugl.h"
#include"timer.h"

//text things
typedef struct tk_font_stuff
{
    uint16_t fontsize;
    uint16_t base;//distance to font baseline

    FT_Library library;
    FT_Face face;
    hb_buffer_t *buf;
    hb_font_t *hbfont;
}tk_font_stuff;

typedef struct tk_text_table
{
    ////// main text table
    char** str;//pointer to text
    bool* strchange;//flag that string has changed
    uint16_t* memlen;//allocated size of str (if 0 then == streln(str));
    uint16_t* n;//item in main table
    uint16_t* cursor;//cursor location in string
    uint16_t* select;//selection length
    uint16_t* ln;//viewport line
    uint16_t* col;//veiwport column
    uint16_t* brklen;//length of brk array
    uint16_t** brk;//linebreak/wrap indices shows first glyph in new line

    tk_font_stuff** tkf;//font for each text element (some may be shared)
    cairo_glyph_t** glyphs;//glyph array
    float** glyph_pos;//array of x positions of glyphs
    uint16_t** cluster_map;
    uint16_t* glyph_count;//number of glyphs in string
    uint16_t* glyph_end;//number of glyphs to draw

    ////// text global
    float scale;//factor text is scaled
    uint8_t cursorstate;//
    uint16_t cursortimer;//index in timer array of cursor timer
    uint16_t nitems,tablesize;//table stats
    uint16_t dff;//default font index
}tk_text_table;

typedef struct
{
    tk_text_table* tkt;
    uint16_t n;//index in text table
}tk_text_stuff;

// dial
typedef struct
{
    float min, max;
    float x0, y0, v0;//drag initiation point
    char* units;
}tk_dial_stuff;

typedef struct
{
    cairo_t **cr;
    cairo_surface_t **surf; 
}tk_draw_stuff;

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
    TK_TEXT_CENTER = 0x4,
    TK_TEXT_VERTICAL = 0x08,
    
}TK_PROPERTIES;

// other magic numbers or bitmasks
typedef enum
{
    TK_CURSOR_STATE = 0x1,
    TK_CURSOR_CHANGED = 0x2,
    TK_CURSOR_MOVED = 0x4
}TK_BITMASKS;

typedef struct tk_table
{
    //////primary table, each index correlates across arrays
    //size and position
    float *x,*y,*w,*h;
    //items on higher layers recieve callbacks, layer 0 is not drawn
    uint8_t *layer;
    //value could be any type so be careful here
    void **value;
    //these allow shaders to cache cairo data
    void **drawstuff; 
    //a string pointer for tooltips
    char **tip;
    //property flags
    uint16_t *props;
    //draw function
    void (**draw_f)(cairo_t*, float, float, void*, void*); //surface, w, h, cache, value
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
    uint8_t lmax;//highest layer
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
