#pragma once

#include "GraphicPrimitives.h"

#define LASER_SPEED 400;

class Laser {
public:
    Laser(Point2D_d position, double rotation);
    ~Laser() = default;

    void  Move(double elapsedTime);
    bool  IsOut();
    float GetFireTimeout();

    void Draw();

    Point2D_d GetPosition();

private:
    Point2D_d position_;
    Point2D_d speed_;
    float     fire_timeout_{0};

    COLOR color_{COLOR::RED};
};
