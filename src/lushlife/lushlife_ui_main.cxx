#ifndef CASYNTH_H
#define CASYNTH_H

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/x.H>

#include "lushlife_ui.h"
#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"

#define LUSHLIFEUI_URI "http://ssj71.github.io/infamousPlugins/plugs.html#lushlife_ui"

static LV2UI_Handle init_lushlifeUI(const struct _LV2UI_Descriptor * descriptor,
		const char * plugin_uri,
		const char * bundle_path,
		LV2UI_Write_Function write_function,
		LV2UI_Controller controller,
		LV2UI_Widget * widget,
		const LV2_Feature * const * features) 
{
    if(strcmp(plugin_uri, LUSHLIFE_URI) != 0)
    {
        return 0;
    }

    LushLifeUI* self = new LushLifeUI();
    if(!self) return 0;
    LV2UI_Resize* resize = NULL;

    self->controller = controller;
    self->write_function = write_function;

    void* parentXwindow = 0;
    for (int i = 0; features[i]; ++i)
    {
        if (!strcmp(features[i]->URI, LV2_UI__parent)) 
        {
           parentXwindow = features[i]->data;
        }
	else if (!strcmp(features[i]->URI, LV2_UI__resize)) 
        {
           resize = (LV2UI_Resize*)features[i]->data;
        }
    }

    self->ui = self->show();
    srand ((unsigned int) time (NULL));

    //must init graph after everything else allocated
    self->graph->set_graph(self->pdxb0,self->pdyb0,
                           self->pdxb1,self->pdyb1,
                           self->pdxb2,self->pdyb2,
                           self->pdxb3,self->pdyb3,
                           self->pdxb4,self->pdyb4,
                           self->pdxb5,self->pdyb5);

    fl_open_display();
    
    // set host to change size of the window
    if (resize)
    {
      resize->ui_resize(resize->handle, self->ui->w(), self->ui->h());
    }
    fl_embed( self->ui,(Window)parentXwindow);
    *widget = (LV2UI_Widget)fl_xid(self->ui);

    return (LV2UI_Handle)self;
}

void cleanup_lushlifeUI(LV2UI_Handle ui)
{
    LushLifeUI *self = (LushLifeUI*)ui;

    delete self->ui;
    delete self;
}

