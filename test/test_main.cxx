//g++ -g -Wall -fpermissive test_main.cxx -I ../src/EnvelopeFollower/build/ -I ../src/draw -I ../src/ffffltk/ -I ../src/EnvelopeFollower/ -lGL -lntk `pkg-config --cflags --libs cairo ntk` -o test_ui

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

//#include "test.h"
#include "envfollower_ui.h"

int main()
{
  //FancyUI a;// = new FancyUI;
  //EnvFollowerUI* a = new EnvFollowerUI();
  EnvFollowerUI a ;//= new EnvFollowerUI();

  //a.make_window();
  //a->ui->show();
  a.ui->show();
  
  Fl::run();
  
  //delete[] a;
  return 0;
}
