#ifndef BLUE_MAX_PROJECTILE_H
#define BLUE_MAX_PROJECTILE_H

#include "../defs.h"
#include "SDL.h"
#include "../geometry.h"

typedef enum {
    PROJECTILE_PLAYER = 0,
    PROJECTILE_PLANE_UP = 1,
    PROJECTILE_PLANE_DOWN = 2
} PROJECTILE_ORIGIN;

typedef struct {
    Vector pos;
    Box hitbox;
    SDL_Texture* texture;
} Projectile;

Projectile projectile_create(const App* app, Vector* pos);

void projectile_move(Projectile* projectile, PROJECTILE_ORIGIN origin);

#endif //BLUE_MAX_PROJECTILE_H
