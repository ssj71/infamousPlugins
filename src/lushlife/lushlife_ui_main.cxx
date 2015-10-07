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
    CaSynthUI *self = (CaSynthUI*)ui;

    delete self->ui;
    delete self;
}

void lushlifeUI_port_event(LV2UI_Handle ui, uint32_t port_index, uint32_t buffer_size, uint32_t format, const void * buffer)
{
    CaSynthUI *self = (CaSynthUI*)ui;
    if(!format)
    {
      float val = *(float*)buffer;
      switch(port_index)
      {
        case GAIN:
          self->mastergain->value(val);
          break;
        case DRY_GAIN:
          self->drygp->Yv.value(val);
          break;
        case DRY_PAN:
          self->drygp->Xv.value(val);
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
          self->harmwidth->value(val);
          break;
        case SLFOA0:
          self->a->value(val);
          break;
        case SLFOF0:
          self->d->value(val);
          break;
        case DELAY0:
          self->b->value(val);
          break;
        case DLFOA0:
          self->sw->value(val);
          break;
        case DLFOF0:
          self->su->value(val);
          break;
        case GAIN0:
          self->r->value(val);
          break;
        case PAN0:
          self->amwave->value(val);
          break;
      }//switch
    }//if float
}

static int
idle(LV2UI_Handle handle)
{
  CaSynthUI* self = (CaSynthUI*)handle;
  self->idle();
  
  return 0;
}

static int
resize_func(LV2UI_Feature_Handle handle, int w, int h)
{
  CaSynthUI* self = (CaSynthUI*)handle;
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
