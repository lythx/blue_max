#ifndef BLUE_MAX_TEXTURES_H
#define BLUE_MAX_TEXTURES_H

#include "SDL.h"
#include "defs.h"

typedef enum {
    TEXTURE_PLAYER_1 = 0,
    TEXTURE_PLAYER_LEFT_1 = 1,
    TEXTURE_PLAYER_RIGHT_1 = 2,
    TEXTURE_PLAYER_2 = 3,
    TEXTURE_PLAYER_LEFT_2 = 4,
    TEXTURE_PLAYER_RIGHT_2 = 5,
    TEXTURE_PLANE_1 = 10,
    TEXTURE_PLANE_2 = 11,
    TEXTURE_PLANE_LEFT = 12,
    TEXTURE_PLANE_RIGHT = 15,
    TEXTURE_TREE = 6,
    TEXTURE_PROJECTILE = 7,
    TEXTURE_BUILDING = 8,
    TEXTURE_AIRPORT = 14
} TEXTURE;

void init_textures(const App* app);

SDL_Texture* get_texture(TEXTURE texture);

#endif //BLUE_MAX_TEXTURES_H
