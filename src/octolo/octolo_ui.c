//spencer jackson
//octolo and stereoctolo UIs

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tikloo/tk.h"
#include"octolo.h"
#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"

#define OCTOLO_UI_URI "http://ssj71.github.io/infamousPlugins/plugs.html#octolo_ui"

typedef struct 
{
    LV2UI_Write_Function write_function;
    LV2UI_Controller controller;
}baggage_t;

void setup_octolo_ui(tk_t tk)
{
    tk_addaDial(tk,10,10,50,50,0,1,0);
}

static LV2UI_Handle init_octolo_ui(
    const struct _LV2UI_Descriptor * descriptor,
    const char * plugin_uri,
    const char * bundle_path,
    LV2UI_Write_Function write_function,
    LV2UI_Controller controller,
    LV2UI_Widget * widget,
    const LV2_Feature * const * features
    ) 
{
    tk_t tk;
    baggage_t* baggage;
    if(strcmp(plugin_uri, OCTOLO_URI) != 0)
    {
        return 0;
    }

    intptr_t parentWindow = 0;
    LV2UI_Resize* resize = NULL;
    for (int i = 0; features[i]; ++i)
    {
        if (!strcmp(features[i]->URI, LV2_UI__parent)) 
        {
           parentWindow = (intptr_t)features[i]->data;
        }
        else if (!strcmp(features[i]->URI, LV2_UI__resize)) 
        {
           resize = (LV2UI_Resize*)features[i]->data;
        }
    }
    if(!parentWindow) return 0;

    tk = tk_gimmeaTiKloo( 250, //w
                          444, //h
                          (char*)"the infamous octolo", //title
                          parentWindow); //parent

    if(!tk) return 0;
    baggage = (baggage_t*)malloc(sizeof(baggage_t));
    tk->user[0] = baggage;

    baggage->controller = controller;
    baggage->write_function = write_function;

    if (resize)
    {
        resize->ui_resize(resize->handle, tk->w[0], tk->h[0]);
    }
    //TODO: UI specific setup 

    *widget = (LV2UI_Widget)tk_embedit(tk);

    return (LV2UI_Handle)tk;
}

void cleanup_octolo_ui(LV2UI_Handle handle)
{
    tk_t tk = (tk_t)handle;
    free(tk->user[0]);
    tk_cleanup(tk);
}

void octolo_ui_port_event(LV2UI_Handle ui, uint32_t port_index, uint32_t buffer_size, uint32_t format, const void * buffer)
{
}

static int idle(LV2UI_Handle handle)
{
    tk_t tk = (tk_t)handle;
    tk_idle(tk);
    return 0;
}
static const LV2UI_Idle_Interface idle_iface = { idle };

static const void*
extension_data(const char* uri)
{
  if (!strcmp(uri, LV2_UI__idleInterface))
  {
    return &idle_iface;
  }
  return NULL;
}

static const LV2UI_Descriptor octoloUI_descriptor = {
    OCTOLO_UI_URI,
    init_octolo_ui,
    cleanup_octolo_ui,
    octolo_ui_port_event,
    extension_data
};

LV2_SYMBOL_EXPORT 
const LV2UI_Descriptor* lv2ui_descriptor(uint32_t index) 
{
    switch (index) {
    case 0:
        return &octoloUI_descriptor;
    default:
        return NULL;
    }
}
