

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include "stuckUItest.h"

int main()
{
  StuckUI a;

  a.show();
  
  Fl::run();
  
  return 0;
}
