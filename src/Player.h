#ifndef BLUE_MAX_PLAYER_H
#define BLUE_MAX_PLAYER_H

#include "geometry.h"

typedef struct {
  Vector pos;
  Box* hitboxes;
  int up;
  int down;
  int left;
  int right;
} Player;

Player player_create(Vector* pos);

void player_handle_keydown(Player* player, int keycode);

void player_handle_keyup(Player* player, int keycode);

void player_move(Player* player);

#endif //BLUE_MAX_PLAYER_H
