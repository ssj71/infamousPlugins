//spencer jackson
// TiKloo GUI for the infamous stuck

#include"tikloo/tk.h"
#include"lv2/lv2plug.in/ns/extensions/ui/ui.h"

#include"stuck.h"
#include"draw_stuckbg.h"
#include"draw_LED.h"

typedef struct stuck_ui
{
    LV2UI_Write_Function write_function;
    LV2UI_Controller controller;
    
    int8_t ofs;
}stuck_ui;

void stickit(tk_t tk, const PuglEvent* event, uint16_t n)
{ 
   stuck_ui* ui = (stuck_ui*)tk->user[0]; 
   *tk->user[n] = (uint8_t)*tk->value[n];
   ui->write_function(ui->controller,n-ui->ofs,sizeof(float),0,tk->user[n]); 
   //set led to match
   *tk->value[n+1] = *tk->value[n];
   tk_damage(tk,n+1);
}

void dial(tk_t tk, const PuglEvent* event, uint16_t n)
{
    const char* units[] = {""," s"};
    
   stuck_ui* ui = (stuck_ui*)tk->user[0]; 
   
   *tk->user[n] = tk_dialvalue(tk,n);
   ui->write_function(ui->controller,n-ui->ofs,sizeof(float),0,tk->user[n]);
   sprintf(tk->tip[n],"%.2f %s",*tk->user[n],units[n-DRONEGAIN]);
   tk_showtipcallback(tk,0,n);
    
}

int main()
{
    stuck_ui* ui = (stuck_ui*)malloc(sizeof(stuck_ui)); 
    uint16_t n;
    tk_t tk = tk_gimmeaTikloo(256,400,"the infamous stuck");
    tk->draw_f[0] = draw_stuckbg;
    tk->properties[0] &= TK_HOLD_RATIO;
    tk->user[0] = ui;


    n = tk_addaButton(tk,
                      43, //x
                      191,//y 
                      22, //w
                      72, //h
                      0); //value
    tk->draw_f[n] = draw_toggleSwitch;
    tk->callback_f[n] = stickit;
    tk_setstring(&tk->tip[n],"Stick It!");
    tk->user[n] = (float*)malloc(sizeof(float));
    
    n = tk_addaButton(tk,
                      77, //x
                      121,//y 
                      18, //w
                      18, //h
                      0); //value
    tk->draw_f[n] = draw_blueLED;
    tk_changelayer(tk,n,1);//on layer 1 it won't recieve events
    //the LED shares state (value) with the button

    n = tk_addaDial(tk,
                    50,  //x
                    280, //y
                    71,  //w
                    71,  //h
                    .01, //min
                    3.0, //max
                    .5); //val
    tk->draw_f[n] = draw_tabDial;
    tk->callback_f = dial;
    tk_setstring(&tk->tip[n],"Drone Level");
    tk->user[n] = (float*)malloc(sizeof(float));

    ui->ofs = DRONEGAIN-n;

    return 1;
}
