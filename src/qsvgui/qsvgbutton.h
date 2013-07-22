#ifndef QSVGBUTTON_H
#define QSVGBUTTON_H

#include <QWidget>
#include <QAbstractButton>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QGraphicsSvgItem>
#include <QGraphicsView>
#include <QGraphicsScene>

class qSVGButton : public QAbstractButton
{
    Q_OBJECT

public:
    explicit qSVGButton(QWidget *parent = 0);
    explicit qSVGButton(QString buttonFile = "defaultButton.svg", QWidget *parent = 0);
    explicit qSVGButton(QString buttonFile = "defaultButton.svg", QString buttonDownFile = "defaultButtonDown.svg", QWidget *parent = 0);
    ~qSVGButton();

private:
    void paintEvent(QPaintEvent *pe);
    void resizeEvent(QResizeEvent *re);
    void init();
    float myheight, mywidth;
    QGraphicsView view;
    QGraphicsScene scene;
    QGraphicsSvgItem *button, *buttonDown;
    QSize b,bd;
    bool hasDown;
};

#endif // QSVGBUTTON_H
