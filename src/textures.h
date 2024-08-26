#ifndef BLUE_MAX_TEXTURES_H
#define BLUE_MAX_TEXTURES_H

#include "SDL.h"
#include "defs.h"

typedef enum {
    TEXTURE_PLAYER = 0,
    TEXTURE_PLAYER_LEFT = 1,
    TEXTURE_PLAYER_RIGHT = 2,
    TEXTURE_PLANE = 3,
    TEXTURE_PLANE_LEFT = 4,
    TEXTURE_PLANE_RIGHT = 5,
    TEXTURE_TREE = 6,
    TEXTURE_PROJECTILE = 7,
    TEXTURE_BUILDING = 8
} TEXTURE;

void init_textures(const App* app);

SDL_Texture* get_texture(TEXTURE texture);

#endif //BLUE_MAX_TEXTURES_H
