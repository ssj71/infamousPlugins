#include "skin.h"

int name2number(QString name);

controlskin::controlskin()
{
    for (int i=0;i<4;i++)
        filename[i] = "";
}

uiskin::uiskin()
{
    blank = true;
    blankcontrols  = true;
    controls = 0;
}

uiskin::~uiskin()
{
   // for(int i=controls-1;i>=0;i--)
   //     delete control[i];
}

controlskin* uiskin::addControl()
{
    controlskin *c = new controlskin;
    control[controls] = c;
    controls++;
    return c;
}

skin::skin()
{

}

skin::skin(QString file)
{
    loadSkin(file);
}

void skin::loadSkin(QString skinFileName)
{
    int l,fxnum=0;
    QString tmp;
    effectskin *currentfx;
    controlskin *currentctl;
    QString previousFiles[4] = {"","","",""};
    QFile file(skinFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             return;
    folder = skinFileName.remove(".skn",Qt::CaseInsensitive)+"/";

    QTextStream in(&file);
    QString line;
    QStringList word;

    while (!in.atEnd())// go till eof
    {
        line = in.readLine().section(';',0,0);
        word = line.split(",",QString::SkipEmptyParts,Qt::CaseInsensitive);
        l = word.length();
        //int i = name2number(word.at(0));
        if (name2number(word.at(0))!=-1)//if new effect
        {
            currentfx = &effects[fxnum++];
            currentfx->blank = false;
            currentfx->name = word.at(0);
            tmp = word.at(1);
            currentfx->file = folder + tmp.remove(0,1);

            line = in.readLine().section(';',0,0);
            word = line.split(",",QString::SkipEmptyParts,Qt::CaseInsensitive);
            l = word.length();

            for(int i=0; l>0; i++)//read until blank line
            {
                currentctl = currentfx->addControl();
                currentctl->type = word.at(0);
                tmp = word.at(1);
                currentctl->parameter = tmp.remove(0,1);
                currentctl->x = word.at(2).toInt();
                currentctl->y = word.at(3).toInt();
                currentctl->w = word.at(4).toInt();
                currentctl->h = word.at(5).toInt();
                if (word.at(6).isEmpty())
                {
                    for (int j=0;j<4;j++)
                        currentctl->filename[j] = previousFiles[j];//if no files specified presume previous
                }
                else
                {
                    for (int j=6;j<l;j++)
                    {
                        tmp = word.at(j);
                        currentctl->filename[j-6] = previousFiles[j-6] = folder + tmp.remove(0,1);
                    }
                }

                line = in.readLine().section(';',0,0);
                word = line.split(",",QString::SkipEmptyParts,Qt::CaseInsensitive);
                l = word.length();
            }
        }

    }

}


int name2number(QString name)
{
    QString n = name.toLower().remove(" ",Qt::CaseInsensitive).remove("_",Qt::CaseInsensitive);//make all lowercase and remove spaces

    if (n=="linealeq" || n=="eq1" || n=="eq" || n=="eqlineal") //EQ1
       return 0;

    else if (n=="compressor")//Compressor
       return 1;

    else if (n=="distorsion" || n=="distortion")//Distortion
       return 2;

    else if (n=="overdrive")//Overdrive
       return 3;

    else if (n=="echo")//Echo
       return 4;

    else if (n=="chorus")//Chorus
       return 5;

    else if (n=="phaser")//Phaser
       return 6;

    else if (n=="flanger")//Flanger
       return 7;

    else if (n=="reverb")//Reverb
       return 8;

    else if (n=="eq2" || n=="parametriceq")//EQ2
       return 9;

    else if (n=="wahwah")//WahWah
       return 10;

    else if (n=="alienwah")//AlienWah
       return 11;

    else if (n=="cabinet")//Cabinet
       return 12;

    else if (n=="pan")//Pan
       return 13;

    else if (n=="har" || n=="harmonizer")//Har
       return 14;

    else if (n=="msicaldelay" || n=="musicaldelay")//MsicalDelay
       return 15;

    else if (n=="noisegate")//NoiseGate
       return 16;

    else if (n=="newdist" || n=="derelict")//NewDist, derelict
       return 17;

    else if (n=="aphaser" || n=="analogphaser")//APhaser
       return 18;

    else if (n=="valve")//Valve
       return 19;

    else if (n=="dualflange")//Dual_Flange
       return 20;

    else if (n=="ring")// Ring
       return 21;

    else if (n=="exciter")// Exciter
       return 22;

    else if (n=="mbdist" || n=="distband")//MBDist?
       return 23;

    else if (n=="arpie")//Arpie
       return 24;

    else if (n=="expander")//Expander
       return 25;

    else if (n=="shuffle")//Shuffle
       return 26;

    else if (n=="synthfilter")//Synthfilter
       return 27;

    else if (n=="varyband")//VaryBand
       return 28;

    else if (n=="convolotron")//Convolotron
       return 29;

    else if (n=="looper")//Looper
       return 30;

    else if (n=="ryanwah" || n=="mutromojo")//RyanWah ?
       return 31;

    else if (n=="rbecho" || n=="echoverse")// RBEcho?
       return 32;

    else if (n=="coilcrafter")// CoilCrafter
       return 33;

    else if (n=="shelfboost")//ShelfBoost
       return 34;

    else if (n=="vocoder")//Vocoder
       return 35;

    else if (n=="sustainer")//Sustainer
       return 36;

    else if (n=="sequence")//Sequence
       return 37;

    else if (n=="shifter")//Shifter
       return 38;

    else if (n=="stompbox")//StompBox
       return 39;

    else if (n=="reverbtron")//Reverbtron
       return 40;

    else if (n=="echotron")//Echotron
       return 41;

    else if (n=="stereoharm")//StereoHarm
       return 42;

    else if (n=="compband")//CompBand
       return 43;

    else if (n=="opticaltrem")//Opticaltrem
       return 44;

    else if (n=="vibe")//Vibe
       return 45;

    else if (n=="infinity")//Infinity
       return 46;

    else
        return -1;

}
