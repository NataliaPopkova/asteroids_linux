#pragma once

#include "GraphicPrimitives.h"

void drawWin() {
    COLOR color = COLOR::GREEN;

    double x0 = SCREEN_WIDTH / 3;
    double y0 = SCREEN_HEIGHT / 3;

    drawLine_d(Point2D_d(x0, y0), Point2D_d(x0 + x0 / 9, 2 * y0), color);
};