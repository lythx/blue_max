#ifndef BLUE_MAX_DEFS_H
#define BLUE_MAX_DEFS_H

#include "SDL.h"

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

#define ROTATION_SIN 0.68199836
#define ROTATION_COS 0.7313537
#define HEIGHT_Y_OFFSET (-0.7)
#define PLANE_BODY_LENGTH 80.0
#define PLANE_BODY_WIDTH 20.0
#define PLANE_BODY_HEIGHT 30.0
#define PLANE_WINGS_LENGTH 10.0
#define PLANE_WINGS_HEIGHT 20.0
#define PLANE_WINGS_WIDTH 80.0

#define PLAYER_HORIZONTAL_SPEED 0.1
#define PLAYER_VERTICAL_SPEED 0.1

#endif //BLUE_MAX_DEFS_H
