#ifndef PREVIEW_H
#define PREVIEW_H

#include <QWidget>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QGraphicsSvgItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QString>
#include <skin.h>

class preview : public QWidget
{
    Q_OBJECT
public:
    explicit preview(skin *currentskin, int effect, QWidget *parent = 0);

signals:

public slots:

private:
    void resizeEvent(QResizeEvent *re);
    float myheight;
    float mywidth;
    float scale;
    int effectNumber
    ;
    QGraphicsSvgItem *box;
    QGraphicsView view;
    QGraphicsScene scene;
    int numItems;

};

#endif // PREVIEW_H
