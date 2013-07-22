#include "qsvgdial.h"
#include "math.h"
#include "stdio.h"

qSVGDial::qSVGDial(QWidget *parent) :
    QDial(parent)
{
    knob = new QGraphicsSvgItem("defaultKnob.svg");
    needle = new QGraphicsSvgItem("defaultNeedle.svg");
    view.setStyleSheet("background: transparent; border: none");

    k = knob->renderer()->defaultSize();
    n = needle->renderer()->defaultSize();
    needle->setTransformOriginPoint(n.width()/2,n.height()/2);
    knob->setTransformOriginPoint(k.width()/2,k.height()/2);
    degPerPos = 340/(this->maximum() - this->minimum());
    middle = (this->maximum() - this->minimum())/2;
    mysize = k.width();
    if (mysize<n.width())  mysize = n.width();
    if (mysize<k.height()) mysize = k.height();
    if (mysize<n.height()) mysize = n.height();

    view.setDisabled(true);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene.addItem(knob);
    scene.addItem(needle);
    view.setScene(&scene);
    view.setParent(this,Qt::FramelessWindowHint);
    QObject::connect(this,SIGNAL(sliderMoved(int)),this,SLOT(rotateNeedle(int)));
}

qSVGDial::qSVGDial(QString knobFile, QString needleFile, QWidget *parent) :
    QDial(parent)
{
    knob = new QGraphicsSvgItem(knobFile);
    needle = new QGraphicsSvgItem(needleFile);
    view.setStyleSheet("background: transparent; border: none");
    k = knob->renderer()->defaultSize();
    n = needle->renderer()->defaultSize();
    needle->setTransformOriginPoint(n.width()/2,n.height()/2);
    knob->setTransformOriginPoint(k.width()/2,k.height()/2);
    if (k!=n)
        needle->setPos((k.width()-n.width())/2,(k.height()-n.height())/2);

    degPerPos = 340/(this->maximum() - this->minimum());
    middle = (this->maximum() - this->minimum())/2;
    mysize = k.width();
    if (mysize<n.width())  mysize = n.width();
    if (mysize<k.height()) mysize = k.height();
    if (mysize<n.height()) mysize = n.height();

    view.setDisabled(true);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene.addItem(knob);
    scene.addItem(needle);
    view.setScene(&scene);
    view.setParent(this,Qt::FramelessWindowHint);
    QObject::connect(this,SIGNAL(sliderMoved(int)),this,SLOT(rotateNeedle(int)));
}

qSVGDial::~qSVGDial()
{

}

void qSVGDial::rotateNeedle(int p)
{
    needle->setRotation((p - middle)*degPerPos);
    view.centerOn(knob);
}

void qSVGDial::resizeEvent(QResizeEvent *re)
{
    if (this->width()>this->height())
    {
        view.setFixedSize(this->height(),this->height());
        view.move((this->width()-this->height())/2,0);
        knob->setScale(this->height()/mysize);
        needle->setScale(this->height()/mysize);
        view.centerOn(knob);
    }
    else
    {
        view.setFixedSize(this->width(),this->width());
        view.move(0,(this->height()-this->width())/2);
        knob->setScale(this->width()/mysize);
        needle->setScale(this->width()/mysize);
        view.centerOn(knob);
    }
    QDial::resizeEvent(re);
}
void qSVGDial::paintEvent(QPaintEvent *pe)
{
}
