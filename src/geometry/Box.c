#include "Box.h"
#include "SDL.h"

Box box_create(double x, double y, double z,
               double length, double width, double height) {
  if(length < 0 || width < 0 || height < 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                    "negative dimension in box_create. Data: (x, y, z, length, width, height) = (%f, %f, %f, %f, %f, %f)",
                    length ,width, height, x, y, z);
    exit(1);
  }
  return (Box) {x, y, z, length, width, height};
}

int box_intersects(const Box* b1, const Box* b2) {
  return b1->x <= b2->x + b2->length &&
         b1->x + b1->length >= b2->x &&
         b1->y <= b2->y + b2->width &&
         b1->y + b1->width >= b2->y &&
         b1->z <= b2->z + b2->height &&
         b1->z + b1->height >= b2->z;
}

int box_point_intersects(const Box* b, const Vector* p) {
  if (p->x < b->x || p->z < b->z || p->z > b->z + b->height) {
    return 0;
  }
  Vector slope = vector_create(b->length, 0.0, 0.0);
  vector_rotate(&slope);
  if (p->x > b->x + slope.x) {
    return 0;
  }
  double y_min = b->y + ((p->x - b->x) * slope.y) / slope.x;
  return y_min <= p->y && p->y <= y_min + b->width;
}

void box_print(const Box* b) {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
               "Box: (x, y, z, length, width, height) = (%f, %f, %f, %f, %f, %f)",
               b->x, b->y, b->z, b->length, b->width, b->height);
}