void lushlifeUI_port_event(LV2UI_Handle ui, uint32_t port_index, uint32_t buffer_size, uint32_t format, const void * buffer)
{
    LushLifeUI *self = (LushLifeUI*)ui;
    if(!format)
    {
      float val = *(float*)buffer;
      switch(port_index)
      {
        case GAIN:
          self->mastergain->value(val);
          break;
        case DRY_GAIN:
          XYhandle::set_ffffltk_valuey((void*)self->drygp,val);
          break;
        case DRY_PAN:
          XYhandle::set_ffffltk_valuex((void*)self->drygp,val);
          break;
        case LFOSHAPE:
          self->shape->value(val);
          break;
        case SYNCLFO:
          self->sync->value(val);
          break;
        
        case ACTIVE0:
          self->activate0->value(val);
          break;
        case SHIFT0:
          XYhandle::set_ffffltk_valuey((void*)self->pd0,val*100);
          break;
        case SLFOA0:
          YBound::set_ffffltk_value((void*)self->pdyb0,val*100);
          break;
        case SLFOF0:
          self->pitchfreq0->value(val);
          break;
        case DELAY0:
          XYhandle::set_ffffltk_valuex((void*)self->pd0,val);
          break;
        case DLFOA0:
          XBound::set_ffffltk_value((void*)self->pdxb0,val);
          break;
        case DLFOF0:
          self->delayfreq0->value(val);
          break;
        case GAIN0:
          XYhandle::set_ffffltk_valuey((void*)self->gp0,val);
          break;
        case PAN0:
          XYhandle::set_ffffltk_valuex((void*)self->gp0,val);
          break;

        case ACTIVE1:
          self->activate1->value(val);
          break;
        case SHIFT1:
          XYhandle::set_ffffltk_valuey((void*)self->pd1,val*100);
          break;
        case SLFOA1:
          YBound::set_ffffltk_value((void*)self->pdyb1,val*100);
          break;
        case SLFOF1:
          self->pitchfreq1->value(val);
          break;
        case DELAY1:
          XYhandle::set_ffffltk_valuex((void*)self->pd1,val);
          break;
        case DLFOA1:
          XBound::set_ffffltk_value((void*)self->pdxb1,val);
          break;
        case DLFOF1:
          self->delayfreq1->value(val);
          break;
        case GAIN1:
          XYhandle::set_ffffltk_valuey((void*)self->gp1,val);
          break;
        case PAN1:
          XYhandle::set_ffffltk_valuex((void*)self->gp1,val);
          break;

        case ACTIVE2:
          self->activate2->value(val);
          break;
        case SHIFT2:
          XYhandle::set_ffffltk_valuey((void*)self->pd2,val*100);
          break;
        case SLFOA2:
          YBound::set_ffffltk_value((void*)self->pdyb2,val*100);
          break;
        case SLFOF2:
          self->pitchfreq2->value(val);
          break;
        case DELAY2:
          XYhandle::set_ffffltk_valuex((void*)self->pd2,val);
          break;
        case DLFOA2:
          XBound::set_ffffltk_value((void*)self->pdxb2,val);
          break;
        case DLFOF2:
          self->delayfreq2->value(val);
          break;
        case GAIN2:
          XYhandle::set_ffffltk_valuey((void*)self->gp2,val);
          break;
        case PAN2:
          XYhandle::set_ffffltk_valuex((void*)self->gp2,val);
          break;

        case ACTIVE3:
          self->activate3->value(val);
          break;
        case SHIFT3:
          XYhandle::set_ffffltk_valuey((void*)self->pd3,val*100);
          break;
        case SLFOA3:
          YBound::set_ffffltk_value((void*)self->pdyb3,val*100);
          break;
        case SLFOF3:
          self->pitchfreq3->value(val);
          break;
        case DELAY3:
          XYhandle::set_ffffltk_valuex((void*)self->pd3,val);
          break;
        case DLFOA3:
          XBound::set_ffffltk_value((void*)self->pdxb3,val);
          break;
        case DLFOF3:
          self->delayfreq3->value(val);
          break;
        case GAIN3:
          XYhandle::set_ffffltk_valuey((void*)self->gp3,val);
          break;
        case PAN3:
          XYhandle::set_ffffltk_valuex((void*)self->gp3,val);
          break;

        case ACTIVE4:
          self->activate4->value(val);
          break;
        case SHIFT4:
          XYhandle::set_ffffltk_valuey((void*)self->pd3,val*100);
          break;
        case SLFOA4:
          YBound::set_ffffltk_value((void*)self->pdyb4,val*100);
          break;
        case SLFOF4:
          self->pitchfreq4->value(val);
          break;
        case DELAY4:
          XYhandle::set_ffffltk_valuex((void*)self->pd4,val);
          break;
        case DLFOA4:
          XBound::set_ffffltk_value((void*)self->pdxb4,val);
          break;
        case DLFOF4:
          self->delayfreq4->value(val);
          break;
        case GAIN4:
          XYhandle::set_ffffltk_valuey((void*)self->gp4,val);
          break;
        case PAN4:
          XYhandle::set_ffffltk_valuex((void*)self->gp4,val);
          break;

        case ACTIVE5:
          self->activate5->value(val);
          break;
        case SHIFT5:
          XYhandle::set_ffffltk_valuey((void*)self->pd3,val*100);
          break;
        case SLFOA5:
          YBound::set_ffffltk_value((void*)self->pdyb5,val*100);
          break;
        case SLFOF5:
          self->pitchfreq5->value(val);
          break;
        case DELAY5:
          XYhandle::set_ffffltk_valuex((void*)self->pd5,val);
          break;
        case DLFOA5:
          XBound::set_ffffltk_value((void*)self->pdxb5,val);
          break;
        case DLFOF5:
          self->delayfreq5->value(val);
          break;
        case GAIN5:
          XYhandle::set_ffffltk_valuey((void*)self->gp5,val);
          break;
        case PAN5:
          XYhandle::set_ffffltk_valuex((void*)self->gp5,val);
          break;
      }//switch
    }//if float
}

static int
idle(LV2UI_Handle handle)
{
  LushLifeUI* self = (LushLifeUI*)handle;
  self->idle();
  
  return 0;
}

static int
resize_func(LV2UI_Feature_Handle handle, int w, int h)
{
  LushLifeUI* self = (LushLifeUI*)handle;
  self->ui->size(w,h);
  
  return 0;
}

static const LV2UI_Idle_Interface idle_iface = { idle };
static const LV2UI_Resize resize_ui = { 0, resize_func };

static const void*
extension_data(const char* uri)
{
  if (!strcmp(uri, LV2_UI__idleInterface))
  {
    return &idle_iface;
  }
  if (!strcmp(uri, LV2_UI__resize))
  {
    return &resize_ui;
  }
  return NULL;
}

static const LV2UI_Descriptor lushlifeUI_descriptor = {
    LUSHLIFEUI_URI,
    init_lushlifeUI,
    cleanup_lushlifeUI,
    lushlifeUI_port_event,
    extension_data
};

LV2_SYMBOL_EXPORT 
const LV2UI_Descriptor* lv2ui_descriptor(uint32_t index) 
{
    switch (index) {
    case 0:
        return &lushlifeUI_descriptor;
    default:
        return NULL;
    }
}
#endif
