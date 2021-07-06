#pragma once

//
//  DO NOT MODIFY THIS FILE
//

#include <stdint.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

// backbuffer
extern uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

enum
{
  VK_ESCAPE,
  VK_SPACE,
  VK_LEFT,
  VK_UP,
  VK_RIGHT,
  VK_DOWN,
  VK_RETURN,

  VK__COUNT
};

// VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, etc.
bool is_key_pressed(int button_vk_code);

void initialize();
void finalize();

void act(float dt);
void draw();

void schedule_quit_game();
