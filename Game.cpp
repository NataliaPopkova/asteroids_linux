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

std::vector<Laser>    lasers;
std::vector<Asteroid> asteroids;

bool gameOver{false};
bool gameWon{false};
int  lives{3};

void laser_logic(float dt);
void spaceShip_logic(float dt);
void lasers_logic(float dt);
void asteroids_logic(float dt);
void asteroids_laser_collision_logic(float dt);


// initialize game data in this function
void initialize() {
    std::srand(std::time(nullptr));

    ship = new SpaceShip();

    for (int i = 0; i < 6; i++) {
        asteroids.push_back(Asteroid());
    };
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt) {
    if (is_key_pressed(VK_DOWN))
        asteroids.back().Explode();

    spaceShip_logic(dt);

    laser_logic(dt);

    asteroids_logic(dt);

    asteroids_laser_collision_logic(dt);
}

void draw() {
    // clear backbuffer
    memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
    ship->Draw();

    for (int i = 0; i < lasers.size(); i++) {
        lasers[i].Draw();
    }

    for (int i = 0; i < asteroids.size(); i++) {
        asteroids[i].Draw();
    }
}

// free game data in this function
void finalize() {
    ship->~SpaceShip();

    for (int i = 0; i < lasers.size(); i++) {
        lasers[i].~Laser();
    }

    for (int i = 0; i < asteroids.size(); i++) {
        asteroids[i].~Asteroid();
    }
}

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
    // Laser to asteroid collisions
    bool foundCollision = false;
    // We go through each asteroid and laser to check for collisions
    for (int i = 0; i < asteroids.size(); i++) {
        for (int j = 0; j < lasers.size(); j++) {
            if (!foundCollision)  // One collision detection per frame is enough
            {
                // Distance between the center of the asteroid and laser
                double distance = pow(asteroids.at(i).GetPosition().x -
                                          lasers.at(j).GetPosition().x,
                                      2) +
                                  pow(asteroids.at(i).GetPosition().y -
                                          lasers.at(j).GetPosition().y,
                                      2);
                // Size of the asteroid
                double size = asteroids.at(i).GetSize();

                if (distance < size) {  // We have a collision

                    // Eliminate laser
                    lasers.erase(lasers.begin() + j);

                    // Explode asteroid and create 2 new if needed
                    if (asteroids.at(i).GetSize() > 1) {
                        // If the asteroid's size is higher than 1, we can split
                        // it into 2 That means creating 2 smaller asteroids and
                        // removing this one
                        Point2D_d cSpeed =
                            Point2D_d(0, asteroids.at(i).GetSpeed());
                        double speed1(asteroids.at(i).GetSpeed());

                        // New asteroid 1

                        Asteroid newAsteroid1(asteroids.at(i).GetPosition(),
                                              asteroids.at(i).GetSize() / 2,
                                              speed1);
                        asteroids.push_back(newAsteroid1);

                        // New asteroid 2

                        double   speed2(-asteroids.at(i).GetSpeed());
                        Asteroid newAsteroid2(asteroids.at(i).GetPosition(),
                                              asteroids.at(i).GetSize() / 2,
                                              speed2);
                        asteroids.push_back(newAsteroid2);

                        // Remove old asteroid
                        asteroids.erase(asteroids.begin() + i);
                    } else {
                        // If atseroid size was 1, we set it to explosion mode
                        asteroids.at(i).Explode();
                    }

                    foundCollision = true;
                }
            }
        }
    }
}