#include "circle.h"
#include <QBrush>
Circle::Circle()
{
    setRect(0,0,10,10);
    setBrush(QBrush(Qt::red));// set point size and create circle function
}

