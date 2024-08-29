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
    long long last_texture_change;
    int texture_type;
} Plane;

Plane plane_create(Vector* pos, PLANE_DIRECTION direction);

void plane_move(Plane* plane);

Projectile plane_shoot(Plane* plane);

SDL_Texture* plane_get_texture(const Plane* plane);

void plane_destroy(Plane* plane);

#endif //BLUE_MAX_PLANE_H
