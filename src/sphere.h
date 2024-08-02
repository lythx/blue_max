#ifndef BLUE_MAX_SPHERE_H
#define BLUE_MAX_SPHERE_H

#include "vector.h"

typedef struct {
    double x;
    double y;
    double z;
    double radius;
} sphere;

sphere sphere_create(double x, double y, double z, double radius);

sphere sphere_create_from_vector(const vector* v, double radius);

int sphere_intersects(const sphere* s1, const sphere* s2);

int sphere_point_intersects(const sphere* s, const vector* p);

void sphere_print(const sphere* s);

#endif //BLUE_MAX_SPHERE_H
