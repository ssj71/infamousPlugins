#include "qsvgui.h"
#include "math.h"


/*

  init_paramothing(paramtype param, widgettype type, Qwidget *thing)
  {
       switch(type)
       {
        case DIAL:

       }
       switch(param)
       {
       case GAIN:
            //integer type
            thing->setMinimum(-15);
            thing->setMaximum(3);
            thing->setValue(1);
            thing->setToolTip("GAIN 1")

       }

  }

  really need to make dial etc able to have better controls. Floats, logarithmic scale etc.
  */

qsvgui::qsvgui(QWidget *parent)
    : QWidget(parent)
{
    numControls = 0;
    bg = new QGraphicsSvgItem("stompbox.svg");
    view.setStyleSheet("background: transparent; border: none");
    p = bg->renderer()->defaultSize();
    bg->setTransformOriginPoint(p.width()/2,p.height()/2);

    myheight = p.height();
    mywidth = p.width();
    view.setDisabled(true);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene.addItem(bg);
    view.setScene(&scene);
    view.setParent(this,Qt::FramelessWindowHint);
}

qsvgui::qsvgui(QString boxFile, QWidget *parent) :
    QWidget(parent)
{
    numControls = 0;
    bg = new QGraphicsSvgItem(boxFile);
    view.setStyleSheet("background: transparent; border: none");
    p = bg->renderer()->defaultSize();
    bg->setTransformOriginPoint(p.width()/2,p.height()/2);

    myheight = p.height();
    mywidth = p.width();
    view.setDisabled(true);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene.addItem(bg);
    view.setScene(&scene);
    view.setParent(this,Qt::FramelessWindowHint);
}

qsvgui::qsvgui(skin *skinfile, QWidget *parent) :
    QWidget(parent)
{
    numControls = 0;
    effectNumber = effect;
    view.setStyleSheet("background: transparent; border: none");
//    box->setTransformOriginPoint(p.width()/2,p.height()/2);

    view.setDisabled(true);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view.setScene(&scene);
    view.setParent(this,Qt::FramelessWindowHint);
    LoadSkin(skinfile,effect);
}

qsvgui::~qsvgui()
{

}

void qsvgui::resizeEvent(QResizeEvent *re)
{
    view.setFixedSize(this->width(),this->height());
    //view.move((this->width()-this->height())/2,(this->width()-this->height())/2);
    if (this->width()/mywidth>this->height()/myheight)
    {
        scale = this->height()/myheight;
    }
    else
    {
        scale = this->width()/mywidth;
    }
    bg->setScale(scale);
    view.centerOn(bg);
    //QWidget::resizeEvent(re);
    QRect v = PedalPosition();
    QRect cpos;
    for(int i = 0; i<numControls; i++)
    {
        cpos = ctrlPos[i];
        controls[i]->setGeometry(v.x()+cpos.x()*scale,v.y()+cpos.y()*scale,cpos.width()*scale,cpos.height()*scale);
    }
}

int qsvgui::LoadSkin(skin *currentskin, int effect)
{
    int n;
    QSize p;
    controlskin *ctl;
    effectskin fx = currentskin->effects[effect];
    bg = new QGraphicsSvgItem(fxfile);
    p = bg->renderer()->defaultSize();

    bg->setTransformOriginPoint(p.width()/2,p.height()/2);
    scene.addItem(bg);
    view.centerOn(bg);

    myheight = p.height();
    mywidth = p.width();

    for (int i = 0;i<fx.controls;i++)
    {
        ctl = fx.control[i];
        this->AddControl(ctl->type,ctl->parameter,ctl->x,ctl->y,ctl->w,ctl->h,ctl->filename[0],ctl->filename[1],ctl->filename[2],ctl->filename[3]);
    }
}

