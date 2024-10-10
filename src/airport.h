#ifndef BLUE_MAX_AIRPORT_H
#define BLUE_MAX_AIRPORT_H

#include "defs.h"
#include "entities.h"

typedef enum {
    AIRPORT_LEFT = 0,
    AIRPORT_RIGHT = 1
} AIRPORT_SIDE;

typedef struct {
    double x;
    AIRPORT_SIDE side;
} Airport;

void airport_initialize();

Vector airport_get_pos(const App* app);

Box airport_get_hitbox(const App* app);

void airport_update(const App* app);

SDL_Texture* airport_get_texture(int* width, int* height);

#endif //BLUE_MAX_AIRPORT_H
