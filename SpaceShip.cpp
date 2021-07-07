#define _USE_MATH_DEFINES

#include <math.h>

#include "SpaceShip.h"

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
    exploded_      = true;
    explosionTime_ = 0;
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
    speed_ += 0.5;
    if (speed_ > 3) {
        speed_ = 3;
    }
}

void SpaceShip::Move(float elapsedTime) {
    if (this->IsExploded()) {
        explosionTime_ += elapsedTime;
    } else {
        if (speed_ == 0) {
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

        speed_ -= 0.1;
        if (speed_ < 0) {
            speed_ = 0;
        }
    }
}

Point2D_d SpaceShip::GetPosition() {
    return position_;
};

double SpaceShip::GetRotation() {
    return rotation_;
};
