#ifndef SKIN_H
#define SKIN_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include "globals.h"

//class dialskin
//{
//public:
//    QString name;
//    int x,y,w,h;
//    QString knob, needle, overlay;
//    //dialskin();
//    //~dialskin();
//};

//class buttonskin
//{
//public:
//    QString name;
//    int x,y,w,h;
//    QString button, pressed, overlay;
//    //buttonskin();
//    //~buttonskin();
//};

//class sliderskin
//{
//public:
//    QString name;
//    int x,y,w,h;
//    QString slot, slide, overlay;
//    //sliderskin();
//    //~sliderskin();
//};

//class ledskin
//{
//public:
//    QString name;
//    int x,y,w,h;
//    QString on, off, overlay;
//    //ledskin();
//    //~ledskin();
//};

class controlskin
{
public:
    controlskin();
    QString type;
    QString parameter;
    int x,y,w,h,theta;
    QString filename[NUM_SVG_FILES];//this allows widgets of up to 4 files
};

class uiskin
{
public:
    QString name;
    QString file;
    bool blank, blankcontrols;
    int controls;
    std::vector<controlskin> control;//this allows up to 50 widgets in each pedal which seems really arbitrary. Lets fix it with an Malloc
    controlskin* addControl();
    void loadSkin(QString skinFile, QString name);
    uiskin();
    uiskin(QString skinFile, QString name);
    ~uiskin();
};

class skin
{
public:
    skin();
    skin(QString file);
    QString folder;
    uiskin effects[NUM_EFFECTS];
    uiskin main[5];
    void loadSkin(QString skinFile);

};

#endif // SKIN_H
