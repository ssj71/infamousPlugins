//spencer jackson //tikloo toolkit

//tk_main.c

//this is approximately based on priciples of data-oriented design, but I'm not really shooting for the performance benefits of DOD. The goal is that it will have the coding benefits: powerful, flexible, simple to extend/tweak, and fewer LOC.

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<harfbuzz/hb-ft.h>
#include"tk.h"
#include"tk_default_draw.h"
#include"tk_test.h"
#include"fonts/LibraSerifModern_Regular.h"
#include"csleep.h"
#include"timer.h"


#ifndef TK_TOOLTIP_TIME
#define TK_TOOLTIP_TIME 1
#endif
#ifndef TK_STARTER_SIZE
#define TK_STARTER_SIZE 64
#endif
#ifndef TK_TEXT_STARTER_SIZE
#define TK_TEXT_STARTER_SIZE 16
#endif

//forward declarations are all in tk_test or tk.h
//static void tk_callback (PuglView* view, const PuglEvent* event);
//void tk_nocallback(tk_t tk, const PuglEvent* e, uint16_t n);

////// Table of Contents:
// Core_Functions
// Sundry_Helper_Functions
// General_Widget_Stuff
// Dial_Stuff
// Button_Stuff
// Timer_Stuff
// General_Text_Stuff
// Text_Entry_Stuff
// Tooltip_Stuff
// Text_Button_Stuff
// Input_Dialog_Stuff


// Core_Functions
tk_t tk_gimmeaTiKloo(uint16_t w, uint16_t h, char* title, intptr_t parentWindow)
{
    tk_t tk = (tk_t)malloc(sizeof(tk_table));

    tk->tablesize = 0;
    tk_growprimarytable(tk);

    //init the text table to len 0
    tk->tkt.str = 0;
    tk->tkt.strchange = false;
    tk->tkt.memlen = 0;
    tk->tkt.n = 0;
    tk->tkt.cursor = 0;
    tk->tkt.select = 0;
    tk->tkt.ln = 0;
    tk->tkt.col = 0;
    tk->tkt.brklen = 0;
    tk->tkt.brk = 0;
    tk->tkt.scale = 0;

    tk->tkt.tkf = 0;
    tk->tkt.glyphs = 0;
    tk->tkt.glyph_pos = 0;
    tk->tkt.glyph_count = 0;
    tk->tkt.cluster_map = 0;

    tk->tkt.cursorstate = 0;
    tk->tkt.cursortimer = 0;
    tk->tkt.nitems = 0;
    tk->tkt.tablesize = 0;

    tk->timer = 0;//this list only gets initialized if there are timers

    tk->tkt.nitems = 0;
    tk->tkt.tablesize = 0;

    //now initialize the main window widget
    tk->w[0] = w;
    tk->h[0] = h;
    tk->w0 = w;
    tk->h0 = h;

    tk->layer[0] = 1;
//    tk->draw[0] = 0;
//    tk->draw[1] = 0;
//    tk->redraw[0] = 0;
//    tk->redraw[1] = 0;
    tk_setstring(&tk->tip[0],title,0);

    tk->cb_f[0] = tk_nocallback;
    tk->draw_f[0] = tk_drawbg;

    tk->lmax = 2;//assume BG and widgets are only current layers
    tk->drag = 0;
    tk->nitems = 1;
    tk->tablesize = TK_STARTER_SIZE;
    tk->ttip = 0;
    tk->quit = 0;

    //start timer stuff
    timer_lib_initialize(&tk->tlibh);

    //start the pugl stuff 
    PuglView* view = puglInit(NULL, NULL);
    //puglInitWindowClass(view, tk->tip[0]);
    puglInitWindowSize(view, tk->w[0], tk->h[0]);
    //puglInitWindowMinSize(view, 256, 256);
    puglInitResizable(view, 1);
    
    puglIgnoreKeyRepeat(view, 0);
    puglSetEventFunc(view, tk_callback);
    puglSetHandle(view, tk);
    puglInitContextType(view, PUGL_CAIRO);//PUGL_CAIRO_GL
    if(parentWindow)puglInitWindowParent(view,(PuglNativeWindow)parentWindow);
    tk->view = view; 
    
    //all set!
    puglCreateWindow(view, tk->tip[0]); 
    tk->cr = (cairo_t*)puglGetContext(tk->view);
    
    return (tk_t) tk;
} 

//for standalone apps
void tk_rollit(tk_t tk)
{ 
    PuglView* view = tk->view;

    puglShowWindow(view);
    tk_draweverything(tk);

    if(tk->timer)
    {
        while (!tk->quit)
        {
            csleep(1);// these are crappy timers jsyk, we sleep for 1ms in between
            puglProcessEvents(view);
            tk_checktimers(tk);
            tk_redraw(tk);
        }
    }
    else
        while (!tk->quit)
        {
            //no timers
            puglWaitForEvent(view);
            puglProcessEvents(view);
            tk_redraw(tk);
        } 
}

//for plugins, returns window ID
intptr_t tk_embedit(tk_t tk)
{
    puglShowWindow(tk->view);
    tk_draweverything(tk);
    return puglGetNativeWindow(tk->view);
}

void tk_idle(tk_t tk)
{
    puglProcessEvents(tk->view); 
    tk_checktimers(tk);
    tk_redraw(tk);
}

void tk_cleanup(tk_t tk)
{
    uint16_t i,n;
    timer_lib_shutdown(tk->tlibh);

    //deal with text table 
    //free text double arrays 
    n = ((tk_text_stuff*)(tk->value[tk->ttip-1]))->n;
    for(i=0;tk->tkt.glyphs[i];i++)
        if(tk->tkt.str[i] && !(tk->ttip && i ==n))//must skip tooltip because its pointing to somebody else's string
            free(tk->tkt.str[i]);
    free(tk->tkt.str);
    n = i;
    tk_rmdupptr((void**)(tk->tkt.tkf));
    for(i=0;i<n;i++)
    {
        if(tk->tkt.brk[i])
            free(tk->tkt.brk[i]);
        if(tk->tkt.tkf[i])
            free(tk->tkt.tkf[i]);
        if(tk->tkt.glyphs[i])
            cairo_glyph_free(tk->tkt.glyphs[i]);
        if(tk->tkt.glyph_pos[i])
            free(tk->tkt.glyph_pos[i]);
        if(tk->tkt.cluster_map[i])
            free(tk->tkt.cluster_map[i]);
    }
    free(tk->tkt.brk);
    free(tk->tkt.tkf);
    free(tk->tkt.glyph_pos);
    free(tk->tkt.glyphs);
    free(tk->tkt.cluster_map);

    free(tk->tkt.strchange); free(tk->tkt.memlen); free(tk->tkt.n); 
    free(tk->tkt.cursor); free(tk->tkt.select);
    free(tk->tkt.ln); free(tk->tkt.col); free(tk->tkt.brklen);
    free(tk->tkt.glyph_count);
    free(tk->tkt.glyph_end);

    //now the main table
    //free double arrays
    for(i=0;tk->cb_f[i];i++)
        if(tk->value[i])
            free(tk->value[i]);
    for(i=0;tk->cb_f[i];i++)
        if(tk->tip[i])
            free(tk->tip[i]);
    for(i=0;tk->cb_f[i];i++)
        if(tk->extras[i])
            free(tk->extras[i]);
    tk_rmdupptr((void**)(tk->drawstuff));
    for(i=0;tk->cb_f[i];i++)
        if(tk->drawstuff[i])
            free(tk->drawstuff[i]);
    //we let the user free anything in user data 

    if(tk->timer) free(tk->timer);
    free(tk->x); free(tk->y); free(tk->w); free(tk->h);
    free(tk->layer); free(tk->value); free(tk->drawstuff);//TODO: pass drawstuff to draw function with everything else null to free
    free(tk->tip);
    free(tk->props); free(tk->extras); free(tk->user);
    free(tk->hold_ratio); free(tk->draw); free(tk->redraw);
    free(tk->draw_f); free(tk->cb_f); free(tk->callback_f);
    puglDestroy(tk->view);
    free(tk);
}

