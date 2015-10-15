//g++ -g -Wall -fpermissive test_main.cxx -I ../src/EnvelopeFollower/build/ -I ../src/draw -I ../src/ffffltk/ -I ../src/EnvelopeFollower/ -lGL -lntk `pkg-config --cflags --libs cairo ntk` -o test_ui

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

//#include "test.h"
#include "lushlife_ui.h"

int main()
{
  //FancyUI a;// = new FancyUI;
  //EnvFollowerUI* a = new EnvFollowerUI();
  LushLifeUI a ;//= new EnvFollowerUI();
  //LushLifeUI *a = new LushLifeUI();

  //a.make_window();
  //a->ui->show();
  a.ui->show();
  
  Fl::run();
  
  //delete[] a;
  return 0;
}
