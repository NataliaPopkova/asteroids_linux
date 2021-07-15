#pragma once

#include "GraphicPrimitives.h"

void drawNumber(int number, Point2D_d position);

void drawWin() {
    COLOR color = COLOR::GREEN;
    
    drawLine_d(Point2D_d(214, 263), Point2D_d(284, 477), color);
    drawLine_d(Point2D_d(284, 477), Point2D_d(347, 263), color);
    drawLine_d(Point2D_d(347, 263), Point2D_d(403, 477), color);
    drawLine_d(Point2D_d(403, 477), Point2D_d(479, 263), color);

    drawLine_d(Point2D_d(511, 263), Point2D_d(511, 477), color);

    drawLine_d(Point2D_d(561, 263), Point2D_d(561, 477), color);
    drawLine_d(Point2D_d(561, 263), Point2D_d(735, 477), color);
    drawLine_d(Point2D_d(735, 477), Point2D_d(735, 263), color);
};

void drawLose() {
    COLOR color = COLOR::RED;

    drawLine_d(Point2D_d(186, 263), Point2D_d(186, 477), color);
    drawLine_d(Point2D_d(186, 477), Point2D_d(315, 477), color);

    drawLine_d(Point2D_d(360, 263), Point2D_d(360, 477), color);
    drawLine_d(Point2D_d(360, 477), Point2D_d(488, 477), color);
    drawLine_d(Point2D_d(488, 477), Point2D_d(488, 263), color);
    drawLine_d(Point2D_d(488, 263), Point2D_d(360, 263), color);

    drawLine_d(Point2D_d(662, 263), Point2D_d(531, 263), color);
    drawLine_d(Point2D_d(531, 263), Point2D_d(531, 353), color);
    drawLine_d(Point2D_d(531, 353), Point2D_d(662, 353), color);
    drawLine_d(Point2D_d(662, 353), Point2D_d(662, 477), color);
    drawLine_d(Point2D_d(662, 477), Point2D_d(531, 477), color);

    drawLine_d(Point2D_d(693, 263), Point2D_d(840, 263), color);
    drawLine_d(Point2D_d(693, 263), Point2D_d(693, 477), color);
    drawLine_d(Point2D_d(693, 353), Point2D_d(840, 353), color);
    drawLine_d(Point2D_d(693, 477), Point2D_d(840, 477), color);
}

/*
    param: position - left top point
*/
void drawScore(int score, Point2D_d position) {
    int first = score / 10;
    int second = score % 10;
    drawNumber(first, position);
    drawNumber(second, Point2D_d(position.x + 70, position.y));
}

/*
    param: position - left top point
*/
void drawNumber(int number, Point2D_d position) {
    COLOR color{COLOR::BLUE};
    switch (number) {
    case 1:
        drawLine_d(Point2D_d(position.x + 60, position.y), Point2D_d(position.x + 60, position.y + 100), color);
        break;
    case 2:
        drawLine_d(position, Point2D_d(position.x + 60, position.y), color);
        drawLine_d(Point2D_d(position.x + 60, position.y), Point2D_d(position.x +60, position.y + 50), color);
        drawLine_d(Point2D_d(position.x + 60, position.y + 50), Point2D_d(position.x, position.y + 50), color);
        drawLine_d(Point2D_d(position.x, position.y + 50), Point2D_d(position.x, position.y + 100), color);
        drawLine_d(Point2D_d(position.x, position.y + 100), Point2D_d(position.x + 60, position.y + 100), color);
        break;
    case 3:
        drawLine_d(position, Point2D_d(position.x + 60, position.y), color);
        drawLine_d(Point2D_d(position.x + 60, position.y), Point2D_d(position.x + 60, position.y + 100), color);
        drawLine_d(Point2D_d(position.x + 60, position.y + 100), Point2D_d(position.x, position.y + 100), color);
        drawLine_d(Point2D_d(position.x + 60, position.y + 50), Point2D_d(position.x, position.y + 50), color);
        break;
    case 4:
        drawLine_d(position, Point2D_d(position.x, position.y + 50), color);
        drawLine_d(Point2D_d(position.x + 60, position.y + 50), Point2D_d(position.x, position.y + 50), color);
        drawLine_d(Point2D_d(position.x + 60, position.y), Point2D_d(position.x + 60, position.y + 100), color);
        break;
    case 5:
        drawLine_d(position, Point2D_d(position.x + 60, position.y), color);
        drawLine_d(position, Point2D_d(position.x, position.y + 50), color);
        drawLine_d(Point2D_d(position.x + 60, position.y + 50), Point2D_d(position.x + 60, position.y + 100), color);
        drawLine_d(Point2D_d(position.x + 60, position.y + 50), Point2D_d(position.x, position.y + 50), color);
        drawLine_d(Point2D_d(position.x + 60, position.y + 100), Point2D_d(position.x, position.y + 100), color);
        break;
    case 6:
        drawLine_d(position, Point2D_d(position.x + 60, position.y), color);
        drawLine_d(position, Point2D_d(position.x, position.y + 100), color);
        drawLine_d(Point2D_d(position.x + 60, position.y + 50), Point2D_d(position.x + 60, position.y + 100), color);
        drawLine_d(Point2D_d(position.x + 60, position.y + 50), Point2D_d(position.x, position.y + 50), color);
        drawLine_d(Point2D_d(position.x + 60, position.y + 100), Point2D_d(position.x, position.y + 100), color);
        break;
    case 7:
        drawLine_d(position, Point2D_d(position.x + 60, position.y), color); 
        drawLine_d(Point2D_d(position.x + 60, position.y), Point2D_d(position.x + 60, position.y + 100), color);
        break;
    case 8:
        drawLine_d(position, Point2D_d(position.x + 60, position.y), color);
        drawLine_d(position, Point2D_d(position.x, position.y + 100), color);
        drawLine_d(Point2D_d(position.x + 60, position.y), Point2D_d(position.x + 60, position.y + 100), color);
        drawLine_d(Point2D_d(position.x + 60, position.y + 100), Point2D_d(position.x, position.y + 100), color);
        drawLine_d(Point2D_d(position.x + 60, position.y + 50), Point2D_d(position.x, position.y + 50), color);
        break;
    case 9:
        drawLine_d(position, Point2D_d(position.x + 60, position.y), color);
        drawLine_d(position, Point2D_d(position.x, position.y + 50), color);
        drawLine_d(Point2D_d(position.x + 60, position.y), Point2D_d(position.x + 60, position.y + 100), color);
        drawLine_d(Point2D_d(position.x + 60, position.y + 100), Point2D_d(position.x, position.y + 100), color);
        drawLine_d(Point2D_d(position.x + 60, position.y + 50), Point2D_d(position.x, position.y + 50), color);
        break;
    case 0:
        drawLine_d(position, Point2D_d(position.x + 60, position.y), color);
        drawLine_d(position, Point2D_d(position.x, position.y + 100), color);
        drawLine_d(Point2D_d(position.x + 60, position.y), Point2D_d(position.x + 60, position.y + 100), color);
        drawLine_d(Point2D_d(position.x + 60, position.y + 100), Point2D_d(position.x, position.y + 100), color);
        break;    
    }
}