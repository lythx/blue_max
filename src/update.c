#include "update.h"

void move_center_and_entities(Vector* center, Player* player,
                              Plane* planes, uint8_t plane_count,
                              Projectile* player_projectiles, uint8_t player_projectile_count,
                              Projectile* up_projectiles, uint8_t up_projectile_count,
                              Projectile* down_projectiles, uint8_t down_projectile_count) {

  player_move(player, center);
  for (uint8_t i = 0; i < plane_count; i++) {
    plane_move(&planes[i]);
  }
  for (uint8_t i = 0; i < player_projectile_count; i++) {
    projectile_move(&player_projectiles[i], PROJECTILE_PLAYER);
  }
  for (uint8_t i = 0; i < up_projectile_count; i++) {
    projectile_move(&up_projectiles[i], PROJECTILE_PLANE_UP);
  }
  for (uint8_t i = 0; i < down_projectile_count; i++) {
    projectile_move(&down_projectiles[i], PROJECTILE_PLANE_DOWN);
  }
}

int handle_collisions(Player* player,
                      Building* buildings, uint8_t* building_count,
                      Plane* planes, uint8_t* plane_count,
                      Projectile* player_projectiles, uint8_t* player_projectile_count,
                      Projectile* up_projectiles, uint8_t* up_projectile_count,
                      Projectile* down_projectiles, uint8_t* down_projectile_count) {

  for (uint8_t i = 0; i < *plane_count; i++) {
    if (box_intersects_array(player->hitboxes, 2, planes[i].hitboxes, 2)) {
      plane_destroy(&planes[i]);
      return 1;
    }
  }
  for (uint8_t i = 0; i < *player_projectile_count; i++) {
    for (uint8_t j = 0; j < *plane_count; j++) {
      if (box_intersects_array(&player_projectiles[i].hitbox, 1, planes[j].hitboxes, 1)) {
        plane_destroy(&planes[j]);
        planes[j] = planes[*plane_count - 1];
        (*plane_count)--;
        j--;
      }
    }
  }
  for (uint8_t i = 0; i < *up_projectile_count; i++) {
    if (box_intersects_array(&up_projectiles[i].hitbox, 1, player->hitboxes, 2)) {
      return 1;
    }
  }
  for (uint8_t i = 0; i < *down_projectile_count; i++) {
    if (box_intersects_array(&down_projectiles[i].hitbox, 1, player->hitboxes, 2)) {
      return 1;
    }
  }
  for (uint8_t i = 0; i < *building_count; i++) {
    Box building_hb = building_hitbox(&buildings[i]);
    if (box_intersects_array(&building_hb, 1, player->hitboxes, 2)) {
      return 1;
    }
  }
  return 0;
}

int update_all(Vector* center, Player* player,
               Building* buildings, uint8_t* building_count,
               Plane* planes, uint8_t* plane_count,
               Projectile* player_projectiles, uint8_t* player_projectile_count,
               Projectile* up_projectiles, uint8_t* up_projectile_count,
               Projectile* down_projectiles, uint8_t* down_projectile_count) {

  move_center_and_entities(center, player, planes, *plane_count, player_projectiles, *player_projectile_count,
                           up_projectiles, *up_projectile_count, down_projectiles, *down_projectile_count);
  return handle_collisions(player, buildings, building_count, planes, plane_count,
                           player_projectiles, player_projectile_count, up_projectiles,
                           up_projectile_count, down_projectiles, down_projectile_count);
}
