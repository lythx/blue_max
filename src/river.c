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
  return ((Vector*) a)->y <= ((Vector*) b)->y ? 1 : -1;
}

void get_points(Vector* points, const Vector* pos, const Vector* slope, const Vector* base) {
  points[0] = vector_copy(pos);
  points[1] = vector_copy(pos);
  vector_sum(&points[1], base);
  points[2] = vector_copy(&points[1]);
  vector_sum(&points[2], slope);
  points[3] = vector_copy(pos);
  vector_sum(&points[3], slope);
}

void get_projection(double* min, double* max, const Vector* normal, const Vector* points) {
  double dot;
  for (uint8_t i = 0; i < 4; i++) {
    dot = vector_dot(points, normal);
    if (dot < *min) {
      *min = dot;
    } else if (dot > *max) {
      *max = dot;
    }
  }
}

int sat_collision(const Vector* pos1, const Vector* slope1, const Vector* base1,
                  const Vector* pos2, const Vector* slope2, const Vector* base2)  {
  double min1, min2, max1, max2;
  Vector normal, points1[4], points2[4];
  // y-axis projection
  min1 = min_d(pos1->y, pos1->y + slope1->y);
  max1 = max_d(pos1->y + base1->y, pos1->y + base1->y + slope1->y);
  min2 = min_d(pos2->y, pos2->y + slope2->y);
  max2 = max_d(pos2->y + base2->y, pos2->y + base2->y + slope2->y);
  if (max1 < min2 || max2 < min1) {
    return 0;
  }

  get_points(points1, pos1, slope1, base1);
  get_points(points2, pos2, slope2, base2);

  // slope1 projection
  min1 = min2 = 1e10;
  max1 = max2 = -1e10;
  normal = vector_create(slope1->y, -slope1->x, 0);
  vector_normalize(&normal);
  get_projection(&min1, &max1, &normal, points1);
  get_projection(&min2, &max2, &normal, points2);
  if (max1 < min2 || max2 < min1) {
    return 0;
  }

  // slope2 projection
  min1 = min2 = 1e10;
  max1 = max2 = -1e10;
  normal = vector_create(slope2->y, -slope2->x, 0);
  vector_normalize(&normal);
  get_projection(&min1, &max1, &normal, points1);
  get_projection(&min2, &max2, &normal, points2);
  if (max1 < min2 || max2 < min1) {
    return 0;
  }
  return 1;
}

int river_box_intersection(const Box* b) {
  Vector key = vector_create(0, b->y, 0);
  int i = binary_search(&key, river, RIVER_SEGMENT_COUNT, sizeof(Vector), search_compare);
  Vector box_pos = vector_create(b->x, b->y, 0);
  Vector box_slope = vector_create(b->length, 0, 0);
  vector_rotate(&box_slope);
  Vector box_base = vector_create(0, b->width, 0);
  Vector river_base = vector_create(0, RIVER_WIDTH, 0);
  while (i + 1 < RIVER_SEGMENT_COUNT && river[i].y < box_pos.y + box_slope.y) {
    Vector slope = vector_copy(&river[i + 1]);
    vector_subtract(&slope, &river[i]);
    if (sat_collision(&box_pos, &box_slope, &box_base, &river[i], &slope, &river_base)) {
      return 1;
    }
    i++;
  }
  return 0;
}

Vector* river_get() {
  return river;
}
