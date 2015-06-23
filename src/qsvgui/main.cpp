#include <QtGui/QApplication>
#include "pedal.h"
#include "skin.h"
#include "QLCDNumber"
#include <QWidget>

#include <string.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Pedal w("skins/default/stompbox.svg",0);
//    w.AddControl("Dial" , "Level", 133, 295, 47, 47, "skins/default/blackKnob.svg", "skins/default/whiteNeedle.svg","","");
//    w.AddControl("Button", "On", 20, 21, 182, 111, "skins/default/blackButton.svg","skins/default/blackButtonPressed.svg","","");
//    w.AddControl("LED", "On", 106, 328, 11, 11, "skins/default/redLEDOff.svg", "skins/default/redLEDOn.svg","","");
//    w.AddControl("Dial", "Gain", 44, 295, 47, 47, "skins/default/blackKnob.svg", "skins/default/whiteNeedle.svg","","");
//    w.AddControl("Dial", "Low", 36, 244, 31, 31, "skins/default/blackKnob.svg", "skins/default/whiteNeedle.svg","","");
//    w.AddControl("Dial", "Mid", 98, 244, 31, 31, "skins/default/blackKnob.svg", "skins/default/whiteNeedle.svg","","");
//    w.AddControl("Dial", "High", 160, 244, 31, 31, "skins/default/blackKnob.svg", "skins/default/whiteNeedle.svg","","");
//    w.show();

////    Pedal l("skins/default/alienwah.svg",0);
////    l.AddControl( "Button", "On", 90, 57, 42, 37, "skins/default/stompButton2.svg", "","","");
////    l.AddControl( "LED", "On", 105, 319, 14, 14, "skins/default/blueLEDOff.svg", "skins/default/blueLEDOn.svg","","");
////    l.AddControl( "Dial", "Phase", 48, 130, 47, 47, "skins/default/blackKnob.svg", "skins/default/whiteNeedle.svg","","");
////    l.AddControl( "Dial", "Depth", 130, 130, 47, 47, "skins/default/blackKnob.svg", "skins/default/whiteNeedle.svg","","");
////    l.show();
//    Pedal l("skins/default/compressor.svg",0);
//    l.AddControl( "Button", "On", 92, 39, 38, 38, "skins/default/stompButton.svg", "","","");
//    l.AddControl( "LED", "On", 103, 262, 17, 17, "skins/default/greenLEDOff.svg", "skins/default/greenLEDOn.svg","","");
//    l.AddControl( "Dial", "A.Time", 19, 274, 71, 71, "skins/default/ivoryKnob.svg", "skins/default/ivoryNeedle.svg","","");
//    l.AddControl( "Dial", "Ratio", 133, 274, 71, 71, "skins/default/ivoryKnob.svg", "skins/default/ivoryNeedle.svg","","");
//    l.AddControl( "Dial", "Threshold", 19, 196, 71, 71, "skins/default/ivoryKnob.svg", "skins/default/ivoryNeedle.svg","","");
//    l.AddControl( "Dial", "Output", 133, 196, 71, 71, "skins/default/ivoryKnob.svg", "skins/default/ivoryNeedle.svg","","");
//    //l.AddControl("Meter","meter",10,10,25,250,"skins/default/greenLEDOff.svg","skins/default/yellowLEDOff.svg","skins/default/redLEDOff.svg","");
//    //l.AddControl( "LCD", "Name", 40, 40, 100, 30, "bla","","","");
//    l.show();

//    Pedal g("skins/default/eq.svg",0);
//    g.AddControl( "Slider", "31_Hz", 30,218,9,117, "skins/default/slot.svg", "skins/default/redSlide.svg","","");
//    g.AddControl( "Slider", "63_Hz", 53,218,9,117, "skins/default/slot.svg", "skins/default/redSlide.svg","","");
//    g.show();

    //LCDDisplay f(0,FALSE, LCDDigit::SMALL_RED);
    //f.setText("hello world:");
    //f.show();

    skin sk("skins/default.skn");
    //sk.loadSkin("skins/default.skn");
    int fx = 0;
    preview prv(&sk,fx,0);
    prv.show();
    Pedal w(&sk,fx,0);
    w.show();
    qSVGSlider barf("skins/default/redSlide.svg","skins/default/slot.svg",0);
    barf.show();
    QLCDNumber art;
    art.show();
    a.connect(&barf,SIGNAL(valueChanged(int)),&art,SLOT(display(int)));

    return a.exec();
}
