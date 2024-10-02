#include "Vector.h"
#include "SDL.h"
#include "math.h"
#include "../defs.h"

#define SIN ROTATION_SIN
#define COS ROTATION_COS

Vector vector_create(double x, double y, double z) {
  return (Vector) {x, y, z};
}

Vector vector_copy(const Vector* v) {
  return (Vector) {v->x, v->y, v->z};
}

void vector_negate(Vector* v) {
  v->x = -v->x;
  v->y = -v->y;
  v->z = -v->z;
}

void vector_sum(Vector* v1, const Vector* v2) {
  v1->x += v2->x;
  v1->y += v2->y;
  v1->z += v2->z;
}

void vector_subtract(Vector* v1, const Vector* v2) {
  v1->x -= v2->x;
  v1->y -= v2->y;
  v1->z -= v2->z;
}

void vector_multiply(Vector* v, double scalar) {
  v->x *= scalar;
  v->y *= scalar;
  v->z *= scalar;
}

double vector_norm(const Vector* v) {
  return sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
}

void vector_normalize(Vector* v) {
  double norm = vector_norm(v);
  if (norm == 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                    "[0, 0, 0] vector passed to vector_normalize.");
    exit(1);
  }
  vector_multiply(v, 1.0 / norm);
}

double vector_dot(const Vector* v1, const Vector* v2) {
  return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

void vector_cross(Vector* v1, const Vector* v2) {
  v1->x = v1->y * v2->z - v1->z * v2->y;
  v1->y = v1->z * v2->x - v1->x * v2->z;
  v1->z = v1->x * v2->y - v1->y * v2->x;
}

void vector_rotate(Vector* v) {
  double vx = v->x;
  v->x = v->x * COS - v->y * SIN;
  v->y = vx * SIN + v->y * COS;
}

void vector_rotate_about_origin(Vector* to_rotate, const Vector* origin) {
  double dx = to_rotate->x - origin->x;
  double dy = to_rotate->y - origin->y;
  to_rotate->x = dx * COS - dy * SIN + origin->x;
  to_rotate->y = dx * SIN + dy * COS + origin->y;
}

double vector_point_distance(const Vector* v1, const Vector* v2) {
  Vector temp = vector_copy(v1);
  vector_subtract(&temp, v2);
  return vector_norm(&temp);
}

void vector_print(const Vector* v) {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
               "[%f, %f, %f]", v->x, v->y, v->z);
}
