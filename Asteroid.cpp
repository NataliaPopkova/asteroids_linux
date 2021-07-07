#define _USE_MATH_DEFINES

#include <math.h>
#include <stdlib.h>

#include "Asteroid.h"

static inline double random(double min, double max) {
    return (double)(rand()) / RAND_MAX * (max - min) + min;
}

Asteroid::Asteroid() {
    // Initialize position_ randomly on the screen
    position_.x = rand() % SCREEN_WIDTH;
    position_.y = rand() % SCREEN_HEIGHT;

    // Initialize fixed speed_ in a random direction
    initial_rotationAngle_ = rand() % 360;

    rotate(initial_rotationAngle_, speed);

    // Initial size_ : 4
    size_ = 4;
}

Asteroid::Asteroid(Point2D_d newPosition, int newSize, double newSpeed)
        : position_(newPosition), speed_(newSpeed), size_(newSize) {
    // Initializes a random rotation speed
    rotation_      = 0;
    rotationSpeed_ = random(ASTEROID_MAX_ROTATION / 2, ASTEROID_MAX_ROTATION);
    // rand() % ASTEROID_MAX_ROTATION - (ASTEROID_MAX_ROTATION / 2);
}

void Asteroid::Move(double elapsedTime) {
    // If size_ > 0, we have an asteroid moving around
    // If size_ == 0, our asteroid is exploded
    if (size_ > 0) {
        // We move it around, and if it goes outside the screen, we make it pop
        // up on the other side;
        rotate(rotation_, speed);

        position_.x += speed.x;
        if (position_.x < size_ * 2) {
            position_.x = SCREEN_WIDTH - size_ * 2;
        }
        if (position_.x > SCREEN_WIDTH - size_ * 2) {
            position_.x = size_ * 2;
        }
        position_.y += speed.y;
        if (position_.y < size_ * 2) {
            position_.y = SCREEN_HEIGHT - size_ * 2;
        }
        if (position_.y > SCREEN_HEIGHT - size_ * 2) {
            position_.y = size_ * 2;
        }
        // We also rotate it
        rotation_ += rotationSpeed_ * elapsedTime;
    } else {
        // We use explosionTime_ to generate a visual explosion and remove it
        // after 0.5 seconds
        explosionTime_ += elapsedTime;
    }
}

void Asteroid::Explode() {
    // Asteroids goes into explosion mode
    size_          = 0;
    explosionTime_ = 0;
}

void Asteroid::Draw() {
    if (size_ > 0) {
        drawPolygonal(position_, size_, 6, color_);

        // If it's not exploded, we draw the asteroid's shape
    } else {
        // In case of an explosion, we draw 9 points moving away from the center
        int angleStep = 360 / ASTEROID_CORNERS;
        for (int i = 0; i < ASTEROID_CORNERS; i++) {
            drawCircle_d(
                Point2D_d(position_.x +
                              (explosionTime_ * (100 + 20 * sizeVariation[i])) *
                                  sin(i * angleStep * M_PI / 180),
                          position_.y -
                              (explosionTime_ * (100 + 20 * sizeVariation[i])) *
                                  cos(i * angleStep * M_PI / 180)),
                4, color_);
        }
    }
}

Point2D_d Asteroid::GetPosition() {
    return position_;
}

double Asteroid::GetSpeed() {
    return speed_;
}

int Asteroid::GetSize() {
    return size_;
}

double Asteroid::GetExplosionTime() {
    return explosionTime_;
}