#include "radar.h"
#include <QApplication>

radar * radar1;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    radar1 = new radar();
   // w.resize(531,260);
    radar1->showFullScreen();//post on screen]

    return a.exec();
}
