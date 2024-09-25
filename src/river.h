#ifndef RIVER_H
#define RIVER_H

#include "geometry.h"
#include "defs.h"

void river_initialize(const Vector* center);

void river_update(const App* app);

int river_point_intersection(const Vector* p);

Vector* river_get();

#endif //RIVER_H
