#include "Laser.h"
#include "Engine.h"


void Laser::Move(double elapsedTime) {
    // Laser moves
    Point2D_d speed{0, speed_};
    rotate(rotation_, speed);

    position_.x += speed.x;
    position_.y += speed.y;

    fire_timeout_ += elapsedTime;
}

bool Laser::IsOut() {
    // Returns true if the Laser is out of the screen area so we can remove
    // it
    if (position_.x < -5 || position_.x > SCREEN_WIDTH + 5 ||
        position_.y < -5 || position_.y > SCREEN_HEIGHT + 5) {
        return true;
    }
    return false;
}

float Laser::GetFireTimeout() {
    return fire_timeout_;
};

void Laser::Draw() {
    drawCircle_d(Point2D_d(position_.x, position_.y), 5, color_);
}

Point2D_d Laser::GetPosition() {
    return position_;
}