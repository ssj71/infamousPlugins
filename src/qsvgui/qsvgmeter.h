#ifndef QSVGMETER_H
#define QSVGMETER_H

#include <QString>
#include <QWidget>
#include "qsvgled.h"

class qSVGMeter : public QWidget
{
    Q_OBJECT
public:
    explicit qSVGMeter(QString greenOffFile, QString greenOnFile, QString yellowOffFile, QString yellowOnFile, QString redOffFile, QString redOnFile, QWidget *parent = 0);
    void setOrientation(Qt::Orientation);

signals:

public slots:
    void setMeter(int value);
    void setMeter(double value);

private:
    qSVGLED *led[10];
    bool vertical;
    void resizeEvent(QResizeEvent *re);


};

#endif // QSVGMETER_H
