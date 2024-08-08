#ifndef BLUE_MAX_DEFS_H
#define BLUE_MAX_DEFS_H

#include "SDL.h"

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

#define ROTATION_SIN 0.5
#define ROTATION_COS 0.8660254
#define HEIGHT_Y_OFFSET (-0.7)
#define PLANE_BODY_LENGTH 300.0
#define PLANE_BODY_WIDTH 50.0
#define PLANE_BODY_HEIGHT 50.0
#define PLANE_WINGS_LENGTH 50.0
#define PLANE_WINGS_HEIGHT 20.0
#define PLANE_WINGS_WIDTH 400.0

#endif //BLUE_MAX_DEFS_H
