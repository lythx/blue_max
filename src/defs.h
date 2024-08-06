#ifndef BLUE_MAX_DEFS_H
#define BLUE_MAX_DEFS_H

#include "SDL.h"

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

#define ROTATION_SIN 0.5
#define ROTATION_COS 0.8660254
#define HEIGHT_Y_OFFSET (-0.4)

#endif //BLUE_MAX_DEFS_H
