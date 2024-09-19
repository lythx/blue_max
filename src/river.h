#ifndef RIVER_H
#define RIVER_H

#include "geometry.h"

void river_initialize(const Vector* center);

void river_generate_next(const Vector* center);

int river_point_intersection(const Vector* p);

Vector* river_get();

#endif //RIVER_H
