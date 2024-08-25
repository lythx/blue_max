#ifndef BLUE_MAX_GENERATE_H
#define BLUE_MAX_GENERATE_H

#include "entities.h"

void generate_plane(const App* app, const Vector* center, Plane* planes, uint8_t* plane_count);

void generate_building(const App* app, const Vector* center, Building* buildings, uint8_t* building_count);

void generate_plane_shots(const App* app, Plane* planes, const uint8_t* plane_count,
                          Projectile* plane_projectiles, uint8_t* plane_projectile_count);

void generate_trees(const App* app, const Vector* center, Tree* trees, uint8_t* tree_count,
                    const Building* buildings, uint8_t building_count);

#endif //BLUE_MAX_GENERATE_H
