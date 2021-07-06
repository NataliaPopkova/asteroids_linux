#include "Laser.h"
#include "Engine.h"

Laser::Laser(Point2D_d position, double rotation) : position_(position) {
    // Initialize the speed_ from a rotation angle
    speed_.x = sin(rotation * M_PI / 180) * LASER_SPEED;
    speed_.y = -cos(rotation * M_PI / 180) * LASER_SPEED;
}

void Laser::Move(double elapsedTime) {
    // Laser moves
    position_.x += elapsedTime * speed_.x;
    position_.y += elapsedTime * speed_.y;

    fire_timeout_ += elapsedTime;
}

bool Laser::IsOut() {
    // Returns true if the Laser is out of the screen area so we can remove
    // it
    if (position_.x < -1 || position_.x > SCREEN_HEIGHT + 1 ||
        position_.y < -1 || position_.y > SCREEN_WIDTH + 1) {
        return true;
    }
    return false;
}

float Laser::GetFireTimeout() {
    return fire_timeout_;
};

void Laser::Draw() {
    // Draws the ball using Direct2D
    drawCircle(Point2D(static_cast<uint32_t>(position_.x),
                       static_cast<uint32_t>(position_.y)),
               5, color_);
}

Point2D_d Laser::GetPosition() {
    return position_;
}