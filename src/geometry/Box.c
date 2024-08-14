#include "Box.h"
#include "../defs.h"

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

Box box_create_around_center(const Vector* center,
                             double length, double width, double height) {
  double x = center->x - length * ROTATION_COS / 2;
  double y = center->y - width / 2 - length * ROTATION_SIN / 2;
  double z = center->z - height / 2;
  return box_create(x, y, z, length, width, height);
}

int box_intersects(const Box* b1, const Box* b2) {
  if (b1->z > b2->z + b2->height || b2->z > b1->z + b1->height) {
    return 0;
  }
  Vector slope1 = vector_create(b1->length, 0.0, 0.0);
  Vector slope2 = vector_create(b2->length, 0.0, 0.0);
  vector_rotate(&slope1);
  vector_rotate(&slope2);
  if (b1->x > b2->x + slope2.x || b2->x > b1->x + slope1.x) {
    return 0;
  }
  double tang = ROTATION_SIN / ROTATION_COS;
  double y1 = b1->y - b1->x * tang;
  double y2 = b2->y - b2->x * tang;
  return (y2 <= y1 && y1 <= y2 + b2->width) ||
         (y1 <= y2 && y2 <= y1 + b1->width) ||
         (y2 <= y1 + b1->width && y1 + b1->width <= y2 + b2->width) ||
         (y1 <= y2 + b2->width && y2 + b2->width <= y1 + b1->width);
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

int box_intersects_array(const Box* arr1, uint8_t size1, const Box* arr2, uint8_t size2) {
  Vector slope1, slope2;
  for (uint8_t i = 0; i < size1; i++) {
    const Box* b1 = &arr1[i];
    slope1 = vector_create(b1->length, 0.0, 0.0);
    vector_rotate(&slope1);
    for (uint8_t j = 0; j < size2; j++) {
      const Box* b2 = &arr2[j];
      if (b1->z > b2->z + b2->height || b2->z > b1->z + b1->height) {
        continue;
      }
      slope2 = vector_create(b2->length, 0.0, 0.0);
      vector_rotate(&slope2);
      if (b1->x > b2->x + slope2.x || b2->x > b1->x + slope1.x) {
        continue;
      }
      double tang = ROTATION_SIN / ROTATION_COS;
      double y1 = b1->y - b1->x * tang;
      double y2 = b2->y - b2->x * tang;
      if ((y2 <= y1 && y1 <= y2 + b2->width) ||
             (y1 <= y2 && y2 <= y1 + b1->width) ||
             (y2 <= y1 + b1->width && y1 + b1->width <= y2 + b2->width) ||
             (y1 <= y2 + b2->width && y2 + b2->width <= y1 + b1->width)) {
        return 1;
      }
    }
  }
  return 0;
}

void box_print(const Box* b) {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
               "Box: (x, y, z, length, width, height) = (%f, %f, %f, %f, %f, %f)",
               b->x, b->y, b->z, b->length, b->width, b->height);
}
