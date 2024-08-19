#include "Player.h"
#include "../defs.h"
#include "../init_SDL.h"

Player player_create(const App* app, Vector* pos) {
  Box body_hb = box_create_around_center(pos, PLANE_BODY_LENGTH,
                                         PLANE_BODY_WIDTH, PLANE_BODY_HEIGHT);
  Box wings_hb = box_create_around_center(pos, PLANE_WINGS_LENGTH,
                                          PLANE_WINGS_WIDTH, PLANE_WINGS_HEIGHT);
  Box* hitboxes = malloc(sizeof(Box) * 2);
  hitboxes[0] = body_hb;
  hitboxes[1] = wings_hb;
  SDL_Texture* texture = load_texture(app, "../assets/player.png");
  return (Player) {*pos, hitboxes, 0, 0, 0, 0, texture};
}

void handle_key(Player* player, int keycode, int value_to_set) {
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
      break;
    default:
      break;
  }
}

void player_handle_keydown(Player* player, int keycode) {
  handle_key(player, keycode, 1);
}

void player_handle_keyup(Player* player, int keycode) {
  handle_key(player, keycode, 0);
}

void player_move(Player* player, Vector* center) {
  Vector forward = vector_create(PLAYER_FORWARD_SPEED, 0, 0);
  vector_rotate(&forward);
  Vector diff = vector_create(0,
                           (player->right - player->left) * PLAYER_HORIZONTAL_SPEED,
                           (player->up - player->down) * PLAYER_VERTICAL_SPEED);
  vector_sum(center, &forward);
  vector_sum(&diff, &forward);
  Vector new_pos = vector_copy(&player->pos);
  vector_sum(&new_pos, &diff);
  double lbound = center->y - PLAYER_HORIZONTAL_BOUND;
  double rbound = center->y + PLAYER_HORIZONTAL_BOUND;
  if (new_pos.y < lbound) {
    new_pos.y = lbound;
  } else if (player->pos.y > rbound) {
    new_pos.y = rbound;
  }
  if (new_pos.z > PLAYER_UP_BOUND) {
    new_pos.z = PLAYER_UP_BOUND;
  }
  diff.y = new_pos.y - player->pos.y;
  diff.z = new_pos.z - player->pos.z;
  vector_sum(&player->pos, &diff);
  player->hitboxes[0].x += diff.x;
  player->hitboxes[0].y += diff.y;
  player->hitboxes[0].z += diff.z;
  player->hitboxes[1].x += diff.x;
  player->hitboxes[1].y += diff.y;
  player->hitboxes[1].z += diff.z;
}

Projectile player_shoot(const App* app, const Player* player) {
  Vector pos = vector_copy(&player->pos);
  return projectile_create(app, &pos, PROJECTILE_PLAYER);
}

