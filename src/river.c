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
  return ((Vector*) a)->x <= ((Vector*) b)->x ? 1 : -1;
}

int river_point_intersection(const Vector* p) {
  Vector* v1 = bsearch(p, river, RIVER_SEGMENT_COUNT, sizeof(Vector), search_compare);
  Vector* v2 = v1 + 1;
  Vector slope = vector_copy(v2);
  vector_subtract(&slope, v1);
  double y_min = v1->y + (p->x - v1->x) * slope.y / slope.x;
  return y_min <= p->y && p->y <= y_min + RIVER_WIDTH;
}

Vector* river_get() {
  return river;
}
