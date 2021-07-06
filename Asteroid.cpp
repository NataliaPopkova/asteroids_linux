#define _USE_MATH_DEFINES

#include <math.h>

#include "Asteroid.h"


Asteroid::Asteroid() {
    // Initialize position_ randomly on the screen
    // position_.x = rand() % SCREEN_WIDTH;
    // position_.y = rand() % SCREEN_HEIGHT;

    position_.x = SCREEN_WIDTH / 2;
    position_.y = SCREEN_HEIGHT / 2;

    // Initialize fixed speed_ in a random direction
    initial_rotationAngle_ = rand() % 360;

    rotate(initial_rotationAngle_, speed);

    // Initial size_ : 4
    size_ = 4;

    // Initializes a random rotation speed_
    rotation_ = 0;
    rotationSpeed_ =
        rand() % ASTEROID_MAX_ROTATION - (ASTEROID_MAX_ROTATION / 2);

    // Generates random shape of the asteroid
    int variation = ASTEROID_SIZE_VARIATION * size_ / 4;
    for (int i = 0; i < ASTEROID_CORNERS; i++) {
        sizeVariation[i] = rand() % variation - (variation / 2.0);
    }
}

Asteroid::Asteroid(Point2D_d newPosition, int newSize, double newSpeed)
        : position_(newPosition), speed_(newSpeed), size_(newSize) {
    // Initializes a random rotation speed
    rotation_ = 0;
    rotationSpeed_ =
        rand() % ASTEROID_MAX_ROTATION - (ASTEROID_MAX_ROTATION / 2);

    // Generates random shape of the asteroid
    int variation = ASTEROID_SIZE_VARIATION * size_ / 4;
    for (int i = 0; i < ASTEROID_CORNERS; i++) {
        sizeVariation[i] = rand() % variation - (variation / 2.0);
    }
}

void Asteroid::Move(double elapsedTime) {
    // If size_ > 0, we have an asteroid moving around
    // If size_ == 0, our asteroid is exploded
    if (size_ > 0) {
        // We move it around, and if it goes outside the screen, we make it pop
        // up on the other side;
        rotate(rotation_, speed);

        position_.x += speed.x;
        if (position_.x < 10) {
            position_.x = SCREEN_WIDTH - 10;
        }
        if (position_.x > SCREEN_WIDTH - 10) {
            position_.x = 10;
        }
        position_.y += speed.y;
        if (position_.y < 10) {
            position_.y = SCREEN_HEIGHT - 10;
        }
        if (position_.y > SCREEN_HEIGHT - 10) {
            position_.y = 10;
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
        int       angleStep = 360 / ASTEROID_CORNERS;
        Point2D_d points[angleStep];
        for (int i = 1; i < ASTEROID_CORNERS; i++) {
            points[i - 1] = Point2D_d(position_.x, position_.y);
            Point2D_d bias(size_ * ASTEROID_SIZE_MULTIPLIER + sizeVariation[i],
                           size_ * ASTEROID_SIZE_MULTIPLIER + sizeVariation[i]);
            move(bias, points[i - 1]);
            rotate(rotation_ + i * angleStep, points[i - 1]);

            if (i > 1) {
                drawLine_d(points[i - 1], points[i], color_);
            }

            if (i == ASTEROID_CORNERS - 1) {
                drawLine_d(points[ASTEROID_CORNERS - 1], points[0], color_);
            }
        }
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