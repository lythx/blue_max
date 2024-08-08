#ifndef BLUE_MAX_SPHERE_H
#define BLUE_MAX_SPHERE_H

#include "Vector.h"

typedef struct {
    double x;
    double y;
    double z;
    double radius;
} Sphere;

Sphere sphere_create(double x, double y, double z, double radius);

Sphere sphere_create_from_vector(const Vector* v, double radius);

int sphere_intersects(const Sphere* s1, const Sphere* s2);

int sphere_point_intersects(const Sphere* s, const Vector* p);

void sphere_print(const Sphere* s);

#endif //BLUE_MAX_SPHERE_H