void tk_growprimarytable(tk_t tk)
{
    uint8_t osz,sz = TK_STARTER_SIZE;
    tk_table tmpt;
    if(tk->tablesize)
        sz = tk->tablesize*2;
    //initialize the table in the struct
    tmpt.x = (float*)calloc(sz,sizeof(float));
    tmpt.y = (float*)calloc(sz,sizeof(float));
    tmpt.w = (float*)calloc(sz,sizeof(float));
    tmpt.h = (float*)calloc(sz,sizeof(float));

    tmpt.layer =   (uint8_t*)calloc(sz+1,sizeof(uint8_t)); 
    tmpt.value =     (void**)calloc(sz,sizeof(void*)); 
    tmpt.tip =       (char**)calloc(sz,sizeof(char*));
    tmpt.props =  (uint16_t*)calloc(sz,sizeof(uint16_t));
    tmpt.extras =    (void**)calloc(sz,sizeof(void*));
    tmpt.user =      (void**)calloc(sz,sizeof(void*));
    tmpt.drawstuff = (void**)calloc(sz,sizeof(void*)); 

    //init the lists
    //lists always keep an extra 0 at the end so the end can be found even if full
    tmpt.hold_ratio = (uint16_t*)calloc(sz+1,sizeof(float));
    tmpt.draw =       (uint16_t*)calloc(sz+1,sizeof(float));
    tmpt.redraw =     (uint16_t*)calloc(sz+1,sizeof(float));

    tmpt.draw_f = (void(**)(cairo_t*,float,float,void*,void*))calloc(sz,sizeof(&tk_drawnothing));
    tmpt.cb_f = (void(**)(tk_t,const PuglEvent*,uint16_t))calloc(sz,sizeof(&tk_callback));
    tmpt.callback_f = (void(**)(tk_t,const PuglEvent*,uint16_t))calloc(sz,sizeof(&tk_callback));

    if(tk->tablesize)
    {
        osz = tk->tablesize;
        memcpy(tmpt.x,      tk->x,      osz*sizeof(float));
        memcpy(tmpt.y,      tk->y,      osz*sizeof(float));
        memcpy(tmpt.w,      tk->w,      osz*sizeof(float));
        memcpy(tmpt.h,      tk->h,      osz*sizeof(float));
        memcpy(tmpt.layer,  tk->layer,  osz*sizeof(uint8_t));
        memcpy(tmpt.value,  tk->value,  osz*sizeof(void*));
        memcpy(tmpt.tip,    tk->tip,    osz*sizeof(char*));
        memcpy(tmpt.props,  tk->props,  osz*sizeof(uint16_t));
        memcpy(tmpt.extras, tk->extras, osz*sizeof(void*));
        memcpy(tmpt.user,   tk->user,   osz*sizeof(void*));
        memcpy(tmpt.drawstuff, tk->drawstuff,osz*sizeof(void*));
        
        memcpy(tmpt.hold_ratio,tk->hold_ratio,osz*sizeof(uint16_t)+1);
        memcpy(tmpt.draw,      tk->draw,      osz*sizeof(uint16_t)+1);
        memcpy(tmpt.redraw,    tk->redraw,    osz*sizeof(uint16_t)+1);

        memcpy(tmpt.draw_f,    tk->draw_f,    osz*sizeof(void(*)(cairo_t*,float,float,void*,void*)));
        memcpy(tmpt.cb_f,      tk->cb_f,      osz*sizeof(void(*)(tk_t,PuglEvent*,uint16_t)));
        memcpy(tmpt.callback_f,tk->callback_f,osz*sizeof(void(*)(tk_t,PuglEvent*,uint16_t)));
    }

    tk->x =      tmpt.x;
    tk->y =      tmpt.y;
    tk->w =      tmpt.w;
    tk->h =      tmpt.h;
    tk->layer =  tmpt.layer;
    tk->value =  tmpt.value;
    tk->tip =    tmpt.tip;
    tk->props =  tmpt.props;
    tk->extras = tmpt.extras;
    tk->user =   tmpt.user;
    tk->drawstuff = tmpt.drawstuff;

    tk->hold_ratio = tmpt.hold_ratio;
    tk->draw =       tmpt.draw;
    tk->redraw =     tmpt.redraw; 
    tk->draw_f =     tmpt.draw_f;
    tk->cb_f =       tmpt.cb_f;
    tk->callback_f = tmpt.callback_f;
}

void tk_resizeeverything(tk_t tk,float w, float h)
{
    uint16_t i,n,tw,th;
    float sx,sy, dx,dy;

    const float x0 = tk->x[0];
    const float y0 = tk->y[0];
    sx = w/(tk->w[0]);//scale change (relative)
    sy = h/(tk->h[0]);
    const float sx0 = (tk->w[0]+2*x0)/tk->w0;//old scaling (absolute)
    const float sy0 = (tk->h[0]+2*y0)/tk->h0;
    const float sx1 = w/tk->w0;//new scaling (absolute)
    const float sy1 = h/tk->h0;
    const float sm0 = sx0<sy0?sx0:sy0;//old small dim
    const float sm1 = sx1<sy1?sx1:sy1;//new small dim
    const float smx = (sm1/sm0)/sx;//min scale factor div. scale x
    const float smy = (sm1/sm0)/sy;

    if(tk->props[0]&TK_HOLD_RATIO)
    {
        if(sx<sy) sy = sx;
        else sx = sy;
        dx = tk->w0*(sx1-sm1)/2;//new window shift
        dy = tk->h0*(sy1-sm1)/2;
        tk->w[0] *= sx;
        tk->h[0] *= sy; 
    }
    else
    {
        dx = (1-smx)/2;//offset factor for individual items
        dy = (1-smy)/2;
        tk->w[0] = w;
        tk->h[0] = h;
        //prescale ones that hold ratio
        for(i=0;tk->hold_ratio[i];i++)
        {
            n = tk->hold_ratio[i];

            tk->x[n] += tk->w[n]*dx;//remove old offset, add new
            tk->y[n] += tk->h[n]*dy;
            tk->w[n] *= smx;
            tk->h[n] *= smy;
        }
        dx = 0;//window shift is actually 0
        dy = 0;
    } 

    //scale items
    n = tk->nitems;
    for(i=1;i<n;i++)
    {
        tk->x[i] -= x0; //remove old shift
        tk->x[i] *= sx;
        tk->x[i] += dx; //add new shift
    } 
    for(i=1;i<n;i++)
    {
        tk->y[i] -= y0;
        tk->y[i] *= sy;
        tk->y[i] += dy;
    } 
    for(i=1;i<n;i++)
        tk->w[i] *= sx;
    for(i=1;i<n;i++)
        tk->h[i] *= sy;

    //update window shift
    tk->x[0] = dx;
    tk->y[0] = dy;

    //scale text
    tk->tkt.scale = sm1;
    for(i=0;i<tk->tkt.nitems;i++)
    {
        n = tk->tkt.n[i];
        tw = tk->w[n];
        th = tk->h[n];
        //TODO: unless they've changed ratio they don't actually need a re-layout
        //TODO: do anything if it doesn't fit?
        tk_textlayout(tk->cr,&tk->tkt,i,&tw,&th,tk->props[n]);
    }
}

void tk_draw(tk_t tk,uint16_t n)
{
    cairo_translate(tk->cr,tk->x[n],tk->y[n]);
    tk->draw_f[n](tk->cr,tk->w[n],tk->h[n],tk->drawstuff[n],tk->value[n]); 
    cairo_translate(tk->cr,-tk->x[n],-tk->y[n]);
}

void tk_redraw(tk_t tk)
{
    uint16_t i,n;
    if( !tk->redraw[0] )
        return;//empty list
    for(i=0; tk->redraw[i]; i++)
    {
        if(tk->layer[tk->redraw[i]])
        {//only draw if on a visible layer
            n = tk->redraw[i];
            if(!tk->props[n]&TK_NO_DAMAGE || tk->layer[n]<tk->lmax)
                tk_damage(tk,n);
            else
                tk_draw(tk,n);
        }
        tk->redraw[i] = 0;
        //TODO: cache everything to avoid redraws?
    }
    tk->tkt.cursorstate &= TK_CURSOR_STATE;//clear changed flags
} 
void tk_draweverything(tk_t tk)
{
    uint16_t i;
    tk_draw(tk,0);//always draw bg
    for(i=0; tk->draw[i]; i++)
    {
        tk_draw(tk,tk->draw[i]);
        //TODO: cache everything to avoid redraws?
    }
}
void tk_damagebox(tk_t tk, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    uint16_t i,l;
    uint16_t x2,y2;
    if(!x)x++;
    if(!y)y++;
    x2 = x--+w+1;
    y2 = y--+h+1;

    //set up clip area
    cairo_save(tk->cr);
    cairo_new_path(tk->cr);
    cairo_move_to(tk->cr, x,y);
    cairo_line_to(tk->cr, x2, y);
    cairo_line_to(tk->cr, x2, y2);
    cairo_line_to(tk->cr, x, y2);
    cairo_close_path(tk->cr);
    cairo_clip_preserve(tk->cr);
        
    for(l=1;l<=tk->lmax;l++)
        for(i=0; tk->cb_f[i]; i++)
            if( tk->layer[i] == l &&
                tk->x[i] < x2 && tk->x[i] + tk->w[i] > x &&
                tk->y[i] < y2 && tk->y[i] + tk->h[i] > y
              )
                tk_draw(tk,i);

    cairo_restore(tk->cr);
}
void tk_damage(tk_t tk, uint16_t n)
{
    tk_damagebox(tk,tk->x[n],tk->y[n],tk->w[n],tk->h[n]);
}

