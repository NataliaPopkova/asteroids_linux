#pragma once

#include "GraphicPrimitives.h"

class Projectile {
public:
    Projectile(Point2D_d position, double rotation);
    ~Projectile();

    void Advance(double elapsedTime);
    bool IsOut();

    void Draw();

    Point2D_d GetPosition();

private:
    Point2D_d position;
    Point2D_d speed;

    COLOR color_;
};
