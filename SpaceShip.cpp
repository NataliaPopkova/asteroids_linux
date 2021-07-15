#define _USE_MATH_DEFINES

#include <math.h>

#include "SpaceShip.h"

SpaceShip::SpaceShip(int lifeNo) {
    // "lives" ships, just to display the number of lives
    // left in the corner of the screen
    Reset();

    // Sets position in the corner of the screen
    position_.x = 30 + lifeNo * 30;
    position_.y = 40;
}

void SpaceShip::Draw() {
    if (!exploded_) {
        Point2D_d headPoint{0, size_};
        Point2D_d leftPoint{-size_ / 2, -size_ / 2};
        Point2D_d rightPoint{size_ / 2, -size_ / 2};

        rotate(rotation_, headPoint);
        rotate(rotation_, leftPoint);
        rotate(rotation_, rightPoint);

        move(position_, headPoint);
        move(position_, leftPoint);
        move(position_, rightPoint);

        drawLine_d(headPoint, leftPoint, color_);
        drawLine_d(leftPoint, rightPoint, color_);
        drawLine_d(rightPoint, headPoint, color_);
    } else {
        // Explosion mode
        int points_num{9};
        int angleStep = 360 / points_num;
        for (int i = 0; i < points_num; i++) {
            drawCircle_d(
                Point2D_d(position_.x - (explosionTime_ * 120) *
                                            cos(i * angleStep * M_PI / 180),

                          position_.y + (explosionTime_ * 120) *
                                            sin(i * angleStep * M_PI / 180)),
                4, color_);
        }
    }
};

void SpaceShip::Reset() {
    // Position in the center of the screen
    position_.x = SCREEN_WIDTH / 2;
    position_.y = SCREEN_HEIGHT / 2;

    // Speed = 0, the ship initially doesn't move
    speed_ = 0;

    rotation_ = 180;

    // The ship is not exploded
    exploded_ = false;
};

void SpaceShip::Explode() {
    // Ship explodes
    exploded_       = true;
    explosionTime_  = 0;
    resistanceTime_ = 0;
}

void SpaceShip::ApplyLeftRotation(float elapsedTime) {
    // Rotates the ship left
    rotation_ -= elapsedTime * 180;
}

void SpaceShip::ApplyRightRotation(float elapsedTime) {
    // Rotates the ship right
    rotation_ += elapsedTime * 180;
}

bool SpaceShip::IsExploded() {
    return exploded_;
};

double SpaceShip::GetExplosionTime() {
    return explosionTime_;
};

void SpaceShip::ApplyAcceleration(float elapsedTime) {
    speed_ += 0.1;
    if (speed_ > 1) {
        speed_ = 1;
    }
}

double SpaceShip::GetSize() {
    return size_;
}

void SpaceShip::Move(float elapsedTime) {
    if (this->IsExploded()) {
        explosionTime_ += elapsedTime;
    } else {
        if (speed_ == 0) {
            resistanceTime_ += elapsedTime;
            return;
        }
        Point2D_d speed{0, speed_};
        rotate(rotation_, speed);

        position_.x += speed.x;
        if (position_.x < size_) {
            position_.x = SCREEN_WIDTH - size_;
        }
        if (position_.x > SCREEN_WIDTH - size_) {
            position_.x = size_;
        }
        position_.y += speed.y;
        if (position_.y < size_) {
            position_.y = SCREEN_HEIGHT - size_;
        }
        if (position_.y > SCREEN_HEIGHT - size_) {
            position_.y = size_;
        }

        speed_ += 0.5;
        if (speed_ > 3) {
            speed_ = 3;

            resistanceTime_ += elapsedTime;
        }
    }
}

Point2D_d SpaceShip::GetPosition() {
    return position_;
};

double SpaceShip::GetRotation() {
    return rotation_;
};

bool SpaceShip::IsResistant() {
    if (resistanceTime_ < RESISTANCE_TIMEOUT) {
        resistant_ = true;
        return resistant_;
    }
    resistant_ = false;
    return resistant_;
}

double SpaceShip::GetResistanceTime() {
    return resistanceTime_;
}
