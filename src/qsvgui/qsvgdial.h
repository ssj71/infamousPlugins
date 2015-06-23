#ifndef QSVGDIAL_H
#define QSVGDIAL_H

#include <QWidget>
#include <QDial>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QGraphicsSvgItem>
#include <QGraphicsView>
#include <QGraphicsScene>

class qSVGDial : public QDial
{
    Q_OBJECT

public:
    explicit qSVGDial(QWidget *parent = 0);
    explicit qSVGDial(QString knobFile = "defaultKnob.svg", QString needleFile = "defaultNeedle.svg", QWidget *parent = 0);
    ~qSVGDial();

private slots:
    void rotateNeedle(int p);

private:
    void resizeEvent(QResizeEvent *re);
    void paintEvent(QPaintEvent *pe);
    float degPerPos;
    float middle;
    float mysize;
    QGraphicsView view;
    QGraphicsScene scene;
    QGraphicsSvgItem *knob;
    QGraphicsSvgItem *needle;
    QSize k,n;

};

#endif // QSVGDIAL_H
