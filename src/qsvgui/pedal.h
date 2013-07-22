#ifndef PEDAL_H
#define PEDAL_H

#include <QtGui/QWidget>
#include <QString>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QGraphicsSvgItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <skin.h>
#include <qsvgdial.h>
#include <qsvgbutton.h>
#include <qsvgled.h>
#include <qsvgslider.h>
#include <qsvgmeter.h>
#include <LCD.h>
#include <preview.h>

class Pedal : public QWidget
{
    Q_OBJECT

public:
    explicit Pedal(QWidget *parent = 0);
    //explicit Pedal(int effect, QWidget *parent = 0);
    explicit Pedal(skin *skinfile, int effect, QWidget *parent);
    explicit Pedal(QString boxFile, QWidget *parent = 0);
    ~Pedal();
    QWidget* AddControl(QString type, QString param, int x, int y, int w, int h, QString file1, QString file2, QString file3, QString file4);

private:
    void resizeEvent(QResizeEvent *re);
    int LoadSkin(skin *currentskin, int effect);
    QRect PedalPosition();
    float myheight;
    float mywidth;
    float scale;
    int effectNumber;
    QGraphicsView view;
    QGraphicsScene scene;
    QGraphicsSvgItem *box;
    QSize p;
    QWidget* controls[20];
    QRect ctrlPos[20];
    int numControls;
};

#endif // PEDAL_H
