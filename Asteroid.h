#pragma once

#include "GraphicPrimitives.h"

#define ASTEROID_SPEED        15
#define ASTEROID_MAX_ROTATION 90
#define ASTEROID_CORNERS      9

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

    double size_{5};
    double explosionTime_{0};
    double rotation_{0};
    double rotationSpeed_{0};
    double initial_rotationAngle_{0};

    Point2D_d speed{0, speed_};

    int sizeVariation[ASTEROID_CORNERS];

    COLOR color_{COLOR::BLUE};
};
