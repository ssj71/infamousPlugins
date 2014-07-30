

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include "test.h"

int main()
{
  FancyUI a;// = new FancyUI;

  a.make_window();
  
  Fl::run();
  
  return 0;
}
