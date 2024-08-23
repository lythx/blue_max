#ifndef BLUE_MAX_RENDER_H
#define BLUE_MAX_RENDER_H

#include "geometry.h"
#include "defs.h"
#include "entities.h"

void render_all(const App* app, const Vector* center, const Player* player,
                const Building* buildings, uint8_t building_count,
                const Plane* planes, uint8_t plane_count,
                const Projectile* player_projectiles, uint8_t player_projectile_count,
                const Projectile* plane_projectiles, uint8_t plane_projectile_count,
                const Tree* trees, uint8_t tree_count);

#endif //BLUE_MAX_RENDER_H