void tk_sharedraw(tk_t tk, uint16_t n)
{
    uint16_t i;
    for(i=0;tk->cb_f[i];i++)
        if(tk->draw_f[i] == tk->draw_f[n])
            tk->drawstuff[i] = tk->drawstuff[n]; 
}

void tk_optimizedefaultdraw(tk_t tk)
{//make any draw functions using default get no damage property
    uint16_t i;
    for(i=0;tk->cb_f[i];i++)
        if(tk->draw_f[i] == tk_drawdial ||
           tk->draw_f[i] == tk_drawbutton)
        {
            tk_draw(tk,i);
            tk_sharedraw(tk,i);
            tk->props[i] |= TK_NO_DAMAGE;
        }
}


void tk_checktimers(tk_t tk)
{
    uint16_t i,n;
    float *nexttime,period, t = (float)timer_current_seconds(tk->tlibh);
    for(i=0;tk->timer && tk->timer[i];i++)
    {
        n = tk->timer[i];
        nexttime = (float*)tk->extras[n];
        if(t>=*nexttime)
        {
            tk->callback_f[n](tk,0,n);
            period = *(float*)tk->value[n];
            if(period)
            {
                *nexttime += period;//set timer for next tick
                if(*nexttime+period<t)
                    *nexttime = t+period;//we're way overdue, start again from now
            }
            else
                tk_removefromlist(tk->timer,tk->timer[i--]);//decrement since the current item was removed
        }
    } 
}

uint16_t tk_eventsearch(tk_t tk, const PuglEvent* event)
{
    uint16_t i,n=0,l=1;
    float x,y;
    switch (event->type) {
    case PUGL_BUTTON_PRESS:
    case PUGL_BUTTON_RELEASE:
        x = event->button.x;
        y = event->button.y;
        break;
    case PUGL_SCROLL:
        x = event->scroll.x;
        y = event->scroll.y;
        break;
    case PUGL_MOTION_NOTIFY:
        x = event->motion.x;
        y = event->motion.y;
        break;
    default:
        return 0;
    }
    for(i=1; tk->cb_f[i]; i++)
    {
        if( x >= tk->x[i] && x <= tk->x[i] + tk->w[i] &&
            y >= tk->y[i] && y <= tk->y[i] + tk->h[i] &&
            tk->layer[i] > l )
        {
            l = tk->layer[i];
            n = i; 
        }
    }
    return n;
}

//primary callback for all events, sorts to appropriate widget
void tk_callback (PuglView* view, const PuglEvent* event)
{ 
    uint16_t n;
    tk_t tk = (tk_t)puglGetHandle(view);
    switch (event->type) {
    case PUGL_NOTHING:
        break;
    case PUGL_CONFIGURE:
        if(event->configure.width == (tk->w[0]+2*tk->x[0]) &&
           event->configure.height == (tk->h[0]+2*tk->y[0]) )
           return;
        tk_resizeeverything(tk,event->configure.width,event->configure.height);
        break;
    case PUGL_EXPOSE:
        tk_damagebox(tk,
                event->expose.x,
                event->expose.y,
                event->expose.width,
                event->expose.height); 
        break;
    case PUGL_CLOSE:
        tk->quit = 1;
        break;
    case PUGL_KEY_PRESS:
        fprintf(stderr, "Key %u (char %u) press (%s)%s\n",
                event->key.keycode, event->key.character, event->key.utf8,
                event->key.filter ? " (filtered)" : "");
        if(tk->focus)
            tk->cb_f[tk->focus](tk,event,tk->focus);
        break;
    case PUGL_KEY_RELEASE:
        fprintf(stderr, "Key %u (char %u) release (%s)%s\n",
                event->key.keycode, event->key.character, event->key.utf8,
                event->key.filter ? " (filtered)" : "");
        break;
    case PUGL_MOTION_NOTIFY:
        if(tk->drag)
        {
            tk->cb_f[tk->drag](tk,event,tk->drag);
            if(tk->ttip)
                tk_settimer(tk,tk->ttip,0);
        }
        else 
        {//tooltip
            n=tk_eventsearch(tk,event);
            tk->tover = n;
            if(tk->ttip)
            {//ttip enabled
                if(n && tk->tip[n] && strlen(tk->tip[n]))//mouse is over a widget with a tip   
                    tk_settimer(tk,tk->ttip,TK_TOOLTIP_TIME);
                else
                {
                    tk_settimer(tk,tk->ttip,0);
                    if(tk->layer[tk->ttip-1])
                        tk_hide(tk,tk->ttip-1,true);
                }
            }
        }
        break;
    case PUGL_BUTTON_RELEASE:
        if(tk->drag)
        {
            tk->cb_f[tk->drag](tk,event,tk->drag);
            tk->drag = 0;
        }
        //no break
    case PUGL_BUTTON_PRESS:
        n = tk_eventsearch(tk,event);
        if(tk->focus != n)
            tk->focus = 0;
        if(tk->ttip)
            tk_settimer(tk,tk->ttip,0); //disable tt
        if(n)
            tk->cb_f[n](tk,event,n);
        break;
    case PUGL_SCROLL:
        n = tk_eventsearch(tk,event);
        if(n)
            tk->cb_f[n](tk,event,n);
        break;
    case PUGL_ENTER_NOTIFY:
        //fprintf(stderr, "Entered\n");
        break;
    case PUGL_LEAVE_NOTIFY:
        //fprintf(stderr, "Exited\n");
        break;
    case PUGL_FOCUS_IN:
        //fprintf(stderr, "Focus in\n");
        break;
    case PUGL_FOCUS_OUT:
        //fprintf(stderr, "Focus out\n");
        break;
    }
}

// Sundry_Helper_Functions
void tk_addtogrowlist(uint16_t** list, uint16_t *len, uint16_t n)
{
    uint16_t i=0;
    uint16_t *newlist;
    if(!*list || !*len)
    {
        *list = (uint16_t*)calloc(sizeof(uint16_t),4);
        *len = 4;
    }
    //check for duplicates
    for(i=0;(*list)[i];i++)//find end of list
        if((*list)[i]==n)
            return;//already in list
    if(i == *len-1)
    {//list is full
        newlist = (uint16_t*)calloc(sizeof(uint16_t),2**len);
        memcpy(newlist,*list,sizeof(uint16_t)**len);
        free(*list);
        *list = newlist;
        *len *=2;
    }
    (*list)[i] = n;
    (*list)[i+1] = 0;
}

void tk_addtolist(uint16_t* list, uint16_t n)
{
    uint16_t i;
    for(i=0;list[i];i++)//find end of list
        if(list[i]==n)
            return;
    list[i] = n;
}

void tk_removefromlist(uint16_t* list, uint16_t n)
{
    uint16_t i;
    for(i=0;list[i]&&list[i]!=n;i++);//find item in list
    if(list[i]==n)
        for(;list[i];i++)
            list[i] = list[i+1]; 
}

//insert n in position i
void tk_insertinlist(uint16_t* list, uint16_t n, uint16_t i)
{
    uint16_t j,k;
    for(j=0;list[j]&&list[j]!=n;j++);//find end of list
    if(list[j]==n)
    {
        //it's already in the list once, move it
        if(j<i)
            for(k=j;k<i;k++)
                list[k] = list[k+1];
        else if(j>i)
            for(k=j;k>i;k--)
                list[k] = list[k-1];
    }
    else
    {
        list[j+1] = 0;//caution, don't call this if you are at the max length already
        for(;j>i;j--)
            list[j] = list[j-1];
    }
    list[i] = n;
}

//memlen is optional, returns length allocated
void tk_setstring(char** str, const char* msg, uint16_t *memlen)
{
    uint16_t l = strlen(msg);
    if( *str ) free(*str);
    *str = (char*)calloc(l+2,sizeof(char));
    strcpy(*str,msg);
    (*str)[l] = 0;
    if( memlen ) *memlen = l+2;
}

void tk_growstring(char** str, uint16_t* memlen)
{
    //TODO: this doesn't work
    uint16_t l = 8;
    char* tmp;
    if( *str )
        l = strlen(*str);
    tmp = (char*)calloc(2*l,sizeof(char));
    if( *str )
    {
        strcpy(tmp,*str);
        free(*str);
    }
    *str = tmp; 
    *memlen = l;
}