int qsvgui::LoadSkin(QString skinfile, QString name)
{
    int n;
    QSize p;

/*    for (int i = 0;i<fx.controls;i++)
    {
        ctl = fx.control[i];
        this->AddControl(ctl->type,ctl->parameter,ctl->x,ctl->y,ctl->w,ctl->h,ctl->filename[0],ctl->filename[1],ctl->filename[2],ctl->filename[3]);
    }
*/
    int l, theta, lncntr = 0;
    QString tmp;
    QString previousFiles[4] = {"","","",""};
    QString currentFiles[4] = {"","","",""};
    QFile file(skinfile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             return;
    folder = skinfile.remove(".skn",Qt::CaseInsensitive)+"/";

    QTextStream in(&file);
    QString line, type, param;
    QStringList word;
    QRect dimensions;


    while (!in.atEnd())// go till eof
    {
        lncntr++;
        line = in.readLine().section(';',0,0);
        word = line.split(",",QString::SkipEmptyParts,Qt::CaseInsensitive);
        l = word.length();
        if (word.at(0) == name)//if matches UI def.
        {
            //load background
            tmp = folder + word.at(1).remove(0,1);
            bg = new QGraphicsSvgItem(tmp);
            p = bg->renderer()->defaultSize();

            bg->setTransformOriginPoint(p.width()/2,p.height()/2);
            scene.addItem(bg);
            view.centerOn(bg);

            myheight = p.height();
            mywidth = p.width();


            lncntr++;
            line = in.readLine().section(';',0,0);
            word = line.split(",",QString::SkipEmptyParts,Qt::CaseInsensitive);
            l = word.length();

            for(int i=0; l>0; i++)//read until blank line
            {
                type = word.at(0);
                tmp = word.at(1);
                param = tmp.remove(0,1);
                dimensions.setX(word.at(2).toInt());
                dimensions.setY(word.at(3).toInt());
                dimensions.setWidth(word.at(4).toInt());
                dimensions.setHeight(word.at(5).toInt());
                if(word.at(6).toInt() == 0 && word.at(6).toLower().endsWith(".svg"))
                {//no theta (rotation)
                    theta = 0;
                    if (word.at(6).isEmpty())
                    {
                        for (int j=0;j<4;j++)
                            currentFiles[j] = previousFiles[j];//if no files specified presume previous
                    }
                    else
                    {
                        for (int j=6;j<l;j++)
                        {
                            tmp = word.at(j);
                            currentFiles[j-6] = previousFiles[j-6] = folder + tmp.remove(0,1);
                        }
                    }
                }
                else
                {//theta
                    theta = word.at(6).toInt();
                    if (word.at(7).isEmpty())
                    {
                        for (int j=0;j<4;j++)
                            currentctl->filename[j] = previousFiles[j];//if no files specified presume previous
                    }
                    else
                    {
                        for (int j=7;j<l;j++)
                        {
                            tmp = word.at(j);
                            currentctl->filename[j-7] = previousFiles[j-7] = folder + tmp.remove(0,1);
                        }
                    }
                }

                //now all the data is loaded, lets add the control
                if(this->AddControl(type,param,dimensions.x,dimensions.y,dimensions.w,dimensions.h,theta,ctl->filename[0],ctl->filename[1],ctl->filename[2],ctl->filename[3]) != 0)
                {//error

                }


                lncntr++;
                line = in.readLine().section(';',0,0);
                word = line.split(",",QString::SkipEmptyParts,Qt::CaseInsensitive);
                l = word.length();
            }
            break;//don't finish file, we have what we need
        }

    }

}

int qsvgui::AddControl(QString type, QString param, int x, int y, int w, int h, int theta, QString file1, QString file2, QString file3, QString file4)
{
    QWidget* control;
    if (type.toLower() == "dial")
    {
        if (!file2.isEmpty())
            control = new qSVGDial(file1,file2,this);
        else
            control = new qSVGDial(this);
    }
    else if (type.toLower() == "button")
    {
        if (!file2.isEmpty())
            control = new qSVGButton(file1,file2,this);
        else if (!file1.isEmpty())
            control = new qSVGButton(file1,this);
        else
            control = new qSVGButton(this);
    }
    else if (type.toLower() == "toggle")
    {
        qSVGButton *temp;
        if (!file2.isEmpty())
            temp = new qSVGButton(file1,file2,this);
        else if (!file1.isEmpty())
            temp = new qSVGButton(file1,this);
        else
            temp = new qSVGButton(this);
        temp->setCheckable(true);
        control = temp;
    }
    else if (type.toLower() == "slider")
    {
        if (!file2.isEmpty())
            control = new qSVGSlider(file1,file2,this);
        else if (!file1.isEmpty())
            control = new qSVGSlider(file1,this);
        else
            control = new qSVGSlider(this);
    }
    else if (type.toLower() == "led")
    {
        if (!file2.isEmpty())
            control = new qSVGLED(file1,file2,this);
        else
            control = new qSVGLED(this);
        for (int i=0;i<numControls;i++)
        {
            if (controls[i]->toolTip().toLower() == param.toLower())
                QObject::connect(controls[i],SIGNAL(clicked()),control, SLOT(toggle()));
        }
    }
    else if (type.toLower() == "meter")
    {
        if (!file3.isEmpty())
        {
            QString on1, on2, on3;
            on1 = file1.replace("Off","On");
            on2 = file2.replace("Off","On");
            on3 = file3.replace("Off","On");
            control = new qSVGMeter(file1,on1,file2,on2,file3,on3,this);
//            for (int i=0;i<numControls;i++)
//            {
//                if (controls[i]->toolTip().toLower() == "output")
//                    QObject::connect(controls[i],SIGNAL(valueChanged(int)),control, SLOT(setMeter(int)));
//            }
        }
    }else if (type.toLower() == "lcd")
    {
        LCDDisplay* f;
        if (!file2.isEmpty())
        {
            if (file1.toLower() == "large")
                f  = new LCDDisplay(this, true, file2);
            else
                f  = new LCDDisplay(this, false, file2);
        }
        else
        {
            f  = new LCDDisplay(this, true, file1);
        }
        control = f;
        f->show();
    }
    control->setToolTip(param);
    //ctrlPos[numControls] = QRect(x,myheight-y-h,w,h);
    //controls[numControls] = control;
    //numControls++;
    this->controls.push_back(control);
    return 0;//control;
}

QRect qsvgui::PedalPosition()
{
    QRect mypos;
    mypos.setWidth(mywidth*scale);
    mypos.setHeight(myheight*scale);
    mypos.setX((this->width()-mypos.width())/2);
    mypos.setY((this->height()-mypos.height())/2);
    return mypos;
}

/*
QString number2name(int number)
{
    switch(number)
    {

         case 0: //EQ1
            return "Lineal_EQ";
            break;

         case 1://Compressor
            return "Compressor";
            break;

         case 2://Distorsion
            return "Distorsion";
            break;

         case 3://Overdrive
            return "Overdrive";
            break;

         case 4://Echo
            return "Echo";
            break;

         case 5://Chorus
            return "Chorus";
            break;

         case 6://Phaser
            return "Phaser";
            break;

         case 7://Flanger
            return "Flanger";
            break;

        case 8://Reverb
            return "Reverb";
            break;

         case 9://EQ2
            return "EQ2";
            break;

         case 10://WahWah
            return "WahWah";
            break;

         case 11://AlienWah
            return "AlienWah";
            break;

         case 12://Cabinet
            return "Cabinet";
            break;

         case 13://Pan
            return "Pan";
            break;

         case 14://Har
            return "Har";
            break;

         case 15://MsicalDelay
            return "MsicalDelay";
            break;

         case 16://NoiseGate
            return "NoiseGate";
            break;

         case 17://NewDist
            return "NewDist";
            break;

         case 18://APhaser
            return "APhaser";
            break;

         case 19://Valve
            return "Valve";
            break;

         case 20://Dual_Flange
            return "Dual_Flange";
            break;

         case 21:// Ring
            return "Ring";
            break;

         case 22:// Exciter
            return "Exciter";
            break;

         case 23://MBDist
            return "MBDist";
            break;

         case 24://Arpie
            return "Arpie";
            break;

         case 25://Expander
            return "Expander";
            break;

         case 26://Shuffle
            return "Shuffle";
            break;

         case 27://Synthfilter
            return "Synthfilter";
            break;

         case 28://VaryBand
            return "VaryBand";
            break;

         case 29://Convolotron
            return "Convolotron";
            break;

         case 30://Looper
            return "Looper";
            break;

         case 31://RyanWah
            return "RyanWah";
            break;

         case 32:// RBEcho
            return "RBEcho";
            break;

         case 33:// CoilCrafter
            return "CoilCrafter";
            break;

         case 34://ShelfBoost
            return "ShelfBoost";
            break;

         case 35://Vocoder
            return "Vocoder";
            break;

         case 36://Sustainer
            return "Sustainer";
            break;

        case 37://Sequence
            return "Sequence";
            break;

        case 38://Shifter
            return "Shifter";
            break;

        case 39://StompBox
            return "StompBox";
            break;

        case 40://Reverbtron
            return "Reverbtron";
            break;

        case 41://Echotron
            return "Echotron";
            break;

        case 42://StereoHarm
            return "StereoHarm";
            break;

        case 43://CompBand
            return "CompBand";
            break;

        case 44://Opticaltrem
            return "Opticaltrem";
            break;

        case 45://Vibe
            return "Vibe";
            break;

        case 46://Infinity
            return "Infinity";
            break;
     }

}


  Lineal_EQ Compressor Distortion Overdrive Echo Chorus Phaser Analog Phaser Flanger Reverb Parametric EQ Cabinet Emulation AutoPan/Stereo Expander Harmonizer Musical Delay Noise Gate WahWah AlienWah Derelict Valve Dual Flange Ring Exciter DistBand Arpie Expander Shuffle Synthfilter VaryBand Convolotron Looper MuTroMojo Echoverse CoilCrafter ShelfBoost Vocoder Sustainer Sequence Shifter StompBox Reverbtron Echotron StereoHarm CompBand Opticaltrem Vibe
*/
/*
int name2number(QString name)
{
    switch(name.toLower())
    {
        case "lineal_eq": //EQ1
           return 0;
           break;

        case "compressor"://Compressor
           return 1;
           break;

        case "distorsion"://Distorsion
           return 2;
           break;

        case "overdrive"://Overdrive
           return 3;
           break;

        case "echo"://Echo
           return 4;
           break;

        case "chorus"://Chorus
           return 5;
           break;

        case "phaser"://Phaser
           return 6;
           break;

        case "flanger"://Flanger
           return 7;
           break;

        case "reverb"://Reverb
           return 8;
           break;

        case "eq2"://EQ2
           return 9;
           break;

        case "wahwah"://WahWah
           return 10;
           break;

        case "alienwah"://AlienWah
           return 11;
           break;

        case "cabinet"://Cabinet
           return 12;
           break;

        case "pan"://Pan
           return 13;
           break;

        case "har"://Har
           return 14;
           break;

        case "msicaldelay"://MsicalDelay
           return 15;
           break;

        case "noisegate"://NoiseGate
           return 16;
           break;

        case "newdist"://NewDist, derelict?
           return 17;
           break;

        case "aphaser"://APhaser
           return 18;
           break;

        case "valve"://Valve
           return 19;
           break;

        case "dual_flange"://Dual_Flange
           return 20;
           break;

        case "ring":// Ring
           return 21;
           break;

        case "exciter":// Exciter
           return 22;
           break;

        case "mbdist"://MBDist
           return 23;
           break;

        case "arpie"://Arpie
           return 24;
           break;

        case "expander"://Expander
           return 25;
           break;

        case "shuffle"://Shuffle
           return 26;
           break;

        case "synthfilter"://Synthfilter
           return 27;
           break;

        case "varyband"://VaryBand
           return 28;
           break;

        case "convolotron"://Convolotron
           return 29;
           break;

        case "looper"://Looper
           return 30;
           break;

        case "ryanwah"://RyanWah
           return 31;
           break;

        case "rbecho":// RBEcho
           return 32;
           break;

        case "coilcrafter":// CoilCrafter
           return 33;
           break;

        case "shelfboost"://ShelfBoost
           return 34;
           break;

        case "vocoder"://Vocoder
           return 35;
           break;

        case "sustainer"://Sustainer
           return 36;
           break;

        case "sequence"://Sequence
           return 37;
           break;

        case "shifter"://Shifter
           return 38;
           break;

        case "stompbox"://StompBox
           return 39;
           break;

        case "reverbtron"://Reverbtron
           return 40;
           break;

        case "echotron"://Echotron
           return 41;
           break;

        case "stereoharm"://StereoHarm
           return 42;
           break;

        case "compband"://CompBand
           return 43;
           break;

        case "opticaltrem"://Opticaltrem
           return 44;
           break;

        case "vibe"://Vibe
           return 45;
           break;

        case "infinity"://Infinity
           return 46;
           break;

        default:
            return -1;
    }
}
*/
