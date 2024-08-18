#ifndef BLUE_MAX_UPDATE_H
#define BLUE_MAX_UPDATE_H

#include "geometry.h"
#include "entities.h"

int update_all(Vector* center, Player* player,
               Building* buildings, uint8_t* building_count,
               Plane* planes, uint8_t* plane_count,
               Projectile* player_projectiles, uint8_t* player_projectile_count,
               Projectile* up_projectiles, uint8_t* up_projectiles_count,
               Projectile* down_projectiles, uint8_t* down_projectiles_count);

#endif //BLUE_MAX_UPDATE_H
