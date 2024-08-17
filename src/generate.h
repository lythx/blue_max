#ifndef BLUE_MAX_GENERATE_H
#define BLUE_MAX_GENERATE_H

#include "Plane.h"
#include "Building.h"

void generate_plane(const App* app, const Vector* center, Plane* planes, uint8_t* plane_count);

void generate_building(const App* app, const Vector* center, Building* buildings, uint8_t* building_count);

#endif //BLUE_MAX_GENERATE_H
