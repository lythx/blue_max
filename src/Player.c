#include "Player.h"
#include "defs.h"

Player player_create(Vector* pos) {
  Box body_hb = box_create_around_center(pos, PLANE_BODY_LENGTH,
                                         PLANE_BODY_WIDTH, PLANE_BODY_HEIGHT);
  Box wings_hb = box_create_around_center(pos, PLANE_WINGS_LENGTH,
                                          PLANE_WINGS_WIDTH, PLANE_WINGS_HEIGHT);
  Box* hitboxes = malloc(sizeof(Box) * 2);
  hitboxes[0] = body_hb;
  hitboxes[1] = wings_hb;
  return (Player) {*pos, hitboxes};
}

void _handle_key(Player* player, int keycode, int value_to_set) {
  switch (keycode) {
    case SDL_SCANCODE_UP:
      player->up = value_to_set;
      break;
    case SDL_SCANCODE_DOWN:
      player->down = value_to_set;
      break;
    case SDL_SCANCODE_LEFT:
      player->left = value_to_set;
      break;
    case SDL_SCANCODE_RIGHT:
      player->right = value_to_set;
  }
}

void player_handle_keydown(Player* player, int keycode) {
  _handle_key(player, keycode, 1);
}

void player_handle_keyup(Player* player, int keycode) {
  _handle_key(player, keycode, 0);
}

void player_move(Player* player) {
  Vector v = vector_create(0,
                           (player->right - player->left) * PLAYER_HORIZONTAL_SPEED,
                           (player->up - player->down) * PLAYER_VERTICAL_SPEED);
  vector_sum(&player->pos, &v);
  player->hitboxes[0].x += v.x;
  player->hitboxes[0].y += v.y;
  player->hitboxes[0].z += v.z;
  player->hitboxes[1].x += v.x;
  player->hitboxes[1].y += v.y;
  player->hitboxes[1].z += v.z;
}
