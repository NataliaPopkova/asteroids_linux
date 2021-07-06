#include "Engine.h"
#include "Laser.h"
#include "SpaceShip.h"
// #include "windows.h"
#include <memory.h>
#include <stdlib.h>
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

Laser* lasers[20];
int    lasers_num{0};

bool gameOver{false};
bool gameWon{false};
int  lives{3};

// initialize game data in this function
void initialize() {
    ship = new SpaceShip();
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt) {
    /// ________________________ Space_ship logic
    /// _______________________________

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
        if (!ship->IsExploded()) {
            if ((lasers_num < 20) ||
                (lasers[lasers_num]->GetFireTimeout() > 0.5)) {
                // If we pressed fire (SPACE key), we create a projectile,
                // starting from the position of the ship and going in the
                // direction the ship is faced
                Laser* laser =
                    new Laser(ship->GetPosition(), ship->GetRotation());
                lasers[lasers_num] = laser;
                lasers_num++;
            }
        }
    }

    for (int i = 0; i < lasers_num; i++) {
        // Move lasers
        lasers[i]->Move(dt);
        if (lasers[i]->IsOut()) {
            // Eliminate laser from the list if it's outside the screen
            Laser* laser = lasers[i];
            for (int j = i; j < lasers_num - 1; j++) {
                lasers[j] = lasers[j + 1];
            }
            lasers[lasers_num - 1] = NULL;
            delete laser;
            lasers_num--;
            i--;
        }
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

    for (int i = 0; i < lasers_num; i++) {
        lasers[i]->Draw();
    }
}

// free game data in this function
void finalize() {
    ship->~SpaceShip();

    for (int i = 0; i < lasers_num; i++) {
        lasers[i]->~Laser();
    }
}
