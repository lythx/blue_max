#include "river.h"
#include "defs.h"
#include "utils.h"

Vector river[RIVER_SEGMENT_COUNT];

Vector next_point(const Vector* center, Vector* v) {
  double x = rand_min_max(RIVER_MIN_SEGMENT_LENGTH, RIVER_MAX_SEGMENT_LENGTH);
  double y = rand_min_max(-RIVER_MAX_SEGMENT_WIDTH, RIVER_MAX_SEGMENT_WIDTH);
  Vector diff = vector_create(x, y, 0);
  vector_rotate(&diff);
  vector_sum(v, &diff);
  double tan = ROTATION_SIN / ROTATION_COS;
  double spawn_center_y = center->y + (v->x - center->x) * tan;
  if (v->y < spawn_center_y - RIVER_LEFT_BOUND) {
    v->y = spawn_center_y - RIVER_LEFT_BOUND;
  } else if (v->y > spawn_center_y + RIVER_RIGHT_BOUND) {
    v->y = spawn_center_y + RIVER_RIGHT_BOUND;
  }
}

void river_initialize(const Vector* center) {
  Vector pos;
  pos = vector_create(-SPAWN_DISTANCE_TO_CENTER, RIVER_START_Y_OFFSET, 0);
  vector_rotate(&pos);
  vector_sum(&pos, center);
  river[0] = pos;
  for (size_t i = 1; i < RIVER_SEGMENT_COUNT; i++) {
    next_point(center, &pos);
    river[i] = vector_copy(&pos);
  }
}

void river_generate_next(const Vector* center) {
  Vector last = vector_copy(&river[RIVER_SEGMENT_COUNT - 1]);
  for (size_t i = 0; i < RIVER_SEGMENT_COUNT - 1; i++) {
    river[i] = river[i + 1];
  }
  next_point(center, &last);
  river[RIVER_SEGMENT_COUNT - 1] = vector_create(last.x, last.y, 0);
}

void river_update(const App* app) {
  Vector v = vector_create(SPAWN_DISTANCE_TO_CENTER, 0, 0);
  vector_rotate(&v);
  if (river[RIVER_SEGMENT_COUNT - 1].y < app->center.y + v.x) {
    river_generate_next(&app->center);
  }
}

int search_compare(const void* a, const void* b) {
  return ((Box*) a)->y <= ((Vector*) b)->y ? 1 : -1;
}

int sat_collision(const Vector* pos1, const Vector* slope1, const Vector* base1,
                  const Vector* pos2, const Vector* slope2, const Vector* base2)  {
  // TODO
  return 0;
}

int river_box_intersection(const Box* b) {
  Vector* v = bsearch(b, river, RIVER_SEGMENT_COUNT, sizeof(Vector), search_compare);
  Vector box_pos = vector_create(b->x, b->y, 0);
  Vector box_slope = vector_create(b->length, 0, 0);
  vector_rotate(&box_slope);
  Vector box_base = vector_create(0, b->width, 0);
  Vector river_base = vector_create(0, RIVER_WIDTH, 0);
  while (b->y + b->length < v->y && v + 1 < river + RIVER_SEGMENT_COUNT) {
    Vector slope = vector_copy(v + 1);
    vector_subtract(&slope, v);
    if (sat_collision(&box_pos, &box_slope, &box_base, v, &slope, &river_base)) {
      return 1;
    }
    v++;
  }
  return 0;
}

Vector* river_get() {
  return river;
}
