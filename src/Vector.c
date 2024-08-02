#include "Vector.h"
#include "SDL.h"
#include "math.h"

Vector vector_create(double x, double y, double z) {
  return (Vector) {x, y, z};
}

Vector vector_sum(const Vector* v1, const Vector* v2) {
  return vector_create(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
}

Vector vector_multiply(const Vector* v, double scalar) {
  return vector_create(scalar * v->x, scalar * v->y, scalar * v->z);
}

double vector_norm(const Vector* v) {
  return sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
}

Vector vector_normalize(const Vector* v) {
  double norm = vector_norm(v);
  if (norm == 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                    "[0, 0, 0] vector passed to vector_normalize.");
    exit(1);
  }
  return vector_multiply(v, 1.0 / norm);
}

double vector_dot_product(const Vector* v1, const Vector* v2) {
  return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

Vector vector_cross_product(const Vector* v1, const Vector* v2) {
  return vector_create(v1->y * v2->z - v1->z * v2->y,
                       v1->z * v2->x - v1->x * v2->z,
                       v1->x * v2->y - v1->y * v2->x);
}

void vector_print(const Vector* v) {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
               "[%f, %f, %f]", v->x, v->y, v->z);
}
