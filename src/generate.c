#include "generate.h"
#include "utils.h"
#include "config.h"

typedef enum {
    UP = 1,
    DOWN = 2
} DIRECTION;

Vector get_random_position(const Vector* center, DIRECTION direction);

void generate_plane(const App* app, Plane* planes, uint8_t* plane_count) {
  if (*plane_count == MAX_PLANES) {
    return;
  }
  double r = rand_0_1();
  if (r > SPAWN_PLANE_CHANCE) {
    return;
  }
  PLANE_DIRECTION direction = PLANE_DOWN;
  // 50% chance the plane gets spawned up
  if (r < (double) SPAWN_PLANE_CHANCE / 2) {
    direction = PLANE_UP;
  }
  Vector pos;
  int collision;
  do {
    collision = 0;
    pos = get_random_position(&app->center, direction == PLANE_DOWN ? UP : DOWN);
    Box path = box_create_around_center(&pos, SPAWN_DISTANCE_TO_CENTER * 5, PLANE_WINGS_WIDTH, PLANE_BODY_HEIGHT);
    for (uint8_t i = 0; i < *plane_count; i++) {
      if (box_intersects_array(planes[i].hitboxes, 2, &path, 1)) {
        collision = 1;
        break;
      }
    }
  } while(collision);
  planes[*plane_count] = plane_create(&pos, direction);
  (*plane_count)++;
}

void generate_building(const App* app, Building* buildings, uint8_t* building_count) {
  if (*building_count == MAX_BUILDINGS || rand_0_1() > SPAWN_BUILDING_CHANCE) {
    return;
  }
  Vector pos;
  int too_close;
  int tries = 0;
  do {
    tries++;
    too_close = 0;
    pos = get_random_position(&app->center, UP);
    pos.z = 0;
    for (uint8_t i = 0; i < *building_count; i++) {
      Vector diff = vector_create(buildings[i].x, buildings[i].y, 0);
      vector_subtract(&diff, &pos);
      if (vector_norm(&diff) < SPAWN_BUILDING_MIN_DISTANCE) {
        too_close = 1;
        break;
      }
    }
  } while(too_close && tries < 3);
  buildings[*building_count] = building_create(pos.x, pos.y, BUILDING_LENGTH, BUILDING_WIDTH, BUILDING_HEIGHT);
  (*building_count)++;
}

void generate_plane_shots(Plane* planes, const uint8_t* plane_count,
                          Projectile* plane_projectiles, uint8_t* plane_projectile_count) {
  long long t = time_ms();
  for (uint8_t i = 0; i < *plane_count; i++) {
    if (t - planes[i].last_shot_timestamp < PLANE_RELOAD_TIME_MS) {
      continue;
    }
    if (rand_0_1() <= PLANE_SHOOT_CHANCE) {
      plane_projectiles[*plane_projectile_count] = plane_shoot(&planes[i]);
      (*plane_projectile_count)++;
    }
  }
}

void generate_trees(const App* app, Tree* trees, uint8_t* tree_count,
                    const Building* buildings, uint8_t building_count) {
  static double last_tree_generation_x = 0.0;
  if (app->center.x - last_tree_generation_x < TREE_DEFAULT_DISTANCE) {
    return;
  }
  last_tree_generation_x = app->center.x;
  Vector mid = vector_create(SPAWN_DISTANCE_TO_CENTER, 0, 0);
  vector_rotate(&mid);
  vector_sum(&mid, &app->center);
  double y = mid.y - WINDOW_WIDTH;
  while (y < mid.y + WINDOW_WIDTH + TREE_DEFAULT_DISTANCE) {
    double x_offset = rand_min_max(-TREE_MAX_OFFSET, TREE_MAX_OFFSET);
    double y_offset = rand_min_max(-TREE_MAX_OFFSET, TREE_MAX_OFFSET);
    Tree tree = tree_create(mid.x + x_offset, y + y_offset);
    Box tree_hb = tree_spawn_area(&tree);
    int is_colliding = 0;
    for (uint8_t i = 0; i < building_count; i++) {
      Box building_hb = building_hitbox(&buildings[i]);
      if (box_intersects(&tree_hb, &building_hb)) {
        is_colliding = 1;
      }
    }
    if (is_colliding) {
      continue;
    }
    trees[*tree_count] = tree;
    (*tree_count)++;
    y += TREE_DEFAULT_DISTANCE;
  }
}

Vector get_random_position(const Vector* center, DIRECTION direction) {
  Vector diff = vector_create(direction == UP ? SPAWN_DISTANCE_TO_CENTER : -SPAWN_DISTANCE_TO_CENTER, 0, 0);
  vector_rotate(&diff);
  Vector spawn = vector_copy(center);
  vector_sum(&spawn, &diff);
  double horizontal_offset = rand_min_max(-PLAYER_HORIZONTAL_BOUND, PLAYER_HORIZONTAL_BOUND);
  double vertical_offset = rand_min_max(SPAWN_PLANE_MIN_HEIGHT, PLAYER_UP_BOUND);
  Vector offset = vector_create(0, horizontal_offset, vertical_offset);
  vector_sum(&spawn, &offset);
  return spawn;
}
