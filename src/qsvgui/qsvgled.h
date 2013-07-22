#ifndef QSVGLED_H
#define QSVGLED_H

#include <QWidget>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QGraphicsSvgItem>
#include <QGraphicsView>
#include <QGraphicsScene>

class qSVGLED : public QWidget
{
    Q_OBJECT
public:
    explicit qSVGLED(QWidget *parent = 0);
    explicit qSVGLED(QString offFile = "defaultLEDOff.svg", QString onFile = "defaultLEDOn.svg", QWidget *parent = 0);

signals:

public slots:
    void toggle();
    void setState(bool);
    void setBrightness(qreal);

private:
    void resizeEvent(QResizeEvent *re);
    float myheight, mywidth;
    QGraphicsView view;
    QGraphicsScene scene;
    QGraphicsSvgItem *LEDon, *LEDoff;
    QSize ln,lf;
    bool state;

};

#endif // QSVGLED_H
