#include "qsvgmeter.h"

qSVGMeter::qSVGMeter(QString greenOffFile, QString greenOnFile, QString yellowOffFile, QString yellowOnFile, QString redOffFile, QString redOnFile, QWidget *parent) :
    QWidget(parent)
{
    vertical = true;
    int h = this->height()/10;
    int y = this->height()-h;
    int w = this->width();
    for(int i=0;i<5;i++)
    {
        led[i] = new qSVGLED(greenOffFile,greenOnFile,this);
        led[i]->setGeometry(0,y-h*i,w,h);
    }
    for(int i=5;i<8;i++)
    {
        led[i] = new qSVGLED(yellowOffFile,yellowOnFile,this);
        led[i]->setGeometry(0,y-h*i,w,h);
    }
    for(int i=8;i<10;i++)
    {
        led[i] = new qSVGLED(redOffFile,redOnFile,this);
        led[i]->setGeometry(0,y-h*i,w,h);
    }
}


void qSVGMeter::setOrientation(Qt::Orientation o)
{
    if (o == Qt::Horizontal)
        vertical = false;
    else
        vertical = true;
}

void qSVGMeter::setMeter(int value)
{
    int i;
    for(i=0;i<(int)(value/10);i++)
        led[i]->setState(true);
    led[i++]->setBrightness((double)value/10 - i);
    for(;i<10;i++)
        led[i]->setState(false);
}

void qSVGMeter::setMeter(double value)
{
    int i;
    for(i=0;i<(int)value/10;i++)
        led[i]->setState(true);
    led[i++]->setBrightness(value/10 - i);
    for(;i<10;i++)
        led[i]->setState(false);
}

void qSVGMeter::resizeEvent(QResizeEvent *re)
{
    if (vertical == false)
    {
        int h = this->height();
        int w = this->width()/10;
        for(int i=0;i<10;i++)
        {
            led[i]->setGeometry(w*i,0,w,h);
        }
    }
    else
    {
        int h = this->height()/10;
        int y = this->height()-h;
        int w = this->width();
        for(int i=0;i<10;i++)
        {
            led[i]->setGeometry(0,y-h*i,w,h);
        }
    }
}