void tk_strinsert(char* dest, char* src, uint16_t i)
{
    char* tmp = (char*)calloc(strlen(&dest[i])+1,sizeof(char));
    strcpy(tmp,&dest[i]);
    strcpy(&dest[i],src);
    strcat(dest,tmp); 
    free(tmp);
}

//remove l characters starting at i
void tk_strcut(char* str, uint16_t i, uint16_t l)
{
    memmove(&str[i], &str[i+l], strlen(str)-l+1);
}

void tk_hide(tk_t tk, uint16_t n, bool damage)
{
    uint16_t i;
    if(tk->layer[n] == tk->lmax)
    {//this could be the only one on this layer
        for(i=0;tk->draw[i];i++);//find end of list
        if(i>1)
            tk->lmax = tk->layer[tk->draw[i-2]];
        else
            tk->lmax = 1;//you have hidden everything
    }
    tk_removefromlist(tk->draw,n);
    tk_removefromlist(tk->redraw,n);
    tk->layer[n] = 0;
    if (damage) tk_damage(tk,n);
}

void tk_changelayer(tk_t tk, uint16_t n, uint16_t layer)
{
    uint16_t i;
    if(!layer)
    {//hide it
        tk_hide(tk,n,true);
    }
    else
    {
        if(layer > tk->lmax)
            tk->lmax = layer;
        else if(tk->layer[n] == tk->lmax)
        {//this could be the only one on this layer
            for(i=0;tk->draw[i];i++);//find end of list
            tk->lmax = tk->layer[tk->draw[--i]];
        }
        for(i=0;tk->layer[tk->draw[i]]<layer+1&&tk->draw[i];i++);//find end of others on same layer
        tk_insertinlist(tk->draw,n,i);
        for(i=0;tk->layer[tk->redraw[i]]<layer+1&&tk->redraw[i];i++);//find end of layer
        tk_insertinlist(tk->redraw,n,i);
        tk->layer[n] = layer;
    }
}

//this function is to avoid double frees in cleanup
void tk_rmdupptr(void** a)
{
    uint16_t i,j;
    for(i=0;a[i];i++)
        for(j=i+1;a[j];j++)
            if(a[i] == a[j])
            {//rm first instance
                a[i] = 0;
                continue;
            }
}

// General_Widget_Stuff
void tk_nocallback(tk_t tk, const PuglEvent* e, uint16_t n)
{(void)tk;(void)e;(void)n;}

