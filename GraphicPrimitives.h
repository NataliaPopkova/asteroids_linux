#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <vector>
#include "Engine.h"

enum COLOR { BLUE = 0x0000ff, RED = 0xff0000, GREEN = 0x00ff00 };

struct Point2D {
    Point2D(int x1, int y1) : x{x1}, y{y1} {};
    int x;
    int y;
};

struct Point2D_d {
    Point2D_d(double x1, double y1) : x{x1}, y{y1} {};
    Point2D_d() = default;
    double x;
    double y;
};

static void rotate(float angle_deg, Point2D_d& point) {
    float angle = angle_deg * M_PI / 180.;

    Point2D_d old = point;
    point.x       = old.x * cos(angle) - old.y * sin(angle);
    point.y       = old.x * sin(angle) + old.y * cos(angle);
}

static void move(const Point2D_d& bias, Point2D_d& point) {
    point.x = point.x + bias.x;
    point.y = point.y + bias.y;
}

/*
    Bresenham's line algorithm
*/
inline void drawLine(Point2D start, Point2D end, COLOR color) {
    const int deltaX = abs(end.x - start.x);
    const int deltaY = abs(end.y - start.y);
    const int signX  = start.x < end.x ? 1 : -1;
    const int signY  = start.y < end.y ? 1 : -1;
    int       error  = deltaX - deltaY;
    if ((end.y > 0) && (end.y < SCREEN_HEIGHT) && (end.x > 0) &&
        (end.x < SCREEN_WIDTH)) {
        buffer[end.y][end.x] = color;
    }
    while (start.x != end.x || start.y != end.y) {
        if ((start.y > 0) && (start.y < SCREEN_HEIGHT) && (start.x > 0) &&
            (start.x < SCREEN_WIDTH)) {
            buffer[start.y][start.x] = color;
        }
        int error2 = error * 2;
        if (error2 > -deltaY) {
            error -= deltaY;
            start.x += signX;
        }
        if (error2 < deltaX) {
            error += deltaX;
            start.y += signY;
        }
    }
};

inline void drawLine_d(Point2D_d start, Point2D_d end, COLOR color) {
    drawLine({(int)start.x, (int)start.y}, {(int)end.x, (int)end.y}, color);
}

/*
    draws a regular polygon
*/
inline void drawPolygonal_d(Point2D_d center, double size, int anglesNum,
                          COLOR color) {
    std::vector<Point2D_d> points;
    Point2D_d              bias(size, size);
    double                 angleStep = 360. / anglesNum;
    Point2D_d              point(center);
    Point2D_d              _center(-center.x, -center.y);

    move(_center, point);
    move(bias, point);
    rotate(0, point);
    move(center, point);

    points.push_back(point);

    for (int i = 1; i < anglesNum; i++) {
        Point2D_d point1(center);
        move(_center, point1);
        move(bias, point1);
        rotate(angleStep * i, point1);
        move(center, point1);

        points.push_back(point1);
        drawLine_d(points[i - 1], points[i], color);
    };

    drawLine_d(points[anglesNum - 1], points[0], color);
}

inline void drawCircle(Point2D center, int radius, COLOR color) {
    int x     = 0;
    int y     = radius;
    int delta = 1 - 2 * radius;
    int error = 0;
    while (y >= 0) {
        if ((center.y + y > radius*2) &&
            (center.y + y < SCREEN_HEIGHT - radius*2) &&
            (center.x + x > radius*2) && (center.x + x < SCREEN_WIDTH - radius*2)) {
            buffer[center.y + y][center.x + x] = color;
            buffer[center.y - y][center.x + x] = color;
            buffer[center.y + y][center.x - x] = color;
            buffer[center.y - y][center.x - x] = color;
        }

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

inline void drawCircle_d(Point2D_d center, int radius, COLOR color) {
    drawCircle({(int)center.x, (int)center.y}, (int)radius, color);
}