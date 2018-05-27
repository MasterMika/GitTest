#include "drawfunc.h"

#include "QPainter"

DrawFunc::DrawFunc()
{
}

void DrawFunc::operator ()(bool cond, QPainter * painter,int x, int y, int width, int height, int padding) const
{
    if(cond){
        painter->setBrush(Qt::black);
        painter->drawRect(x + padding, y + padding, width - 2 * padding, height - 2 * padding);
    }else {
        painter->setPen(Qt::black);
        painter->setBrush(Qt::white);
        painter->drawRect(x + padding, y + padding, width - 2 * padding, height - 2 * padding);
    }
}

