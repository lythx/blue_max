#include "generate.h"
#include "stdlib.h"
#include "utils.h"

typedef enum {
    UP = 1,
    DOWN = 2
} DIRECTION;

Vector get_random_position(const Vector* center, DIRECTION direction);

void generate_plane(const App* app, const Vector* center, Plane* planes, uint8_t* plane_count) {
  if (*plane_count == MAX_PLANES) {
    return;
  }
  int r = rand();
  if (r > SPAWN_PLANE_CHANCE * RAND_MAX) {
    return;
  }
  PLANE_DIRECTION direction = PLANE_DOWN;
  // 50% chance the plane gets spawned up
  if (r < (SPAWN_PLANE_CHANCE / 2) * RAND_MAX) {
    direction = PLANE_UP;
  }
  Vector pos;
  int collision;
  do {
    collision = 0;
    pos = get_random_position(center, direction == PLANE_DOWN ? UP : DOWN);
    Box path = box_create_around_center(&pos, SPAWN_DISTANCE_TO_CENTER * 5, PLANE_WINGS_WIDTH, PLANE_BODY_HEIGHT);
    for (uint8_t i = 0; i < *plane_count; i++) {
      if (box_intersects_array(planes[i].hitboxes, 2, &path, 1)) {
        collision = 1;
        break;
      }
    }
  } while(collision);
  planes[*plane_count] = plane_create(app, &pos, direction);
  (*plane_count)++;
}

void generate_building(const App* app, const Vector* center, Building* buildings, uint8_t* building_count) {
  if (*building_count == MAX_BUILDINGS || rand() > SPAWN_BUILDING_CHANCE * RAND_MAX) {
    return;
  }
  Vector pos;
  int too_close;
  do {
    too_close = 0;
    pos = get_random_position(center, UP);
    pos.z = 0;
    for (uint8_t i = 0; i < *building_count; i++) {
      Vector diff = vector_create(buildings[i].x, buildings[i].y, 0);
      vector_subtract(&diff, &pos);
      if (vector_norm(&diff) < SPAWN_BUILDING_MIN_DISTANCE) {
        too_close = 1;
        break;
      }
    }
  } while(too_close);
  buildings[*building_count] = building_create(app, pos.x, pos.y, 100.0, 100.0, 100.0);
  (*building_count)++;
}

void generate_plane_shots(const App* app, Plane* planes, const uint8_t* plane_count,
                          Projectile* plane_projectiles, uint8_t* plane_projectile_count) {
  long long t = time_ms();
  for (uint8_t i = 0; i < *plane_count; i++) {
    if (t - planes[i].last_shot_timestamp < PLANE_RELOAD_TIME_MS) {
      continue;
    }
    if (rand() <= PLANE_SHOOT_CHANCE * RAND_MAX) {
      plane_projectiles[*plane_projectile_count] = plane_shoot(app, &planes[i]);
      (*plane_projectile_count)++;
    }
  }
}

Vector get_random_position(const Vector* center, DIRECTION direction) {
  Vector diff = vector_create(direction == UP ? SPAWN_DISTANCE_TO_CENTER : -SPAWN_DISTANCE_TO_CENTER, 0, 0);
  vector_rotate(&diff);
  Vector spawn = vector_copy(center);
  vector_sum(&spawn, &diff);
  double horizontal_range = PLAYER_HORIZONTAL_BOUND * 2;
  double horizontal_offset = ((double) rand() / RAND_MAX) * horizontal_range - PLAYER_HORIZONTAL_BOUND;
  double vertical_range = PLAYER_UP_BOUND - SPAWN_PLANE_MIN_HEIGHT;
  double vertical_offset = ((double) rand() / RAND_MAX) * vertical_range;
  Vector offset = vector_create(0, horizontal_offset, vertical_offset);
  vector_sum(&spawn, &offset);
  return spawn;
}
