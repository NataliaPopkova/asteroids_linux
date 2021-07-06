#pragma once

#include <stdio.h>
#include <math.h>
#include "Engine.h"

enum COLOR {
    BLUE  = 0x0000ff,
    RED   = 0xff0000,
    GREEN = 0x00ff00
};

struct Point2D
{
    Point2D(int x1, int y1) : x{ x1 }, y{ y1 } {};
    int x;
    int y;
};

struct Point2D_d
{
    Point2D_d(double x1, double y1) : x{ x1 }, y{ y1 } {};
    double x;
    double y;
};

/*
    Bresenham's line algorithm
*/
inline void drawLine(Point2D start, Point2D end, COLOR color) {
    const int deltaX = abs(end.x - start.x);
    const int deltaY = abs(end.y - start.y);
    const int signX = start.x < end.x ? 1 : -1;
    const int signY = start.y < end.y ? 1 : -1;
    int error = deltaX - deltaY;
    buffer[end.x][end.y] = color;
    while (start.x != end.x || start.y != end.y)
    {
        buffer[start.x][start.y] = color;
        int error2 = error * 2;
        if (error2 > -deltaY)
        {
            error -= deltaY;
            start.x += signX;
        }
        if (error2 < deltaX)
        {
            error += deltaX;
            start.y += signY;
        }
    }
};

inline void drawCircle(Point2D center, int radius, COLOR color) {
    int x = 0;
    int y = radius;
    int delta = 1 - 2 * radius;
    int error = 0;
    while (y >= 0) {
        buffer[center.x + x][center.y + y] = color;
        buffer[center.x + x][center.y - y] = color;
        buffer[center.x - x][center.y + y] = color;
        buffer[center.x - x][center.y - y] = color;

        error = 2 * (delta + y) - 1;
        if (delta < 0 && error <= 0) {
            ++x;
            delta += 2 * x + 1;
            continue;
        }
        error = 2 * (delta - x) - 1;
        if (delta > 0 && error > 0) {
            --y;
            delta += 1 - 2 * y;
            continue;
        }
        ++x;
        delta += 2 * (x - y);
        --y;
    }
}