uint16_t tk_addaWidget(tk_t tk, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{ 
    uint16_t n = tk->nitems++;
    if (tk->nitems == tk->tablesize)
        tk_growprimarytable(tk);
    tk->x[n] = x;
    tk->y[n] = y;
    tk->w[n] = w;
    tk->h[n] = h;
    tk->layer[n] = 2;//bg is layer 1
    tk_addtolist(tk->draw,n);
    tk->draw_f[n] = tk_drawnothing;
    tk->cb_f[n] = tk_nocallback;
    tk->callback_f[n] = tk_nocallback;
    return n;
}

// Dial_Stuff
float tk_getdial(tk_t tk, uint16_t n)
{
    float *v = (float*)tk->value[n];
    tk_dial_stuff* tkd = (tk_dial_stuff*)tk->extras[n];
    if(tk->props[n]&TK_VALUE_PARABOLIC)
        return *v**v*(tkd->max-tkd->min)+ tkd->min;
    else
        return *v*(tkd->max-tkd->min)+ tkd->min;
}

void tk_setdial(tk_t tk, uint16_t n, float v)
{
    tk_dial_stuff* tkd = (tk_dial_stuff*)tk->extras[n];
    float *val = (float*)tk->value[n];
    if(v > tkd->max) v = tkd->max;
    if(v < tkd->min) v = tkd->min;
    if(tk->props[n]&TK_VALUE_PARABOLIC)
        *val = sqrt((v - tkd->min)/(tkd->max-tkd->min));
    else
        *val = (v - tkd->min)/(tkd->max-tkd->min);
    tk_addtolist(tk->redraw,n);
}

void tk_dialcallback(tk_t tk, const PuglEvent* event, uint16_t n)
{
    float s = tk->w[n],*v = (float*)tk->value[n];
    tk_dial_stuff* tkd = (tk_dial_stuff*)tk->extras[n];
    switch (event->type) {
    case PUGL_MOTION_NOTIFY:
        if(s < tk->h[n]) s= tk->h[n]; //here we make the assumption dials will usually be approximately round (not slider shaped)
        *v = tkd->v0 +
             (event->motion.x - tkd->x0)/(30.f*s) + 
             (tkd->y0 - event->motion.y)/(3.f*s);
        if(*v > 1) *v = 1;
        if(*v < 0) *v = 0;
        tk->callback_f[n](tk,event,n);
        tk_addtolist(tk->redraw,n);
        break;
    case PUGL_BUTTON_PRESS:
        tk->drag = n;
        tkd->x0 = event->button.x;
        tkd->y0 = event->button.y;
        tkd->v0 = *v;
        break;
    case PUGL_BUTTON_RELEASE:
        tkd->x0 = 0;
        tkd->y0 = 0;
        break;
    case PUGL_SCROLL:
        *v += event->scroll.dx/(30.f*s)+ event->scroll.dy/(3.f*s);
        if(*v > 1) *v = 1;
        if(*v < 0) *v = 0;
        tk->callback_f[n](tk,event,n);
        tk_addtolist(tk->redraw,n);
        break;
    default:
        break;
    }
}


uint16_t tk_addaDial(tk_t tk, uint16_t x, uint16_t y, uint16_t w, uint16_t h, float min, float max, float val)
{
    uint16_t n = tk->nitems;
    tk_dial_stuff* tkd = (tk_dial_stuff*)malloc(sizeof(tk_dial_stuff));

    tk_addaWidget(tk,x,y,w,h);
    tk->extras[n] = (void*)tkd;
    tkd->min = min;
    tkd->max = max;
    tk->value[n] = (void*)malloc(sizeof(float));
    *(float*)tk->value[n] = (val-min)/(max-min); 

    tk->draw_f[n] = tk_drawdial;//default
    tk_addtolist(tk->hold_ratio,n);

    tk->cb_f[n] = tk_dialcallback;
    return n;

}

// Button_Stuff
void tk_buttoncallback(tk_t tk, const PuglEvent* event, uint16_t n)
{
    bool *v = (bool*)tk->value[n];
    switch (event->type) {
    case PUGL_MOTION_NOTIFY:
        if( tk->props[n]&TK_BUTTON_MOMENTARY &&
            (event->motion.x < tk->x[n] || event->motion.x > tk->x[n] + tk->w[n] ||
            event->motion.y < tk->y[n] || event->motion.y > tk->y[n] + tk->h[n])
          )
        {
            //click has left the widget
            tk->drag = 0;
            *v = !*v;
            tk->callback_f[n](tk,event,n);
            tk_addtolist(tk->redraw,n);
        }
        break;
    case PUGL_BUTTON_PRESS:
        tk->drag = n;
        if(tk->props[n]&TK_BUTTON_MOMENTARY)
        {
            *v = !*v;
            tk->callback_f[n](tk,event,n);
            tk_addtolist(tk->redraw,n);
        }
        break;
    case PUGL_BUTTON_RELEASE:
        if(tk->drag == n &&
           (event->button.x >= tk->x[n] && event->button.x <= tk->x[n] + tk->w[n] &&
            event->button.y >= tk->y[n] && event->button.y <= tk->y[n] + tk->h[n])
          )
        {
            *v = !*v;
            tk->callback_f[n](tk,event,n);
            tk_addtolist(tk->redraw,n);
        }
        break;
    default:
        break;
    }
}

uint16_t tk_addaButton(tk_t tk, uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool val)
{
    uint16_t n = tk->nitems;

    tk_addaWidget(tk,x,y,w,h);
    tk->value[n] = (void*)malloc(sizeof(bool));
    *(bool*)tk->value[n] = val;

    tk->draw_f[n] = tk_drawbutton;//default

    tk->cb_f[n] = tk_buttoncallback;
    return n; 
}

// Timer_Stuff

//timers are an entirely different beast from other widgets
void tk_settimer(tk_t tk, uint16_t n, float s)
{
    *(float*)tk->value[n] = s;
    *(float*)tk->extras[n] = (float)timer_current_seconds(tk->tlibh)+s;
    if(s)
        tk_addtolist(tk->timer,n);
    else
        tk_removefromlist(tk->timer,n);
}

uint16_t tk_addaTimer(tk_t tk, float s)
{
    //may want to make this actually off the window
    uint16_t n = tk->nitems++; 
    tk->x[n] = 0;
    tk->y[n] = 0;
    tk->w[n] = 0;
    tk->h[n] = 0;
    tk->layer[n] = 0;
    tk->draw_f[n] = tk_drawnothing;
    tk->cb_f[n] = tk_nocallback;
    tk->callback_f[n] = tk_nocallback;
    tk->value[n] = malloc(sizeof(float));
    tk->extras[n] = malloc(sizeof(float));
    if(!tk->timer)
        tk->timer = (uint16_t*)calloc(tk->tablesize,sizeof(uint16_t));//probably won't need this many, manually allocate this if you want to use a little less memory
    tk_settimer(tk,n,s);
    return n;
}

// General_Text_Stuff

//this function makes the font stuff from a binary blob or file
//fsize is binary size (if 0 the 2nd variable must be a path)
//findex is the font index in the file
tk_font_stuff* tk_gimmeaFont(tk_t tk, const uint8_t* font, uint32_t fsize, uint32_t findex, uint16_t h) 
{
    int fontsize = h;
    tk_font_stuff* tkf = (tk_font_stuff*)malloc(sizeof(tk_font_stuff));

    //freetype stuff 
    FT_Library  library;   /* handle to library     */
    FT_Face     face;      /* handle to face object */
    FT_Error    error;
    //cairo stuff
    cairo_font_extents_t extents;
    //harfbuzz stuff
    hb_buffer_t *buf;
    hb_font_t *hbfont;

    //now font setup stuff 
    error = FT_Init_FreeType( &library );
    if ( error ) 
    { 
        fprintf(stderr, "OH NO, Freetype init problem!");
        free(tkf);
        return 0;
    }

    if(fsize)
        error = FT_New_Memory_Face( library,
             font,
             fsize,
             findex,
             &face );
    else
        error = FT_New_Face( library,
             (char*)font,
             findex,
             &face );
    if ( error == FT_Err_Unknown_File_Format )
    {
      //... the font file could be opened and read, but it appears
      //  ... that its font format is unsupported
        fprintf(stderr, "OH NO, Font problem!");
        free(tkf);
        return 0;
    }
    else if ( error )
    {
          //... another error code means that the font file could not
          //  ... be opened or read, or that it is broken...
        fprintf(stderr, "OH NO, Font not found!");
        free(tkf);
        return 0;
    } 

    //CAIRO
    cairo_set_font_face(tk->cr, cairo_ft_font_face_create_for_ft_face(face,0));
    cairo_set_font_size(tk->cr, fontsize);

    cairo_font_extents(tk->cr,&extents);

    //harfbuzz
    buf = hb_buffer_create();
    //TODO: at some point it may be necessary to allow these to be specified, but not today
    hb_buffer_set_unicode_funcs(buf, hb_unicode_funcs_get_default());
    hb_buffer_set_direction(buf, HB_DIRECTION_LTR); /* or LTR */
    hb_buffer_set_script(buf, HB_SCRIPT_LATIN); /* see hb-unicode.h */
    hb_buffer_set_language(buf, hb_language_from_string("en", 2));
    //convert the ft font face to hb_font
    hbfont = hb_ft_font_create(face,NULL);
    hb_font_set_scale(hbfont, fontsize*64, fontsize*64);
    hb_ft_font_set_funcs(hbfont);

    //the buffer will be loaded with text and shaped when its time to render

    tkf->library = library;
    tkf->face = face;
    tkf->fontsize = fontsize;
    tkf->base = extents.ascent;
    tkf->buf = buf;
    tkf->hbfont = hbfont;

    return tkf; 
}

//we assume there is a valid font with set size and a string, we will set line brks 
//we will pass back the actual dimensions in w and h, and 
//return  true if the text fits in the provided size 
bool tk_textlayout(cairo_t* cr, tk_text_table* tkt, uint16_t n, uint16_t *w, uint16_t *h, uint16_t props)
{
//TODO: should this be changed to batch process all strings?
    bool fit;
    uint16_t i,j,size,str_index,lastwhite,*tmp;
    const int margin = 2;
    float x,y,xmax,xstart,ostart;
    tk_font_stuff* tkf = tkt->tkf[n];

    hb_glyph_info_t *glyph_info;
    float *glyph_pos = tkt->glyph_pos[n];
    hb_glyph_position_t *glyph_position;

    cairo_glyph_t* glyphs = tkt->glyphs[n];
    unsigned int glyph_count = tkt->glyph_count[n];
    uint16_t *cluster_map = tkt->cluster_map[n];

    if(props&TK_TEXT_VERTICAL)
    {
       tmp = w;
       w = h;
       h = tmp;
    }

    *w /= tkt->scale;
    *w -= margin;//leave space for RHS margin
    *h /= tkt->scale;

    size = tkt->tkf[n]->fontsize;
    //TODO: there is no strchange when finding tip location or window ratio change
    if(tkt->strchange[n])
    {
        //shape
        hb_buffer_reset(tkf->buf);
        hb_buffer_add_utf8(tkf->buf,tkt->str[n],-1,0,-1);//magic numbers mean use strlen, no offset, add full string
        hb_buffer_set_direction(tkf->buf,HB_DIRECTION_LTR);
        hb_shape(tkf->hbfont,tkf->buf, NULL, 0);//no features specified

        glyph_info = hb_buffer_get_glyph_infos(tkf->buf, &glyph_count);
        glyph_position = hb_buffer_get_glyph_positions(tkf->buf, &glyph_count);
        //TODO: why separate _end and _count? _end is number to be drawn, _count is number allocated
        tkt->glyph_end[n] = glyph_count;
        if(glyph_count > tkt->glyph_count[n])
        {
            free(glyphs);
            free(cluster_map);
            free(glyph_pos);
            glyphs = (cairo_glyph_t*)malloc(sizeof(cairo_glyph_t) * (glyph_count+1));
            glyphs[glyph_count].index = 0; //add null at end of list
            glyphs[glyph_count].x = 0;
            glyphs[glyph_count].y = 0;
            cluster_map = (uint16_t*)malloc(sizeof(uint16_t)*glyph_count+1);
            glyph_pos = (float*)malloc(sizeof(float)*(glyph_count+1));
        }

        x=0;
        for (i=0; i < glyph_count; ++i) 
        {
            glyphs[i].index = glyph_info[i].codepoint;
            cluster_map[i] = glyph_info[i].cluster;
            glyph_pos[i] = (x + glyph_position[i].x_offset/64.0);
            x += glyph_position[i].x_advance/64.0;
        }
        glyph_pos[i] = x; //get end of string
        cluster_map[i] = strlen(tkt->str[n]);
    }
    tkt->brk[n][0] = 0; //clear list

    xstart = xmax = lastwhite = 0;
    y = tkf->base;
    str_index = 0;
    for (i = 0; i < glyph_count; i++) 
    {
        str_index = cluster_map[i];
        x = glyph_pos[i] - xstart + margin;
        glyphs[i].x = x;
        glyphs[i].y = y;
        if(isspace(tkt->str[n][str_index]))
        {//keep track of most recent whitespace so we can break there
            lastwhite = i;
            if (tkt->str[n][str_index] == '\n') //newline
            {//newline breaks anyway
                tk_addtogrowlist(&tkt->brk[n], &tkt->brklen[n], i+1);
                y += size;
                xstart = glyph_pos[i+1];
            }
        } 

        if(glyph_pos[i+1]-xstart+margin > *w)
        {
            if(props&TK_TEXT_WRAP)
            {//go back to last whitespace put the rest on a newline
                ostart = xstart;//store old start
                if(!lastwhite || glyph_pos[lastwhite+1] == xstart)
                {//single word doesn't fit on a line
                    xstart = glyph_pos[i];
                    lastwhite = i-1;
                    if(glyph_pos[lastwhite+1]-ostart > xmax) //check length of line
                        xmax = glyph_pos[lastwhite+1]-ostart;
                }
                else
                {
                    xstart = glyph_pos[lastwhite+1];
                    if(glyph_pos[lastwhite]-ostart > xmax) //check length of line
                        xmax = glyph_pos[lastwhite]-ostart;
                }
                tk_addtogrowlist(&tkt->brk[n], &tkt->brklen[n], lastwhite+1);
                y += size;
                for(j=lastwhite+1;j<=i;j++)
                {//move previous glyphs to new line
                    x = glyph_pos[j] - xstart + margin;
                    glyphs[j].x = x;
                    glyphs[j].y = y;
                }
            }
            else if(tkt->glyph_end[n] > i)
            {
                //TODO: need to reset glyph end if now its wider
                tkt->glyph_end[n] = i;
            }
        }
    }
    //populate extra glyph to know where line ends
    x = glyph_pos[i] - xstart + margin;
    glyphs[i].x = x;
    glyphs[i].y = y;
    if(glyph_pos[i]-xstart > xmax) //check last line
        xmax = glyph_pos[i]-xstart;

    tkt->glyphs[n] = glyphs;
    tkt->glyph_count[n] = glyph_count;
    tkt->glyph_pos[n] = glyph_pos;
    tkt->cluster_map[n] = cluster_map;

    y += size-tkf->base;

    fit = true;
    if(xmax > *w)
        fit = false;
    if(y > *h)
        fit = false; 
    //TODO: show what you can at least
    if(!fit)
    fprintf(stderr, "doesn't fit! %f>%i or %f>%i  %s\n",xmax,*w,y,*h,tkt->str[n]);

    if(fit && props&TK_TEXT_CENTER)
    {//center
        x = (*w-xmax-margin)/2.0;
        y = (*h-y)/2.0;
        for (i = 0; i <= glyph_count; i++)
        {
            glyphs[i].x += x;
            glyphs[i].y += y;
        }
    }

    *w = (xmax+margin)*tkt->scale;
    *h = y*tkt->scale;

    if(props&TK_TEXT_VERTICAL)
    {
       tmp = w;
       w = h;
       h = tmp;
    }

    return fit;
}

//set the text of a text widget
void tk_settext(tk_t tk, uint16_t n, const char* str)
{
    uint16_t tw,th,s;
    tk_text_stuff* tkts;
    tw = tk->w[n];
    th = tk->h[n];
    tkts = (tk_text_stuff*)tk->value[n];
    s = tkts->n;
    tk_setstring(&tk->tkt.str[s],str,0);
    tk->tkt.strchange[s] = true;
    tk_textlayout(tk->cr,&tk->tkt,s,&tw,&th,tk->props[n]);
    tk_addtolist(tk->redraw,n);
}

void tk_growtexttable(tk_text_table* tkt)
{
    uint8_t osz,sz = TK_TEXT_STARTER_SIZE;
    tk_text_table tmpt;
    if(tkt->tablesize)
        sz = 2*tkt->tablesize;
    tmpt.str =         (char**)calloc(sz,sizeof(char*));
    tmpt.strchange = (bool*)calloc(sz,sizeof(bool));
    tmpt.memlen =   (uint16_t*)calloc(sz,sizeof(uint16_t));
    tmpt.n =        (uint16_t*)calloc(sz,sizeof(uint16_t));
    tmpt.cursor =   (uint16_t*)calloc(sz,sizeof(uint16_t));
    tmpt.select =   (uint16_t*)calloc(sz,sizeof(uint16_t));
    tmpt.ln =       (uint16_t*)calloc(sz,sizeof(uint16_t));
    tmpt.col =      (uint16_t*)calloc(sz,sizeof(uint16_t));
    tmpt.brklen =   (uint16_t*)calloc(sz,sizeof(uint16_t));
    tmpt.brk =     (uint16_t**)calloc(sz,sizeof(uint16_t*));

    tmpt.tkf =    (tk_font_stuff**)calloc(sz,sizeof(tk_font_stuff*));
    tmpt.glyphs = (cairo_glyph_t**)calloc(sz,sizeof(cairo_glyph_t*));
    tmpt.glyph_pos =  (float**)calloc(sz,sizeof(float*));
    tmpt.cluster_map = (uint16_t**)calloc(sz,sizeof(uint16_t*));
    tmpt.glyph_count =  (uint16_t*)calloc(sz,sizeof(uint16_t));
    tmpt.glyph_end   =  (uint16_t*)calloc(sz,sizeof(uint16_t));

    if(tkt->tablesize)
    {
        osz = tkt->tablesize;
        memcpy(tmpt.str,      tkt->str,      osz*sizeof(char*));
        memcpy(tmpt.strchange,tkt->strchange,osz*sizeof(bool));
        memcpy(tmpt.memlen,   tkt->memlen,   osz*sizeof(uint16_t));
        memcpy(tmpt.n,        tkt->n,        osz*sizeof(uint16_t));
        memcpy(tmpt.cursor,   tkt->cursor,   osz*sizeof(uint16_t));
        memcpy(tmpt.select,   tkt->select,   osz*sizeof(uint16_t));
        memcpy(tmpt.ln,       tkt->ln,       osz*sizeof(uint16_t));
        memcpy(tmpt.col,      tkt->col,      osz*sizeof(uint16_t));
        memcpy(tmpt.brklen,   tkt->brklen,   osz*sizeof(uint16_t));
        memcpy(tmpt.brk,      tkt->brk,      osz*sizeof(uint16_t*));

        memcpy(tmpt.tkf,      tkt->tkf,      osz*sizeof(tk_font_stuff*));
        memcpy(tmpt.glyphs,   tkt->glyphs,   osz*sizeof(cairo_glyph_t*));
        memcpy(tmpt.glyph_pos,   tkt->glyph_pos,   osz*sizeof(float*));
        memcpy(tmpt.cluster_map, tkt->cluster_map, osz*sizeof(uint16_t));
        memcpy(tmpt.glyph_count, tkt->glyph_count, osz*sizeof(uint16_t));
        memcpy(tmpt.glyph_end,   tkt->glyph_end,   osz*sizeof(uint16_t));
    }

    tkt->str = tmpt.str;
    tkt->strchange = tmpt.strchange;
    tkt->memlen = tmpt.memlen;
    tkt->n = tmpt.n;
    tkt->cursor = tmpt.cursor;
    tkt->select = tmpt.select;
    tkt->ln = tmpt.ln;
    tkt->col = tmpt.col;
    tkt->brklen = tmpt.brklen;
    tkt->brk = tmpt.brk;

    tkt->tkf = tmpt.tkf;
    tkt->glyphs = tmpt.glyphs;
    tkt->glyph_pos = tmpt.glyph_pos;
    //tkt->clusters = tmpt.clusters;
    //tkt->extents = tmpt.extents;
    tkt->glyph_count = tmpt.glyph_count;
    tkt->glyph_end = tmpt.glyph_end;
    tkt->cluster_map = tmpt.cluster_map;
    //tkt->cluster_count = tmpt.cluster_count;
    //tkt->extents_count = tmpt.extents_count;

    tkt->tablesize = sz;
}

uint16_t tk_addaText(tk_t tk, uint16_t x, uint16_t y, uint16_t w, uint16_t h, tk_font_stuff* font, const char* str)
{
    uint16_t n = tk->nitems; 
    uint16_t s = tk->tkt.nitems++;
    uint16_t w2 = w;
    uint16_t h2 = h;
    tk_text_table* tkt = &tk->tkt;

    tk_text_stuff* tkts = (tk_text_stuff*)malloc(sizeof(tk_text_stuff));
    
    tk_addaWidget(tk,x,y,w,h);
    
    if(!tkt->tablesize || s >= tkt->tablesize)
        tk_growtexttable(&tk->tkt);

    tk_setstring(&tkt->str[s],str, &tkt->memlen[s]);

    tk_addtogrowlist(&tkt->brk[s], &tkt->brklen[s], 0);//alloc list for linebreaks

    if(!font)
    {
        if(tkt->tkf[0])//check for default font
            font = tkt->tkf[0];
        else
        {//make the default font
            font = tk_gimmeaFont(tk,LibraSerifModern_Regular,sizeof(LibraSerifModern_Regular),0,10);
        }
    }
    tkt->tkf[s] = font;
    tkt->scale = 1;
    tkt->strchange[s] = true;
    tkt->ln = 0;
    tk_textlayout(tk->cr,tkt,s,&w2,&h2,0);
    //TODO: what if w and h don't fit right out the gate?

    tk->draw_f[n] = tk_drawtext;
    tkts->tkt = tkt;
    tkts->n = s;
    tkt->n[s] = n;
    tk->value[n] = tkts;

    return n; 
} 

uint16_t tk_addaVerticalText(tk_t tk, uint16_t x, uint16_t y, uint16_t w, uint16_t h, tk_font_stuff* font, const char* str)
{
    uint16_t n = tk_addaText(tk,x,y,h,w,font,str); //notice the tricky w,h transpose!
    tk->w[n] = w;
    tk->h[n] = h;
    tk->props[n] |= TK_TEXT_VERTICAL;
    tk->draw_f[n] = tk_drawverticaltext;
    return n;
}

// Text_Entry_Stuff

//gets character index of clicked pos in text
uint16_t tk_gettextchar(tk_text_table* tkt, uint16_t n, uint16_t x, uint16_t y)
{
    uint16_t i,j,end;
    x /= tkt->scale;
    y /= tkt->scale;
    if(y>2) y -= 2;
    else y = 0;
    j=0;
    for(i=tkt->brk[n][0];i&&y>tkt->glyphs[n][i].y;i=tkt->brk[n][++j]);//find row
    end = tkt->brk[n][j];
    if(j)j--; //line no.
    if(!end)end = tkt->glyph_count[n]; //end of line glyph
    for(i=tkt->brk[n][j];(x-tkt->glyphs[n][i].x)>(tkt->glyphs[n][i+1].x-x)&&i<end;i++); //find col
    j = tkt->cluster_map[n][i];
    return j;
}

void tk_textentrycallback(tk_t tk, const PuglEvent* event, uint16_t n)
{
    uint16_t tw,th,del,c;
    uint8_t s = ((tk_text_stuff*)tk->value[n])->n;
    switch (event->type) {
    case PUGL_BUTTON_PRESS:
        if(tk->focus == n)
        {
            c = tk_gettextchar(&tk->tkt,s,event->button.x-tk->x[n],event->button.y-tk->y[n]);
            if(c == tk->tkt.cursor[s])
            {//3rd click
                tk->tkt.cursor[s] = 0; //TODO: it would maybe be nicer to just highlight the current word
                tk->tkt.select[s] = strlen(tk->tkt.str[s]);
                tk->tkt.cursorstate |= TK_CURSOR_MOVED;
            }
            else
            {//2nd click
                tk->tkt.cursor[s] = c;
                tk->tkt.select[s] = 0;
                tk->tkt.cursorstate |= TK_CURSOR_STATE + TK_CURSOR_MOVED;
            }
        }
        else
        {//1st click
            tk->focus = n;
            tk_settimer(tk,tk->tkt.cursortimer,.4);
            tk->tkt.cursorstate |= TK_CURSOR_MOVED;
        }
        tk_addtolist(tk->redraw,n);
        tk->drag = n;
        break;
    case PUGL_MOTION_NOTIFY:
        if(tk->focus == n)
        {
            tw = tk_gettextchar(&tk->tkt,s,event->button.x-tk->x[n],event->button.y-tk->y[n]); //just using tw for calulating selection size
            //TODO: is cursor in character index or glyphs?
            if(tw > tk->tkt.cursor[s])
                tw -= tk->tkt.cursor[s];
            else
            {
                th = tk->tkt.cursor[s]+tk->tkt.select[s] - tw;
                tk->tkt.cursor[s] = tw; //move cursor back
                tw = th;
            }
            if(tw != tk->tkt.select[s])
            {
                tk->tkt.select[s] = tw;
                tk->tkt.cursorstate |= TK_CURSOR_MOVED;
                //tk->tkt.cursorstate |= TK_CURSOR_CHANGED + TK_CURSOR_MOVED;
                tk_addtolist(tk->redraw,n);
            }
        }
        break;
    case PUGL_KEY_PRESS:
        //navigation
        tw = strlen(tk->tkt.str[s]);
        if(event->key.keycode == 113 && tk->tkt.cursor[s])
            tk->tkt.cursor[s]--; //back arrow
        else if(event->key.keycode == 114 && (tk->tkt.cursor[s]+tk->tkt.select[s])<tw)
            tk->tkt.cursor[s] = tk->tkt.cursor[s]+tk->tkt.select[s]+1; //forward arrow
        else if(event->key.keycode == 110)
            tk->tkt.cursor[s] = 0; //home
        else if(event->key.keycode == 115)
            tk->tkt.cursor[s] = tw; //end
        //TODO: up down
        //TODO: ignore shift, ctl etc
        else if(strlen((char*)event->key.utf8))
        {//it changes the string
            del = tk->tkt.select[s];
            if(!del)del++;
            if(event->key.keycode == 119)
            {//delete
                if(tk->tkt.cursor[s]<tw) 
                    tk_strcut(tk->tkt.str[s], tk->tkt.cursor[s], del);
                else return;//no change, no redraw
            }
            else if(event->key.keycode == 22)
            {//backspace
                if(tk->tkt.select[s])
                    tk_strcut(tk->tkt.str[s], tk->tkt.cursor[s], del);
                else if(tk->tkt.cursor[s])
                    tk_strcut(tk->tkt.str[s], --tk->tkt.cursor[s], del);
                else return;//no change, no redraw
            }
            else
            {//regular character keypress
                if(tw+strlen((char*)event->key.utf8)+1 > tk->tkt.memlen[s])
                    tk_growstring(&tk->tkt.str[s], &tk->tkt.memlen[s]);
                tk_strcut(tk->tkt.str[s],tk->tkt.cursor[s],tk->tkt.select[s]);//remove (replace) selection
                tk_strinsert(tk->tkt.str[s],(char*)event->key.utf8,tk->tkt.cursor[s]++);
            }
            tk->tkt.strchange[s] = true;
            tw = tk->w[n];
            th = tk->h[n];
            tk_textlayout(tk->cr,&tk->tkt,s,&tw,&th,tk->props[n]);
        }
        tk->tkt.select[s] = 0;
        tk->tkt.cursorstate |= TK_CURSOR_STATE + TK_CURSOR_MOVED;
        tk_addtolist(tk->redraw,n);
        tk->callback_f[n](tk,event,n);
    default:
        break;
    }
}

//this helper is mostly used by draw functions
void tk_gettextcursor(void* valp, int *x, int *y, int *sx, int *sy)
{
    tk_text_stuff* tkts = (tk_text_stuff*)valp;
    tk_text_table* tkt = (tk_text_table*)tkts->tkt;
    int i,j,n = tkts->n;
    float deltax=0;
    
    *sx = *sy = 0;
    if(!tkt->glyph_count[n])
    {
        *x = *y = 0;
        return;
    }
    for(i=0;i<tkt->glyph_count[n] && tkt->cluster_map[n][i]<tkt->cursor[n];i++);//get the cursor glyph
    if(i==tkt->glyph_count[n])
    {//cursor is at the end
        deltax = tkt->glyph_pos[n][i] - tkt->glyph_pos[n][i-1];
        i--;
    }
    else if(tkt->select[n])
    {
        //TODO: here cursor is compared to clusters is that consistent?
        for(j=i;j<tkt->glyph_count[n] && tkt->cluster_map[n][j]<(tkt->cursor[n]+tkt->select[n]);j++);
        deltax = tkt->glyph_pos[n][j] - tkt->glyph_pos[n][j-1]; //selection always goes to end of character
        j--;
        *sx = (tkt->glyphs[n][j].x + deltax + 0)*tkt->scale;
        *sy = (tkt->glyphs[n][j].y - tkt->tkf[n]->base + 2)*tkt->scale;
        deltax = 0;
    }
    *x = (tkt->glyphs[n][i].x + deltax - 2)*tkt->scale;
    *y = (tkt->glyphs[n][i].y - tkt->tkf[n]->base)*tkt->scale;
}

void tk_cursorcallback(tk_t tk, const PuglEvent* event, uint16_t n)
{
    if(tk->focus)
    {
        tk->tkt.cursorstate ^= TK_CURSOR_STATE;
        tk->tkt.cursorstate |= TK_CURSOR_CHANGED;
        tk_addtolist(tk->redraw,tk->focus);
    }
    else
        tk_settimer(tk,n,0);
}

uint16_t tk_addaTextEntry(tk_t tk, uint16_t x, uint16_t y, uint16_t w, uint16_t h, tk_font_stuff* font, const char* str)
{
    uint16_t n = tk_addaText(tk, x, y, w, h, font, str);
    uint16_t s = ((tk_text_stuff*)tk->value[n])->n;
    tk->cb_f[n] = tk_textentrycallback;
    tk->draw_f[n] = tk_drawtextentry;
    tk->props[n] |= TK_NO_DAMAGE;
    tk->tkt.cursor[s] = 0;
    tk->tkt.select[s] = strlen(tk->tkt.str[s]);

    if(!tk->tkt.cursortimer)
    {
        tk->tkt.cursortimer = tk_addaTimer(tk, 0);
        tk->callback_f[tk->tkt.cursortimer] = tk_cursorcallback;
    }
    return n;
}

// Tooltip_Stuff
void tk_showtipcallback(tk_t tk, const PuglEvent* e, uint16_t n)
{
    uint16_t w,h,s;
    const uint8_t b = 4;//buffer around edges
    const uint8_t b2 = 2*b;
    float ww,wh;//window w and h
    n--;//text widget is 1 before timer part of ttip
    tk_text_stuff* tkts = (tk_text_stuff*)tk->value[n];
    s = tkts->n;
    if(!tk->tover) return;//no tip
    tkts->tkt->str[s] = tk->tip[tk->tover];
    tkts->tkt->strchange[s] = true;
    tk_settimer(tk,tk->ttip,0);//disable timer

    ww = tk->w[0]+2*tk->x[0];//window w
    wh = tk->h[0]+2*tk->y[0];//window h
    tk->x[n] = tk->x[tk->tover]; //move tip
    tk->y[n] = tk->y[tk->tover];

    //find best place to put the tip
    //first try to the right
    w = ww-tk->x[tk->tover]-tk->w[tk->tover];
    h = wh;
    if(w>b2) w-=b2;
    if(h>b2) h-=b2;
    if(tk_textlayout(tk->cr,tkts->tkt,s,&w,&h,TK_TEXT_WRAP))
    {//it fits
        tk->x[n] += tk->w[tk->tover]+b;
    } 
    else
    {//try on the left side
        w = tk->x[tk->tover];
        h = wh;
        if(w>b2) w-=b2;
        if(h>b2) h-=b2;
        if(tk_textlayout(tk->cr,tkts->tkt,s,&w,&h,TK_TEXT_WRAP))
        {//it fits
            tk->x[n] -= w+b;
        }
        else
        {//try above
            w = ww;
            h = tk->y[tk->tover];
            if(w>b2) w-=b2;
            if(h>b2) h-=b2;
            if(tk_textlayout(tk->cr,tkts->tkt,s,&w,&h,TK_TEXT_WRAP))
            {//it fits
                tk->y[n] -= h+b;
            }
            else
            {//try below
                w = ww;
                h = wh-tk->y[tk->tover]-tk->h[tk->tover];
                if(w>b2) w-=b2;
                if(h>b2) h-=b2;

                if(tk_textlayout(tk->cr,tkts->tkt,s,&w,&h,TK_TEXT_WRAP))
                {//it fits
                    tk->y[n] += tk->h[tk->tover]+h+b;
                }
                else
                {//don't show it
                    tk->x[n] = 0;
                    tk->y[n] = 0;
                    tk->w[n] = 0;
                    tk->h[n] = 0;
                    fprintf(stderr,"tooltip too long\n");
                    return;
                }
            }//below
        }//above
    }//left
    tk->w[n] = w+b2;
    tk->h[n] = h+b;
    if(tk->x[n]+w+b > ww)
        tk->x[n] = ww-w-b2;
    if(tk->y[n]+h+b > wh)
        tk->y[n] = wh-h-b2;

    tk_changelayer(tk,n,3);
}

uint16_t tk_addaTooltip(tk_t tk, tk_font_stuff* font)
{
    //need text 
    uint16_t n = tk_addaText(tk, 0, 0, 0, 12, font, " ");
    tk->h[n] = 0;
    tk->layer[n] = 0;
    free(tk->tip[n]);
    tk->tip[n] = 0;
    free(tk->tkt.str[tk->tkt.nitems-1]);//this just gets pointed to the tooltip str
    tk->tkt.str[tk->tkt.nitems-1] = tk->tip[0];//just a placeholder

    tk->draw_f[n] = tk_drawtip;
    tk->props[n] |= TK_NO_DAMAGE;//only does damage when it leaves, which is handled in tk_hide

    //need timer
    n = tk_addaTimer(tk, 0);
    tk->ttip = n; 
    tk->callback_f[n] = tk_showtipcallback;

    return n;
}

// Text_Button_Stuff
void tk_textbuttoncallback(tk_t tk, const PuglEvent* event, uint16_t n)
{
    bool v = *(bool*)tk->value[n];
    tk_buttoncallback(tk, event, n);
    if(v != *(bool*)tk->value[n])
        tk_addtolist(tk->redraw,n+1);
}

uint16_t tk_addaTextButton(tk_t tk, uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool val, const char* str)
{ //text button is a button with a text widget on top
    uint16_t n;
    n = tk_addaButton(tk,x,y,w,h,val);
    tk->cb_f[n] = tk_textbuttoncallback;
    n = tk_addaText(tk, x, y, w, h, 0,str);
    tk->props[n] |= TK_TEXT_CENTER;
    return n-1; //return the button index 
}

// Input_Dialog_Stuff
void tk_hideinputdialog(tk_t tk, uint16_t n)
{
    uint16_t nd;
    for(nd=n+6;nd>n;nd--) tk_hide(tk,nd,false);//hide all
    tk_hide(tk,n,true);//damage the last box
}

void tk_showinputdialog(tk_t tk, uint16_t n, const char* prompt_str, const char* def_input, void (*cb_f)(tk_t tk, char* str, void* data), void* data)
{
    uint16_t nd;
    uint8_t lmx = tk->lmax+1;
    tk_settext(tk, n+1, prompt_str); //set strings
    tk_settext(tk, n+2, def_input);
    uint8_t s = ((tk_text_stuff*)tk->value[n+2])->n;
    tk->tkt.select[s] = strlen(def_input);
    tk->focus = n+2; //this doesn't work because the click release will change the focus away, it would be nice if you could just type
    tk->extras[n+1] = (void*)cb_f; //set callback
    tk->extras[n+2] = data;
    *(bool*)tk->value[n+3] = false; //reset buttons
    *(bool*)tk->value[n+5] = false;
    tk_changelayer(tk,n++,lmx++);//put the background at the top layer
    for(nd=n+6;n<nd;n++) tk_changelayer(tk,n,lmx);//show rest atop bg
}

void tk_inputcancel(tk_t tk, const PuglEvent* e, uint16_t n)
{
    if((bool)tk->value[n])
    {
        tk_hideinputdialog(tk,n-3);
    }
}

void tk_inputok(tk_t tk, const PuglEvent* e, uint16_t n)
{
    tk_text_stuff* tkts;
    uint16_t s;
    void (*cb_f)(tk_t tk, char* str, void* data);
    if((bool)tk->value[n])
    {
        tkts = (tk_text_stuff*)tk->value[n-3];//text entry of dialog is 3 widgets previous
        s = tkts->n;
        //cb_f = (void (*cb_f)(char* str, void* data))tk->extras[n];
        cb_f = (void (*)(tk_t, char*, void*))tk->extras[n-4];
        if(cb_f) cb_f(tk, tk->tkt.str[s], tk->extras[n-3]);
        tk_hideinputdialog(tk,n-5);
    }
}

void tk_inputenter(tk_t tk, const PuglEvent* event, uint16_t n)
{
    if(event->type == PUGL_KEY_PRESS)
    {
        if(event->key.keycode == 36)
        {
            //"press" the ok button
            *(bool*)tk->value[n+3] = true;
            tk_inputok(tk,0,n+3);
        }
    }
}


//input dialog requires the window to be big enough
uint16_t tk_addaInputDialog(tk_t tk, tk_font_stuff* font)
{//0 background, 1 prompt text, 2 input textentry, 3-4 cancel, 5-6 ok
    uint16_t n,nd;
    const uint16_t midx = tk->x[0] + tk->w[0]/2.0;
    const uint16_t midy = tk->y[0] + tk->h[0]/2.0;
    const uint16_t margin = 5;
    const uint16_t buttonw = 40;
    const uint16_t buttonh = 14+margin;
    const uint16_t dialogw = buttonw+margin+buttonw+margin+buttonw+margin+buttonw;
    const uint16_t dialogh = margin+2*buttonh+margin+buttonh+margin+buttonh+margin;
    const uint16_t dialogx = midx-dialogw/2;
    const uint16_t dialogy = midy-dialogh/2;
    uint16_t y = dialogy;

    if(dialogx>tk->w[0] || dialogy>tk->h[0]) return 0; //didn't fit
    n = tk_addaButton(tk, dialogx, dialogy, dialogw, dialogh, 0); //this button is just the box around the dialog
    tk->cb_f[n] = tk_nocallback;
    y += margin;
    nd = tk_addaText(tk, dialogx+margin, y, dialogw-2*margin, buttonh, 0, "Input a value:");//prompt
    tk->props[nd] += TK_TEXT_WRAP;
    y += 2*buttonh+margin;
    nd = tk_addaTextEntry(tk, dialogx+margin, y, dialogw-2*margin, buttonh, 0, "Default");//input
    tk->callback_f[nd] = tk_inputenter;
    y += buttonh+margin;
    nd = tk_addaTextButton(tk, midx-buttonw-margin, y, buttonw, buttonh, 0, "Cancel");
    tk->callback_f[nd] = tk_inputcancel;
    nd = tk_addaTextButton(tk, midx+margin, y, buttonw, buttonh, 0, "OK");
    tk->callback_f[nd] = tk_inputok;
    tk_hideinputdialog(tk,n);
    return n;
}
