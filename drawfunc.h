#ifndef DRAWFUNC_H
#define DRAWFUNC_H

#include <QPainter>

class DrawFunc {
public:
    DrawFunc();
    void operator() (bool cond, QPainter * painter,int x, int y, int width, int height, int padding) const;
};

#endif // DRAWFUNC_H
