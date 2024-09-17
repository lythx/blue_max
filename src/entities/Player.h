#ifndef BLUE_MAX_PLAYER_H
#define BLUE_MAX_PLAYER_H

#include "../geometry.h"
#include "../draw.h"
#include "Projectile.h"

typedef struct {
  Vector pos;
  Box* hitboxes;
  uint8_t up;
  uint8_t down;
  uint8_t left;
  uint8_t right;
  uint8_t texture_type;
  long long last_texture_change;
  long long last_shot_timestamp;
} Player;

Player player_create(Vector* pos);

void player_handle_keydown(Player* player, int keycode);

void player_handle_keyup(Player* player, int keycode);

void player_move(Player* player, Vector* center);

SDL_Texture* player_get_texture(const Player* player, int* width, int* height);

Projectile player_shoot(Player* player);

int player_can_shoot(const Player* player);

#endif //BLUE_MAX_PLAYER_H
