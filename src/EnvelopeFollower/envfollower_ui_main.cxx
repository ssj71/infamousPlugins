#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/x.H>

#include "envfollower_ui.h"
#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"

#define ENVFOLLOWERUI_URI "http://infamousplugins.sourceforge.net/plugs.html#envfollower_ui"

static LV2UI_Handle init_envfollowerUI(const struct _LV2UI_Descriptor * descriptor,
		const char * plugin_uri,
		const char * bundle_path,
		LV2UI_Write_Function write_function,
		LV2UI_Controller controller,
		LV2UI_Widget * widget,
		const LV2_Feature * const * features) 
{
    if(strcmp(plugin_uri, ENVFOLLOWER_URI) != 0)
    {
        return 0;
    }

    EnvFollowerUI* self = new EnvFollowerUI();
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

    return (LV2UI_Handle)self;
}

void cleanup_envfollowerUI(LV2UI_Handle ui)
{
    EnvFollowerUI *self = (EnvFollowerUI*)ui;

    delete self;
}

void envfollowerUI_port_event(LV2UI_Handle ui, uint32_t port_index, uint32_t buffer_size, uint32_t format, const void * buffer)
{
    EnvFollowerUI *self = (EnvFollowerUI*)ui;
    if(!format)
    {
      float val = *(float*)buffer;
      char str[5];
      switch(port_index)
      {
        case PEAKRMS:
          self->peakrms->value(val);
	  break;
        case ATIME:
          self->attack->value(val);
	  break;
        case DTIME:
          self->decay->value(val);
	  break;
        case THRESHOLD:
          self->threshold->value(val);
	  break;
        case SATURATION:
          self->saturation->value(val);
	  break;
        case CHANNEL:
          self->channel->value(val);
	  break;
        case CONTROL_NO:
          self->cc->value(val);
	  break;
        case MINV:
          self->min->value(val);
	  break;
        case MAXV:
          self->max->value(val);
	  break;
        case REVERSE:
          self->reverse->value(val);
	  break;

        case CTL_IN:
          sprintf(str,"%1.2f",val);
          self->inLCD->copy_label(str);
          self->inScope->push_val(val);
	  break;
        case CTL_OUT:
          sprintf(str,"%3.0f",val*127.0);
          self->outLCD->copy_label(str);
          self->outScope->push_val(val);
	  break;
      }
    }
}

static int
idle(LV2UI_Handle handle)
{
  EnvFollowerUI* self = (EnvFollowerUI*)handle;
  self->idle();
  
  return 0;
}

static int
resize_func(LV2UI_Feature_Handle handle, int w, int h)
{
  EnvFollowerUI* self = (EnvFollowerUI*)handle;
  //self->ui->size(w,h);
  
  return 0;
}

static const LV2UI_Idle_Interface idle_iface = { idle };
static const LV2UI_Resize resize_ui = { 0, resize_func };//ideally 1st member would be the EnvFollowerUI instance

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

static const LV2UI_Descriptor envfollowerUI_descriptor = {
    ENVFOLLOWERUI_URI,
    init_envfollowerUI,
    cleanup_envfollowerUI,
    envfollowerUI_port_event,
    extension_data
};

LV2_SYMBOL_EXPORT 
const LV2UI_Descriptor* lv2ui_descriptor(uint32_t index) 
{
    switch (index) {
    case 0:
        return &envfollowerUI_descriptor;
    default:
        return NULL;
    }
}
