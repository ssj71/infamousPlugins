#ifndef QSVGUI_H
#define QSVGUI_H

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

class qsvgui : public QWidget
{
    Q_OBJECT

public:
    explicit qsvgui(QWidget *parent = 0);
    //explicit Pedal(int effect, QWidget *parent = 0);
    explicit qsvgui(skin *skinfile, QWidget *parent);
    explicit qsvgui(QString boxFile, QWidget *parent = 0);
    ~qsvgui();
    int AddControl(QString type, QString param, int x, int y, int w, int h, int theta, QString file1, QString file2, QString file3, QString file4);

private:
    void resizeEvent(QResizeEvent *re);
    skin sk;
    int LoadSkin(skin *currentskin, int effect);
    int LoadSkin(QString skinfile, QString name);
    QRect PedalPosition();
    float myheight;
    float mywidth;
    float scale;
    QGraphicsView view;
    QGraphicsScene scene;
    QGraphicsSvgItem *bg;
    QSize p;
    std::vector<QWidget> controls;
    std::vector<QRect> ctrlPos;
};

#endif // QSVGUI_H
