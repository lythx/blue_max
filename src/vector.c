#include "vector.h"
#include "SDL.h"
#include "math.h"

vector vector_create(double x, double y, double z) {
  return (vector) {x, y, z};
}

vector vector_sum(const vector* v1, const vector* v2) {
  return vector_create(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
}

vector vector_multiply(const vector* v, double scalar) {
  return vector_create(scalar * v->x, scalar * v->y, scalar * v->z);
}

double vector_norm(const vector* v) {
  return sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
}

vector vector_normalize(const vector* v) {
  double norm = vector_norm(v);
  if (norm == 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                    "[0, 0, 0] vector passed to vector_normalize.");
    exit(1);
  }
  return vector_multiply(v, 1.0 / norm);
}

double vector_dot_product(const vector* v1, const vector* v2) {
  return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

vector vector_cross_product(const vector* v1, const vector* v2) {
  return vector_create(v1->y * v2->z - v1->z * v2->y,
                       v1->z * v2->x - v1->x * v2->z,
                       v1->x * v2->y - v1->y * v2->x);
}

void vector_print(const vector* v) {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
               "[%f, %f, %f]", v->x, v->y, v->z);
}
