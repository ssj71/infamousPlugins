#include "preview.h"

preview::preview(skin *currentskin, int effect, QWidget *parent) :
    QWidget(parent)
{
    int n;
    QGraphicsSvgItem *item, *item2;
    QSize p, p2;
    controlskin *ctl;
    effectskin fx = currentskin->effects[effect];
    box = new QGraphicsSvgItem(fx.file);
    p = box->renderer()->defaultSize();
    scene.addItem(box);
    view.centerOn(box);

    myheight = p.height();
    mywidth = p.width();

    for (int i = 0;i<fx.controls;i++)
    {
        ctl = fx.control[i];
        QString str = ctl->type.toLower();
        if (str == "dial" )
        {
            item = new QGraphicsSvgItem(ctl->filename[0],box);
            p = item->renderer()->defaultSize();

            item2 = new QGraphicsSvgItem(ctl->filename[1],box);
            p2 = item2->renderer()->defaultSize();

            if (p.height()<p2.height())
                p = p2;
            item->setScale(ctl->h/p.height());
            item->setPos(ctl->x,myheight-p.height()-ctl->y);
            scene.addItem(item);
            item2->setScale(ctl->h/p.height());
            item2->setPos(ctl->x,myheight-p.height()-ctl->y);
            scene.addItem(item);
        }
        else if (str == "slider")
        {
            item = new QGraphicsSvgItem(ctl->filename[0],box);
            p = item->renderer()->defaultSize();
            if (ctl->h > ctl->w)
                item->setScale(ctl->h/p.height());
            else
                item->setScale(ctl->w/p.width());
            item->setPos(ctl->x,myheight-p.height()-ctl->y);
            scene.addItem(item);

            item = new QGraphicsSvgItem(ctl->filename[1],box);
            p = item->renderer()->defaultSize();
            if (ctl->h < ctl->w)
                item->setScale(ctl->h/p.height());
            else
                item->setScale(ctl->w/p.width());
            item->setPos(ctl->x,myheight-ctl->y);
            scene.addItem(item);
        }
        else
        {
            item = new QGraphicsSvgItem(ctl->filename[0],box);
            p = item->renderer()->defaultSize();
            item->setScale(ctl->w/p.width());
            item->setPos(ctl->x,myheight-p.height()-ctl->y);
            scene.addItem(item);
        }
    }

    view.setDisabled(true);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setStyleSheet("background: transparent; border: none");
    view.setScene(&scene);
    view.setParent(this,Qt::FramelessWindowHint);
}

void preview::resizeEvent(QResizeEvent *re)
{
    //view.scale(this->width()/mywidth,this->height()/myheight);
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
    box->setScale(scale);
    view.centerOn(box);
    QWidget::resizeEvent(re);
}
