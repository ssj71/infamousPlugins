#include "qsvgled.h"

qSVGLED::qSVGLED(QWidget *parent) :
    QWidget(parent)
{
    LEDoff = new QGraphicsSvgItem("defaultLEDOff.svg");
    LEDon = new QGraphicsSvgItem("defaultLEDOn.svg");
    lf = LEDoff->renderer()->defaultSize();
    ln = LEDon->renderer()->defaultSize();
    LEDon->setTransformOriginPoint(ln.width()/2,ln.height()/2);
    LEDoff->setTransformOriginPoint(lf.width()/2,lf.height()/2);
    view.setStyleSheet("background: transparent; border: none");

    myheight = ln.height();
    mywidth = ln.width();
    if (myheight<lf.height()) myheight = lf.height();
    if (mywidth<lf.width()) mywidth = lf.width();
    view.setDisabled(true);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene.addItem(LEDoff);
    scene.addItem(LEDon);
    view.setScene(&scene);
    view.setParent(this,Qt::FramelessWindowHint);
    this->setParent(parent,Qt::FramelessWindowHint);

    state = false;
    LEDon->setVisible(state);
}

qSVGLED::qSVGLED(QString offFile, QString onFile, QWidget *parent) :
    QWidget(parent)
{
    LEDoff = new QGraphicsSvgItem(offFile);
    LEDon = new QGraphicsSvgItem(onFile);
    lf = LEDoff->renderer()->defaultSize();
    ln = LEDon->renderer()->defaultSize();
    LEDon->setTransformOriginPoint(ln.width()/2,ln.height()/2);
    LEDoff->setTransformOriginPoint(lf.width()/2,lf.height()/2);
    view.setStyleSheet("background: transparent; border: none");

    myheight = ln.height();
    mywidth = ln.width();
    if (myheight<lf.height()) myheight = lf.height();
    if (mywidth<lf.width()) mywidth = lf.width();
    view.setDisabled(true);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene.addItem(LEDoff);
    scene.addItem(LEDon);
    view.setScene(&scene);
    view.setParent(this,Qt::FramelessWindowHint);
    this->setParent(parent,Qt::FramelessWindowHint);

    state = false;
    LEDon->setVisible(state);
}

void qSVGLED::resizeEvent(QResizeEvent *re)
{
    if (this->width()>this->height())
    {
        view.setFixedSize(this->width(),this->height());
        LEDon->setScale(this->height()/myheight);
        LEDoff->setScale(this->height()/myheight);
        view.centerOn(LEDon);
    }
    else
    {
        view.setFixedSize(this->width(),this->height());
        LEDon->setScale(this->width()/mywidth);
        LEDoff->setScale(this->width()/mywidth);
        view.centerOn(LEDon);
    }
    QWidget::resizeEvent(re);
}

void qSVGLED::toggle()
{
    state = !state;
    LEDon->setVisible(state);
    LEDon->setOpacity(1);
}


void qSVGLED::setState(bool newstate)
{
    state = newstate;
    LEDon->setVisible(state);
    LEDon->setOpacity(1);
}

void qSVGLED::setBrightness(qreal value)
{
    state = value;
    LEDon->setOpacity(value);
    LEDon->setVisible(true);
}
