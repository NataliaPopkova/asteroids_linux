#pragma once

#include "Asteroid.h"
#include "Engine.h"
#include "Laser.h"
#include "SpaceShip.h"
// #include "windows.h"
#include <memory.h>
#include <stdlib.h>
#include <chrono>
#include <random>
#include <vector>


SpaceShip* ship;

std::vector<Laser>     lasers;
std::vector<Asteroid>  asteroids;
std::vector<SpaceShip> lifeShips;

bool gameOver{false};
bool gameWon{false};
int  lives{3};
int  asteroids_n{6};

void laser_logic(float dt);
void spaceShip_logic(float dt);
void lasers_logic(float dt);
void asteroids_logic(float dt);
void asteroids_laser_collision_logic(float dt);
void asteroid_ship_collision_logic(float dt);


void laser_logic(float dt) {
    if (is_key_pressed(VK_SPACE)) {
        if (lasers.size() == 0) {
            lasers.push_back(Laser(ship->GetPosition(), ship->GetRotation()));
        };

        if (!ship->IsExploded() && (lasers.size() > 0) &&
            (lasers.back().GetFireTimeout() > 0.2)) {
            if (lasers.size() < 20) {
                lasers.push_back(
                    Laser(ship->GetPosition(), ship->GetRotation()));
            }
        }
    }

    for (int i = 0; i < lasers.size(); i++) {
        // Move lasers
        lasers[i].Move(dt);

        if (lasers[i].IsOut()) {
            lasers.erase(lasers.begin() + i);
            i--;
        }
    }
}

void spaceShip_logic(float dt) {
    if (is_key_pressed(VK_ESCAPE))
        schedule_quit_game();

    if (is_key_pressed(VK_LEFT)) {
        if (!ship->IsExploded()) {
            ship->ApplyLeftRotation(dt);
        }
    }

    if (is_key_pressed(VK_RIGHT)) {
        if (!ship->IsExploded()) {
            ship->ApplyRightRotation(dt);
        }
    }

    if (is_key_pressed(VK_UP)) {
        if (!ship->IsExploded()) {
            ship->ApplyAcceleration(dt);
        }
    }

    ship->Move(dt);
    if (ship->IsExploded() && ship->GetExplosionTime() > 0.5) {
        // If the ship is exploded and 0.5 seconds has passed, we reset it and
        // decrease the lives.
        ship->Reset();
        lives--;
        lifeShips.pop_back();
        if (lives == 0) {
            // Game Over
            gameOver = true;
            gameWon  = false;
        }
    }
}

void asteroids_logic(float dt) {
    for (int i = 0; i < asteroids.size(); i++) {
        // Move the asteroids
        asteroids[i].Move(dt);
        if (asteroids[i].GetSize() == 0 &&
            asteroids[i].GetExplosionTime() > 0.5) {
            // If the asteroid is exploded and 0.5 seconds passed, we remove the
            // asteroid from the list
            asteroids.erase(asteroids.begin() + i);
        }
    }

    if (asteroids.size() == 0) {
        // You won!
        gameOver = true;
        gameWon  = true;
    }

    if (gameOver == true)
        schedule_quit_game();
}

void asteroids_laser_collision_logic(float dt) {
    bool foundCollision{false};
    // We go through each asteroid and laser to check for collisions
    for (int i = 0; i < asteroids.size(); i++) {
        for (int j = 0; j < lasers.size(); j++) {
            if (!foundCollision)  // One collision detection per frame is enough
            {
                // Distance between the center of the asteroid and laser
                double distance = sqrt(pow(asteroids[i].GetPosition().x -
                                               lasers[j].GetPosition().x,
                                           2) +
                                       pow(asteroids[i].GetPosition().y -
                                               lasers[j].GetPosition().y,
                                           2));
                // Size of the asteroid
                double size = asteroids[i].GetSize();

                if (distance < size) {  // We have a collision
                    // Remove laser
                    lasers.erase(lasers.begin() + j);

                    // Explode asteroid and create 2 new if needed
                    if (asteroids[i].GetSize() > ASTEROID_MIN_SIZE) {
                        // If the asteroid's size is higher than 1, we can split
                        // it into 2 That means creating 2 smaller asteroids and
                        // removing this one
                        Point2D_d cSpeed =
                            Point2D_d(0, asteroids[i].GetSpeed());
                        double speed1(asteroids[i].GetSpeed());

                        // New asteroid 1
                        Asteroid newAsteroid1(asteroids[i].GetPosition(),
                                              asteroids[i].GetSize() / 2,
                                              speed1);
                        asteroids.push_back(newAsteroid1);

                        // New asteroid 2
                        double   speed2(-asteroids[i].GetSpeed());
                        Asteroid newAsteroid2(asteroids[i].GetPosition(),
                                              asteroids[i].GetSize() / 2,
                                              speed2);
                        asteroids.push_back(newAsteroid2);

                        // Remove old asteroid
                        asteroids.erase(asteroids.begin() + i);
                    } else {
                        // If atseroid size was ASTEROID_MIN_SIZE, we set it to
                        // explosion mode
                        asteroids[i].Explode();
                    }

                    foundCollision = true;
                }
            }
        }
    }
}

void asteroid_ship_collision_logic(float dt) {
    bool foundCollision{false};
    if (!ship->IsExploded()) {
        foundCollision = false;
        // We go through all the steroids
        for (int i = 0; i < asteroids.size(); i++) {
            if (!foundCollision)  // One collision per frame is enough
            {
                // Distance between ship's and asteroid's centers
                double distance = sqrt(
                    pow(asteroids[i].GetPosition().x - ship->GetPosition().x,
                        2) +
                    pow(asteroids[i].GetPosition().y - ship->GetPosition().y,
                        2));
                // Asteroid's size + ship's size
                double size = asteroids[i].GetSize() / 2 + ship->GetSize();

                // If we have a collision
                if (distance < size) {
                    // Ship explosion
                    ship->Explode();

                    foundCollision = true;
                }
            }
        }
    }
}