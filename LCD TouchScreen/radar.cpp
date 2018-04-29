#include "radar.h"
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QPainter>
#include "math.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QDebug>
//#define PI 3.14159265
radar::radar()
{
    scene = new QGraphicsScene();  //Scene
    scene -> setSceneRect(0,0,480,272);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    timer = new QTimer; //set timer
    connect(timer,SIGNAL(timeout()),this,SLOT(draw()));

   

    //this->setObjectName("mainWindow");
    //this->setStyleSheet("QWidget { background-image: url(:/new/prefix1/1.jpg); }");

    //QPalette palette;
    //palette.setBrush(QPalette::Background, QBrush(QPixmap("/Users/jianqinggao/Desktop/1.jpg")));
    table = new Table();
    table->setPos(0,0); //set background start location
    scene->addItem(table); //add things on background
    
    circle = new Circle();
    scene->addItem(circle);
    //x = 100;
    //y = 50;
    x = 200;
    y = 100;
    circle->setPos(x,y); //set point location
    timer->start(1000); //set timer period
    qDebug()<<"timer";
}


void radar::draw()
{
    //image = QImage("1.jpg");
   // qDebug()<<"draw";
    QFile file("/home/root/servo.txt");//read file
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);

    QFile file1("/home/root/sensor.txt");    
    file1.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in1(&file1);

    x = in.readLine().toInt(); //get file data to x,y
    y = in1.readLine().toInt();
    file.close();
    file1.close();
    qDebug()<<"x is"<<x<<"y is" <<y;
    
    y=220-y;
    x= (560/6)+x; //location calculation
    /*if(y==0)
    {
    x=240;
    y=272;
    qDebug()<<"DisEqlZero";
}
    else if(y!=0)
{
   int a;
   a=y;
   y=272-int(sin(x*PI/180)*y);
   x=240-int(cos(x*PI/180)*a);
   qDebug()<<"DisNOOOOOEqlZero";
}*/

    //x = 240;
    //y = 135;
    //x = 240;
    //y = 135;
    //y = 136-y;
    //x = atan(x)*y;
    circle->setPos(x,y);
    qDebug()<<"draw";
    //QPainter painter(&image);

    //painter
    //timer->update();
}
