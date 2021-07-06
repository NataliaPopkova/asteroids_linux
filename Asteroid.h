#pragma once

#include "GraphicPrimitives.h"

#define ASTEROID_SPEED           5
#define ASTEROID_MAX_ROTATION    90
#define ASTEROID_SIZE_MULTIPLIER 5
#define ASTEROID_SIZE_VARIATION  10
#define ASTEROID_CORNERS         9

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
    double    speed_;

    int    size_;
    double explosionTime_;
    double rotation_;
    double rotationSpeed_;
    double initial_rotationAngle_;

    Point2D_d speed{0, speed_};

    int sizeVariation[ASTEROID_CORNERS];

    COLOR color_{COLOR::BLUE};
};
