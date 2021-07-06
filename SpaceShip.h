#pragma once

#include "GraphicPrimitives.h"


class SpaceShip {
public:
    SpaceShip() = default;

    SpaceShip(Point2D_d position, Point2D_d speed)
            : position_{position}, speed_{speed} {};

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

    void Reset();

private:
    COLOR color_{COLOR::BLUE};

    Point2D_d position_{Point2D_d(SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2)};
    Point2D_d speed_{Point2D_d(0, 0)};

    double rotation_{-90};
    int    hp_;

    bool   exploded_{false};
    double explosionTime_;
};