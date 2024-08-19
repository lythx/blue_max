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
    PROJECTILE_ORIGIN origin;
} Projectile;

Projectile projectile_create(const App* app, Vector* pos, PROJECTILE_ORIGIN origin);

void projectile_move(Projectile* projectile);

#endif //BLUE_MAX_PROJECTILE_H
