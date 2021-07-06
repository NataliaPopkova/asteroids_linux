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

//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT,
//                                       VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 -
//  left button, 1 - right button) clear_buffer() - set all pixels in buffer to
//  'black' is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()


SpaceShip* ship;

std::vector<Laser>    lasers;
std::vector<Asteroid> asteroids;

bool gameOver{false};
bool gameWon{false};
int  lives{3};

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
    /// ___________________ Space_ship logic __________________

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

    if (is_key_pressed(VK_DOWN))
        ship->Explode();

    /// ________________________ Laser logic _______________________________

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

    /// ______________________ Asteroids logic _____________________________

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

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit
// colors (8 bits per R, G, B)
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
