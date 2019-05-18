//spencer jackson
//tikloo toolkit

//tk.h - the public interface for the tikloo toolkit
#ifndef TK_H
#define TK_H
#include"tk_types.h"


//functions that return some kind of struct
tk_t tk_gimmeaTiKloo( uint16_t w, uint16_t h, char* title, intptr_t parentWindow);
tk_font_stuff* tk_gimmeaFont(tk_t tk, const uint8_t* font, uint32_t fsize, uint32_t findex, uint16_t h);

//functions that add widgets to the table
uint16_t tk_addaWidget(tk_t tk, uint16_t x, uint16_t y, uint16_t w, uint16_t h); 
uint16_t tk_addaDial(tk_t tk, uint16_t x, uint16_t y, uint16_t w, uint16_t h, float min, float max, float val);
uint16_t tk_addaButton(tk_t tk, uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool val);
uint16_t tk_addaTimer(tk_t tk, float s);
uint16_t tk_addaText(tk_t tk, uint16_t x, uint16_t y, uint16_t w, uint16_t h, tk_font_stuff* font, const char* str);
uint16_t tk_addaTextEntry(tk_t tk, uint16_t x, uint16_t y, uint16_t w, uint16_t h, tk_font_stuff* font, const char* str);
uint16_t tk_addaTooltip(tk_t tk, tk_font_stuff* font);
uint16_t tk_addaTextButton(tk_t tk, uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool val, const char* str);
uint16_t tk_addaInputDialog(tk_t tk, tk_font_stuff* font);

//core functions
void tk_rollit(tk_t tk);
intptr_t tk_embedit(tk_t tk);
void tk_idle(tk_t tk);
void tk_cleanup(tk_t tk);

//various helping functions
void tk_hide(tk_t tk, uint16_t n, bool damage);
void tk_changelayer(tk_t tk, uint16_t n, uint16_t layer);
void tk_optimizedefaultdraw(tk_t tk);

void tk_addtogrowlist(uint16_t** list, uint16_t *len, uint16_t n);
void tk_addtolist(uint16_t* list, uint16_t n);
void tk_removefromlist(uint16_t* list, uint16_t n);
void tk_insertinlist(uint16_t* list, uint16_t i, uint16_t n);
void tk_setstring(char** str, const char* msg, uint16_t *memlen);
void tk_settimer(tk_t tk, uint16_t n, float s);
float tk_getdial(tk_t tk, uint16_t n);
void tk_setdial(tk_t tk, uint16_t n, float v);
void tk_settext(tk_t tk, uint16_t n, const char* str);
void tk_gettextcursor(void* valp, int *x, int *y, int *w, int *h);

void tk_showinputdialog(tk_t tk, uint16_t n, const char* prompt_str, const char* def_input, void (*cb_f)(tk_t tk, char* str, void* data), void* data);
#endif
