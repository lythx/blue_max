#ifndef RIVER_H
#define RIVER_H

#include "geometry.h"
#include "defs.h"

void river_initialize(const Vector* center);

void river_update(const App* app);

int river_box_intersection(const Box* b);

Vector* river_get();

#endif //RIVER_H
