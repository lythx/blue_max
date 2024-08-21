#ifndef BLUE_MAX_INPUT_H
#define BLUE_MAX_INPUT_H

#include "defs.h"
#include "entities.h"

int handle_input(const App* app, SDL_Event* event, Player* player,
                 Projectile* player_projectiles, uint8_t* player_projectile_count);

#endif //BLUE_MAX_INPUT_H
