#include "Sphere.h"
#include "SDL.h"

Sphere sphere_create(double x, double y, double z, double radius) {
  if (radius < 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                    "Negative radius passed to sphere_create. Data: (%f, %f, %f), %f",
                    x, y, z, radius);
    exit(1);
  }
  return (Sphere) {x, y, z, radius};
}

Sphere sphere_create_from_vector(const Vector* v, double radius) {
  return sphere_create(v->x, v->y, v->z, radius);
}

int sphere_intersects(const Sphere* s1, const Sphere* s2) {
  Vector v = vector_create(s1->x - s2->x, s1->y - s2->y, s1->z - s2->z);
  double distance = vector_norm(&v);
  return distance <= s1->radius + s2->radius;
}

int sphere_point_intersects(const Sphere* s, const Vector* p) {
  Vector v = vector_create(s->x - p->x, s->y - p->y, s->z - p->z);
  double distance = vector_norm(&v);
  return distance <= s->radius;
}

void sphere_print(const Sphere* s) {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
               "Sphere: point (%f, %f, %f), radius %f", s->x, s->y, s->z, s->radius);
}
