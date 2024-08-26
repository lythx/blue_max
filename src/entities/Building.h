#ifndef BLUE_MAX_BUILDING_H
#define BLUE_MAX_BUILDING_H

#include "SDL.h"
#include "../geometry.h"
#include "../defs.h"

typedef struct {
    double x;
    double y;
    double length;
    double width;
    double height;
    SDL_Texture* texture;
} Building;

Building building_create(double x, double y, double length, double width, double height);

Box building_hitbox(const Building* building);

#endif //BLUE_MAX_BUILDING_H
