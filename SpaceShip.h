#pragma once

#include "GraphicPrimitives.h"


class SpaceShip {
public:
    SpaceShip() = default;

    SpaceShip(Point2D_d position, Point2D_d speed)
            : position_{position}, speed_{0} {};

    ~SpaceShip() = default;

    bool Update();

    void Draw();

    void ApplyLeftRotation(float elapsedTime);

    void ApplyRightRotation(float elapsedTime);

    void ApplyAcceleration(float elapsedTime);

    void Move(float elapsedTime);

    void Explode();

    bool IsExploded();

    double GetExplosionTime();

    Point2D_d GetPosition();

    double GetRotation();

    void Reset();

private:
    COLOR color_{COLOR::BLUE};

    Point2D_d position_{Point2D_d(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2)};
    double    speed_{0};
    double    rotation_{180};
    int       hp_;

    bool   exploded_{false};
    double explosionTime_;
};