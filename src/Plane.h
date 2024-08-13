#ifndef BLUE_MAX_PLANE_H
#define BLUE_MAX_PLANE_H

#include "SDL.h"
#include "geometry.h"
#include "defs.h"

typedef enum {
    PLANE_UP = 1,
    PLANE_DOWN = 2
} PLANE_DIRECTION;

typedef struct {
    Vector pos;
    Box* hitboxes;
    int direction;
    SDL_Texture* texture;
} Plane;

Plane plane_create(const App* app, Vector* pos);

void plane_move(Plane* plane);

void plane_destroy(Plane* plane);

#endif //BLUE_MAX_PLANE_H
