#include "qsvgslider.h"

qSVGSlider::qSVGSlider(QWidget *parent)
{
    slide = new QGraphicsSvgItem("defaultSlide.svg");
    slot = new QGraphicsSvgItem("defaultSlot.svg");
    b = slide->renderer()->defaultSize();
    s = slot->renderer()->defaultSize();
    slide->setTransformOriginPoint(b.width()/2,b.height()/2);
    slot->setTransformOriginPoint(s.width()/2,s.height()/2);
    view.setStyleSheet("background: transparent; border: none");

    myheight = b.height();
    mywidth = b.width();
    if (myheight<s.height()) myheight = s.height();
    if (mywidth<s.width()) mywidth = s.width();

    view.setDisabled(true);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene.addItem(slot);
    scene.addItem(slide);
    view.setScene(&scene);
    view.setParent(this,Qt::FramelessWindowHint);
    this->setParent(parent);
}

qSVGSlider::qSVGSlider(QString slideFile, QWidget *parent)
{
    slide = new QGraphicsSvgItem(slideFile);
    slot = new QGraphicsSvgItem("defaultSlot.svg");
    b = slide->renderer()->defaultSize();
    s = slot->renderer()->defaultSize();
    slide->setTransformOriginPoint(b.width()/2,b.height()/2);
    slot->setTransformOriginPoint(s.width()/2,s.height()/2);
    view.setStyleSheet("background: transparent; border: none");

    myheight = b.height();
    mywidth = b.width();
    if (myheight<s.height()) myheight = s.height();
    if (mywidth<s.width()) mywidth = s.width();

    view.setDisabled(true);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene.addItem(slot);
    scene.addItem(slide);
    view.setScene(&scene);
    view.setParent(this,Qt::FramelessWindowHint);
    this->setParent(parent);
}

qSVGSlider::qSVGSlider(QString slideFile, QString slotFile, QWidget *parent)
{
    slide = new QGraphicsSvgItem(slideFile);
    slot = new QGraphicsSvgItem(slotFile);
    b = slide->renderer()->defaultSize();
    s = slot->renderer()->defaultSize();
    slide->setTransformOriginPoint(b.width()/2,b.height()/2);
    slot->setTransformOriginPoint(s.width()/2,s.height()/2);
    view.setStyleSheet("background: transparent; border: none");

    myheight = b.height();
    mywidth = b.width();
    if (myheight<s.height()) myheight = s.height();
    if (mywidth<s.width()) mywidth = s.width();
    if (mywidth>myheight) setOrientation(Qt::Horizontal);

    view.setDisabled(true);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    scene.addItem(slot);
    scene.addItem(slide);
    view.setScene(&scene);
    view.setParent(this,Qt::FramelessWindowHint);
    this->setParent(parent);
}

qSVGSlider::~qSVGSlider()
{
    //noting
}

void qSVGSlider::paintEvent(QPaintEvent *pe)
{
    if (orientation() == Qt::Horizontal)
    {
        double r = this->width()*(1- b.height()/myheight);
        slide->setPos(r*this->sliderPosition()/ (this->maximum() - this->minimum()) - r/2, (s.height() - b.height())/2);//(b.height()-s.height())*this->width()/myheight/2 );
        view.centerOn(slot);
    }
    else
    {
        //double r = this->height()*(b.height()/myheight);
        //slide->setPos((b.width()-s.width())/2, r*this->sliderPosition()/ (this->minimum() - this->maximum()) );
        double r = this->height()*(1- b.height()/myheight);
        slide->setPos((b.width()-s.width())/2,r*this->sliderPosition()/ (this->maximum() - this->minimum()));//(b.height()-s.height())*this->width()/myheight/2 );
        view.centerOn(slot);
    }
    //QSlider::paintEvent(pe);
    view.show();
}

void qSVGSlider::resizeEvent(QResizeEvent *re)
{
    if (orientation() == Qt::Horizontal)
    {
        view.setFixedSize(this->width(),this->height());
        slide->setScale(this->width()/myheight);
        slot->setScale(this->width()/myheight);
        view.centerOn(slot);
    }
    else
    {
        view.setFixedSize(this->width(),this->height());
        slide->setScale(this->height()/myheight);
        slot->setScale(this->height()/myheight);
        view.centerOn(slot);
    }

//    if (this->width()>this->height())
//    {
//        view.setFixedSize(this->width(),this->height());
//        LEDon->setScale(this->height()/myheight);
//        LEDoff->setScale(this->height()/myheight);
//        view.centerOn(LEDon);
//    }
//    else
//    {
//        view.setFixedSize(this->width(),this->height());
//        LEDon->setScale(this->width()/mywidth);
//        LEDoff->setScale(this->width()/mywidth);
//        view.centerOn(LEDon);
//    }
    QSlider::resizeEvent(re);
}

void qSVGSlider::setOrientation(Qt::Orientation o)
{
    if (o == Qt::Horizontal)
    {
        slide->setRotation(-90);
        slot->setRotation(-90);
    }
    else
    {
        slide->setRotation(0);
        slot->setRotation(0);
    }
    QSlider::setOrientation(o);
}

