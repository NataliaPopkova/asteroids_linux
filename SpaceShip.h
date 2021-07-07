#pragma once

#include "GraphicPrimitives.h"

class SpaceShip {
public:
    SpaceShip() = default;

    SpaceShip(int lifeNo);

    ~SpaceShip() = default;

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

    double GetSize();

    void Reset();

private:
    COLOR color_{COLOR::GREEN};

    Point2D_d position_{Point2D_d(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2)};
    double    speed_{0};
    double    rotation_{180};
    double    size_{30};

    bool   exploded_{false};
    double explosionTime_;
};