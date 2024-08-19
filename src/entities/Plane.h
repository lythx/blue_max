#ifndef BLUE_MAX_PLANE_H
#define BLUE_MAX_PLANE_H

#include "SDL.h"
#include "../geometry.h"
#include "../defs.h"
#include "Projectile.h"

typedef enum {
    PLANE_UP = 1,
    PLANE_DOWN = 2
} PLANE_DIRECTION;

typedef struct {
    Vector pos;
    Box* hitboxes;
    int direction;
    long long last_shot_timestamp;
    SDL_Texture* texture;
} Plane;

Plane plane_create(const App* app, Vector* pos, PLANE_DIRECTION direction);

void plane_move(Plane* plane);

Projectile plane_shoot(const App* app, Plane* plane);

void plane_destroy(Plane* plane);

#endif //BLUE_MAX_PLANE_H
