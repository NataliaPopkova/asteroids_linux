#pragma once

#include "GraphicPrimitives.h"

#define ASTEROID_SPEED    3
#define ASTEROID_CORNERS  9
#define ASTEROID_MAX_SIZE 35
#define ASTEROID_MIN_SIZE 15

class Asteroid {
public:
    Asteroid();
    Asteroid(Point2D_d newPosition, int newSize, double newSpeed);
    ~Asteroid() = default;

    void Move(double elapsedTime);
    void Explode();

    void Draw();

    Point2D_d GetPosition();
    double    GetSpeed();
    int       GetSize();
    double    GetExplosionTime();

private:
    Point2D_d position_;
    double    speed_{ASTEROID_SPEED};

    double size_{ASTEROID_MAX_SIZE};
    double explosionTime_{0};
    double initial_rotationAngle_{0};

    Point2D_d speed{0, speed_};

    COLOR color_{COLOR::BLUE};
};
