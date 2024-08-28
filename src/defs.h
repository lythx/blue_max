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
#define PLANE_UP_SPEED 6.0
#define PLANE_DOWN_SPEED 3.0

#define MAX_PLANES 4
#define MAX_PROJECTILES 128
#define MAX_BUILDINGS 4
#define MAX_TREES 256

#define PLAYER_FORWARD_SPEED 3.0
#define PLAYER_HORIZONTAL_SPEED 4.5
#define PLAYER_VERTICAL_SPEED 4.5
#define PLAYER_HORIZONTAL_BOUND 300.0
#define PLAYER_UP_BOUND 300.0

#define PROJECTILE_SPEED_PLAYER 15.5
#define PROJECTILE_SPEED_UP 10.0
#define PROJECTILE_SPEED_DOWN 7.0
#define PROJECTILE_LENGTH 30.0
#define PROJECTILE_DIAMETER 5.0
#define PLANE_RELOAD_TIME_MS 1300
#define PLANE_SHOOT_CHANCE 0.2

#define SPAWN_DISTANCE_TO_CENTER 600.0
#define SPAWN_PLANE_CHANCE 0.005
#define SPAWN_PLANE_MIN_HEIGHT 100.0
#define SPAWN_BUILDING_CHANCE 0.002
#define SPAWN_BUILDING_MIN_DISTANCE 400.0

#define UNLOAD_DISTANCE_TO_CENTER 1000.0

#define COLOR_GRASS_R 0
#define COLOR_GRASS_G 0
#define COLOR_GRASS_B 200

#define TREE_WIDTH 100.0
#define TREE_HEIGHT 120.0
#define TREE_DEFAULT_DISTANCE 200.0
#define TREE_MAX_OFFSET 70.0
#define TREE_GRID_COLUMNS 8
#define TREE_GRID_ROWS 12

#endif //BLUE_MAX_DEFS_H
