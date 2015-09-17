#ifndef QSVGSLIDER_H
#define QSVGSLIDER_H

#include <QWidget>
#include <QSlider>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QGraphicsSvgItem>
#include <QGraphicsView>
#include <QGraphicsScene>

class qSVGSlider : public QSlider
{
    Q_OBJECT

public:
    explicit qSVGSlider(QWidget *parent = 0);
    explicit qSVGSlider(QString slideFile = "defaultSlide.svg", QWidget *parent = 0);
    explicit qSVGSlider(QString slideFile = "defaultSlide.svg", QString slotFile = "defaultslot.svg", QWidget *parent = 0);
    void setOrientation(Qt::Orientation);
    ~qSVGSlider();

private:
    void paintEvent(QPaintEvent *pe);
    void resizeEvent(QResizeEvent *re);
    float myheight, mywidth;
    QGraphicsView view;
    QGraphicsScene scene;
    QGraphicsSvgItem *slide, *slot;
    QSize s,b;
    bool horizontal;
};

#endif // QSVGSLIDER_H
