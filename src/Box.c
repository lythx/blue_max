#include "Box.h"
#include "SDL.h"

Box box_create(double min_x, double min_y, double min_z,
               double max_x, double max_y, double max_z) {
  if(min_x > max_x || min_y > max_y || min_z > max_z) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                    "min value greater then max value in box_create. Data: min: (%f, %f %f), max: (%f, %f, %f)",
                    min_x, min_y, min_z, max_x, max_y, max_z);
    exit(1);
  }
  return (Box) {min_x, min_y, min_z, max_x, max_y, max_z};
}

Box box_create_from_vectors(const Vector* min, const Vector* max) {
  return box_create(min->x, min->y, min->z, max->x, max->y, max->z);
}

int box_intersects(const Box* b1, const Box* b2) {
  return b1->min_x <= b2->max_x &&
         b1->max_x >= b2->min_x &&
         b1->min_y <= b2->max_y &&
         b1->max_y >= b2->min_y &&
         b1->min_z <= b2->max_z &&
         b1->max_z >= b2->min_z;
}

int box_point_intersects(const Box* b, const Vector* p) {
  return (b->min_x <= p->x && p->x <= b->max_x) &&
         (b->min_y <= p->y && p->y <= b->max_y) &&
         (b->min_z <= p->z && p->z <= b->max_z);
}

void box_print(const Box* b) {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
               "Box: min (%f, %f, %f), max (%f, %f, %f)",
               b->min_x, b->min_y, b->min_z, b->max_x, b->max_y, b->max_z);
}
