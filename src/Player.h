#ifndef BLUE_MAX_PLAYER_H
#define BLUE_MAX_PLAYER_H

#include "geometry.h"
#include "draw.h"
#include "Projectile.h"

typedef struct {
  Vector pos;
  Box* hitboxes;
  int up;
  int down;
  int left;
  int right;
  SDL_Texture* texture;
} Player;

Player player_create(const App* app, Vector* pos);

void player_handle_keydown(Player* player, int keycode);

void player_handle_keyup(Player* player, int keycode);

void player_move(Player* player, Vector* center);

Projectile player_shoot(const App* app, const Player* player);

#endif //BLUE_MAX_PLAYER_H
