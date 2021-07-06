#pragma once

#include "GraphicPrimitives.h"

#define LASER_SPEED 5

class Laser {
public:
    Laser(Point2D_d position, double rotation)
            : position_(position), rotation_(rotation){};
    ~Laser() = default;

    void  Move(double elapsedTime);
    bool  IsOut();
    float GetFireTimeout();

    void Draw();

    Point2D_d GetPosition();

private:
    Point2D_d position_;
    double    speed_{LASER_SPEED};
    double    rotation_;
    float     fire_timeout_{0};

    COLOR color_{COLOR::RED};
};
