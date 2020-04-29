#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/x.H>

#include "hip2b_ui.h"
#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"

#define HIP2BUI_URI "http://ssj71.github.io/infamousPlugins/plugs.html#hip2b_ui"

static LV2UI_Handle init_hip2bUI(const struct LV2UI_Descriptor * descriptor,
		const char * plugin_uri,
		const char * bundle_path,
		LV2UI_Write_Function write_function,
		LV2UI_Controller controller,
		LV2UI_Widget * widget,
		const LV2_Feature * const * features) 
{
    if(strcmp(plugin_uri, HIP2B_URI) != 0)
    {
        return 0;
    }

    Hip2BUI* self = new Hip2BUI();
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

void cleanup_hip2bUI(LV2UI_Handle ui)
{
    Hip2BUI *self = (Hip2BUI*)ui;

    delete self->ui;
    delete self;
}

void hip2bUI_port_event(LV2UI_Handle ui, uint32_t port_index, uint32_t buffer_size, uint32_t format, const void * buffer)
{
    Hip2BUI *self = (Hip2BUI*)ui;
    if(!format)
    {
      float val = *(float*)buffer;
      switch(port_index)
      {
        case UPP:
          self->up->value(val);
	  break;
        case DOWNN:
          self->down->value(val);
	  break;
        case INGAIN:
          self->input->value(val);
	  break;
        case OUTGAIN:
          self->output->value(val);
	  break;
        case OCTAVE:
          self->octave->value(val);
	  break;
        case WETDRY:
          self->wetdry->value(val);
	  break;
      }
    }
}

static int
idle(LV2UI_Handle handle)
{
  Hip2BUI* self = (Hip2BUI*)handle;
  self->idle();
  
  return 0;
}

static int
resize_func(LV2UI_Feature_Handle handle, int w, int h)
{
  Hip2BUI* self = (Hip2BUI*)handle;
  if(self && w>0 && h>0)
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

static const LV2UI_Descriptor hip2bUI_descriptor = {
    HIP2BUI_URI,
    init_hip2bUI,
    cleanup_hip2bUI,
    hip2bUI_port_event,
    extension_data
};

LV2_SYMBOL_EXPORT 
const LV2UI_Descriptor* lv2ui_descriptor(uint32_t index) 
{
    switch (index) {
    case 0:
        return &hip2bUI_descriptor;
    default:
        return NULL;
    }
}
