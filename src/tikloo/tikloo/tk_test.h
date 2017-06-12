//spencer jackson //tikloo toolkit

//tk_test.h a header for testing only, it exposes all the guts you shouldn't need to worry about, but I won't get upset if you include this either
//every function in tk_main should either appear here or in tk.h

void tk_draw(tk_t tk,uint16_t n);
void tk_redraw(tk_t tk);
void tk_draweverything(tk_t tk);
uint16_t tk_dumbsearch(tk_t tk, const PuglEvent* event);
static void tk_callback (PuglView* view, const PuglEvent* event);
void tk_rmdupptr(void** a);

//WIDGET STUFF
void tk_nocallback(tk_t tk, const PuglEvent* e, uint16_t n);
void tk_dialcallback(tk_t tk, const PuglEvent* event, uint16_t n);
void tk_buttoncallback(tk_t tk, const PuglEvent* event, uint16_t n);
void tk_showtipcallback(tk_t tk, const PuglEvent* e, uint16_t n);
uint8_t tk_textlayout(cairo_t* cr, tk_text_table* tkt, uint16_t n, uint16_t *w, uint16_t *h, uint8_t wrap);
