#ifndef RADAR_H
#define RADAR_H
#include <QWidget>
#include <QtGui>
#include <QGraphicsScene>
#include <QtCore>
#include <QGraphicsView>
#include <QPainter>
#include "table.h"
#include "circle.h"
class radar: public QGraphicsView
{
    Q_OBJECT

public:
     radar();
     QGraphicsScene * scene;
     Table * table;
     Circle * circle;
/*protected:
    void paintEvent();*/
private:
    //Ui::MainWindow *ui;
    QTimer *timer;
    QImage image;
    int x;
    int y;
public slots:
    void draw();
};

#endif // RADAR_H
