#include "update.h"

void move_center_and_entities(Vector* center, Player* player,
                              Plane* planes, uint8_t plane_count,
                              Projectile* player_projectiles, uint8_t player_projectile_count,
                              Projectile* plane_projectiles, uint8_t plane_projectile_count) {

  player_move(player, center);
  for (uint8_t i = 0; i < plane_count; i++) {
    plane_move(&planes[i]);
  }
  for (uint8_t i = 0; i < player_projectile_count; i++) {
    projectile_move(&player_projectiles[i]);
  }
  for (uint8_t i = 0; i < plane_projectile_count; i++) {
    projectile_move(&plane_projectiles[i]);
  }
}

int handle_collisions(Player* player,
                      Building* buildings, uint8_t* building_count,
                      Plane* planes, uint8_t* plane_count,
                      Projectile* player_projectiles, uint8_t* player_projectile_count,
                      Projectile* plane_projectiles, uint8_t* plane_projectile_count,
                      Tree* trees, uint8_t* tree_count) {
  for (uint8_t i = 0; i < *plane_count; i++) {
    if (box_intersects_array(player->hitboxes, 2, planes[i].hitboxes, 2)) {
      plane_destroy(&planes[i]);
      return 1;
    }
  }
  for (uint8_t i = 0; i < *player_projectile_count; i++) {
    for (uint8_t j = 0; j < *plane_count; j++) {
      if (box_intersects_array(&player_projectiles[i].hitbox, 1, planes[j].hitboxes, 1)) {
        player_projectiles[i] = player_projectiles[*player_projectile_count - 1];
        (*player_projectile_count)--;
        i--;
        plane_destroy(&planes[j]);
        planes[j] = planes[*plane_count - 1];
        (*plane_count)--;
        j--;
      }
    }
  }
  for (uint8_t i = 0; i < *plane_projectile_count; i++) {
    if (box_intersects_array(&plane_projectiles[i].hitbox, 1, player->hitboxes, 2)) {
      return 1;
    }
  }
  for (uint8_t i = 0; i < *building_count; i++) {
    Box building_hb = building_hitbox(&buildings[i]);
    if (box_intersects_array(&building_hb, 1, player->hitboxes, 2)) {
      return 1;
    }
  }
  for (uint8_t i = 0; i < *tree_count; i++) {
    Box tree_hb = tree_hitbox(&trees[i]);
    if (box_intersects_array(&tree_hb, 1, player->hitboxes, 2)) {
      return 1;
    }
  }
  return 0;
}

int should_unload(Vector* pos, const Vector* center) {
  pos->z = 0;
  vector_subtract(pos, center);
  return vector_norm(pos) > UNLOAD_DISTANCE_TO_CENTER;
}

void unload_off_camera(const Vector* center,
                       Building* buildings, uint8_t* building_count,
                       Plane* planes, uint8_t* plane_count,
                       Projectile* player_projectiles, uint8_t* player_projectile_count,
                       Projectile* plane_projectiles, uint8_t* plane_projectile_count,
                       Tree* trees, uint8_t* tree_count) {
  Vector v;
  for (uint8_t i = 0; i < *plane_count; i++) {
    v = vector_copy(&planes[i].pos);
    if (should_unload(&v, center)) {
      plane_destroy(&planes[i]);
      planes[i] = planes[*plane_count - 1];
      (*plane_count)--;
      i--;
    }
  }
  for (uint8_t i = 0; i < *player_projectile_count; i++) {
    v = vector_copy(&player_projectiles[i].pos);
    if (should_unload(&v, center)) {
      player_projectiles[i] = player_projectiles[*player_projectile_count - 1];
      (*player_projectile_count)--;
      i--;
    }
  }
  for (uint8_t i = 0; i < *plane_projectile_count; i++) {
    v = vector_copy(&plane_projectiles[i].pos);
    if (should_unload(&v, center)) {
      plane_projectiles[i] = plane_projectiles[*plane_projectile_count - 1];
      (*plane_projectile_count)--;
      i--;
    }
  }
  for (uint8_t i = 0; i < *building_count; i++) {
    v = vector_create(buildings[i].x, buildings[i].y, 0);
    if (should_unload(&v, center)) {
      buildings[i] = buildings[*building_count - 1];
      (*building_count)--;
      i--;
    }
  }
  for (uint8_t i = 0; i < *tree_count; i++) {
    v = vector_create(trees[i].x, trees[i].y, 0);
    if (should_unload(&v, center)) {
      trees[i] = trees[*tree_count - 1];
      (*tree_count)--;
      i--;
    }
  }
}

int update_all(Vector* center, Player* player,
               Building* buildings, uint8_t* building_count,
               Plane* planes, uint8_t* plane_count,
               Projectile* player_projectiles, uint8_t* player_projectile_count,
               Projectile* plane_projectiles, uint8_t* plane_projectile_count,
               Tree* trees, uint8_t* tree_count) {

  move_center_and_entities(center, player, planes, *plane_count, player_projectiles, *player_projectile_count,
                           plane_projectiles, *plane_projectile_count);
  if (handle_collisions(player, buildings, building_count, planes, plane_count,
                           player_projectiles, player_projectile_count, plane_projectiles, plane_projectile_count,
                           trees, tree_count)) {
    return 1;
  }
  unload_off_camera(center, buildings, building_count, planes, plane_count,
                    player_projectiles, player_projectile_count, plane_projectiles, plane_projectile_count,
                    trees, tree_count);
  return 0;
}
