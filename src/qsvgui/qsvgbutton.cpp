#include "qsvgbutton.h"
#include "stdio.h"



qSVGButton::qSVGButton(QWidget *parent) :
    QAbstractButton(parent)
{
    button = new QGraphicsSvgItem("defaultButton.svg");
    b = button->renderer()->defaultSize();
    hasDown = false;
    button->setTransformOriginPoint(b.width()/2,b.height()/2);
    view.setStyleSheet("background: transparent; border: none");

    myheight = b.height();
    mywidth = b.width();
    if (myheight<bd.height()) myheight = bd.height();
    if (mywidth<bd.width()) mywidth = bd.width();
    view.setDisabled(true);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene.addItem(button);
    view.setScene(&scene);
    view.setParent(this,Qt::FramelessWindowHint);
}

qSVGButton::qSVGButton(QString buttonFile, QWidget *parent) :
    QAbstractButton(parent)
{
    button = new QGraphicsSvgItem(buttonFile);
    b = button->renderer()->defaultSize();
    hasDown = false;
    button->setTransformOriginPoint(b.width()/2,b.height()/2);
    view.setStyleSheet("background: transparent; border: none");

    myheight = b.height();
    mywidth = b.width();
    if (myheight<bd.height()) myheight = bd.height();
    if (mywidth<bd.width()) mywidth = bd.width();
    view.setDisabled(true);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene.addItem(button);
    view.setScene(&scene);
    view.setParent(this,Qt::FramelessWindowHint);
}

qSVGButton::qSVGButton(QString buttonFile, QString buttonDownFile, QWidget *parent) :
    QAbstractButton(parent)
{
    button = new QGraphicsSvgItem(buttonFile);
    buttonDown = new QGraphicsSvgItem(buttonDownFile);
    b = button->renderer()->defaultSize();
    bd = buttonDown->renderer()->defaultSize();
    hasDown = true;
    buttonDown->setVisible(false);
    button->setTransformOriginPoint(b.width()/2,b.height()/2);
    buttonDown->setTransformOriginPoint(bd.width()/2,bd.height()/2);
    view.setStyleSheet("background: transparent; border: none");

    myheight = b.height();
    mywidth = b.width();
    if (myheight<bd.height()) myheight = bd.height();
    if (mywidth<bd.width()) mywidth = bd.width();
    view.setDisabled(true);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene.addItem(button);
    scene.addItem(buttonDown);
    view.setScene(&scene);
    view.setParent(this,Qt::FramelessWindowHint);
}


qSVGButton::~qSVGButton()
{

}


void qSVGButton::paintEvent(QPaintEvent *pe)
{
    if(hasDown)
    {
        if(this->isChecked() || this->isDown())
        {
            buttonDown->setVisible(true);
        }
        else
        {
            buttonDown->setVisible(false);
        }
    }
}

void qSVGButton::resizeEvent(QResizeEvent *re)
{
    if (this->width()/mywidth>this->height()/myheight)
    {
        view.setFixedSize(this->width(),this->height());
        button->setScale(this->height()/myheight);
        if(hasDown)buttonDown->setScale(this->height()/myheight);
        view.centerOn(button);
    }
    else
    {
        view.setFixedSize(this->width(),this->height());
        button->setScale(this->width()/mywidth);
        if(hasDown)buttonDown->setScale(this->width()/mywidth);
        view.centerOn(button);
    }
    QAbstractButton::resizeEvent(re);
}
