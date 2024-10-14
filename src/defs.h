#ifndef BLUE_MAX_DEFS_H
#define BLUE_MAX_DEFS_H

#include "SDL.h"
#include "geometry/Vector.h"

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    int scene_width;
    int scene_height;
    int window_width;
    int window_height;
    int left_padding;
    int right_padding;
    int top_padding;
    int bottom_padding;
    Vector center;
    int display_hitboxes;
    double scene_scale;
} App;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;

#define DEBUG_LOG 1

#define ROTATION_SIN 0.72
#define ROTATION_COS 0.694
#define HEIGHT_Y_OFFSET (-0.7)

#define PLANE_BODY_LENGTH 60.0
#define PLANE_BODY_WIDTH 20.0
#define PLANE_BODY_HEIGHT 30.0
#define PLANE_WINGS_LENGTH 10.0
#define PLANE_WINGS_HEIGHT 20.0
#define PLANE_WINGS_WIDTH 80.0
#define PLANE_UP_SPEED 6.0
#define PLANE_DOWN_SPEED 3.0
#define PLANE_RELOAD_TIME_MS 1300
#define PLANE_SHOOT_CHANCE 0.2
#define PLANE_TEXTURE_CHANGE_INTERVAL_MS 80
#define PLANE_TEXTURE_WIDTH 85
#define PLANE_TEXTURE_HEIGHT (PLANE_TEXTURE_WIDTH * (57.0 / 94.0))

#define MAX_PLANES 4
#define MAX_PROJECTILES 128
#define MAX_BUILDINGS 4
#define MAX_TREES 256

#define PLAYER_FORWARD_SPEED 3.0
#define PLAYER_HORIZONTAL_SPEED 4.5
#define PLAYER_VERTICAL_SPEED 4.5
#define PLAYER_HORIZONTAL_BOUND 300.0
#define PLAYER_UP_BOUND 450.0
#define PLAYER_TEXTURE_CHANGE_INTERVAL_MS 80
#define PLAYER_TEXTURE_FORWARD_WIDTH 85
#define PLAYER_TEXTURE_FORWARD_HEIGHT (PLAYER_TEXTURE_FORWARD_WIDTH * (57.0 / 94.0))
#define PLAYER_TEXTURE_RIGHT_WIDTH (PLAYER_TEXTURE_FORWARD_WIDTH * (82.0 / 94.0))
#define PLAYER_TEXTURE_RIGHT_HEIGHT (PLAYER_TEXTURE_RIGHT_WIDTH * (56.0 / 82.0))
#define PLAYER_TEXTURE_LEFT_WIDTH (PLAYER_TEXTURE_FORWARD_WIDTH * (93.0 / 94.0))
#define PLAYER_TEXTURE_LEFT_HEIGHT (PLAYER_TEXTURE_FORWARD_WIDTH * (44.0 / 93.0))
#define PLAYER_RELOAD_TIME_MS 300

#define PROJECTILE_SPEED_PLAYER 15.5
#define PROJECTILE_SPEED_UP 10.0
#define PROJECTILE_SPEED_DOWN 7.0
#define PROJECTILE_LENGTH 30.0
#define PROJECTILE_DIAMETER 5.0
#define PROJECTILE_TEXTURE_WIDTH 10
#define PROJECTILE_TEXTURE_HEIGHT (PROJECTILE_TEXTURE_WIDTH * (410.0 / 848.0))

#define BUILDING_WIDTH 170.0
#define BUILDING_LENGTH 50.0
#define BUILDING_HEIGHT 90.0
#define BUILDING_TEXTURE_WIDTH 200.0
#define BUILDING_TEXTURE_HEIGHT (BUILDING_TEXTURE_WIDTH * (410.0 / 848.0))

#define SPAWN_DISTANCE_TO_CENTER 600.0
#define SPAWN_PLANE_CHANCE 0.005
#define SPAWN_PLANE_MIN_HEIGHT 100.0
#define SPAWN_BUILDING_CHANCE 0.002
#define SPAWN_BUILDING_MIN_DISTANCE 400.0

#define UNLOAD_DISTANCE_TO_CENTER 1000.0

#define COLOR_GRASS_R 37
#define COLOR_GRASS_G 114
#define COLOR_GRASS_B 0

#define TREE_WIDTH 30.0
#define TREE_HEIGHT 120.0
#define TREE_TEXTURE_WIDTH 80.0
#define TREE_TEXTURE_HEIGHT 50.0
#define TREE_DEFAULT_DISTANCE 200.0
#define TREE_MAX_OFFSET 70.0
#define TREE_GRID_COLUMNS 8
#define TREE_GRID_ROWS 12
#define TREE_COLOR_R 37
#define TREE_COLOR_G 66
#define TREE_COLOR_B 0
#define TREE_ROOT_COLOR_R 0
#define TREE_ROOT_COLOR_G 0
#define TREE_ROOT_COLOR_B 0
#define TREE_BLACK_SQUARE_PROBABILITY 0.1
#define TREE_SPAWN_AREA_WIDTH 60.0

#define CAMERA_CENTER_OFFSET_X (-500)
#define CAMERA_CENTER_OFFSET_Y 0
#define CAMERA_CENTER_OFFSET_Z 800

#define DEFAULT_WINDOW_WIDTH 800
#define DISPLAY_WIDTH_TO_HEIGHT_RATIO 1.5

#define FLEX_TOP_PADDING 0.05
#define FLEX_SCENE 0.75
#define FLEX_BOTTOM_UI 0.2

#define UI_FONT_SIZE 30
#define UI_TOP_PADDING 15
#define UI_LEFT_PADDING 100
#define UI_TEXT_LINE_HEIGHT 28
#define UI_COLOR_1_R 52
#define UI_COLOR_1_G 162
#define UI_COLOR_1_B 182
#define UI_COLOR_2_R 159
#define UI_COLOR_2_G 255
#define UI_COLOR_2_B 255

#define RIVER_SEGMENT_COUNT 30
#define RIVER_WIDTH 300.0
#define RIVER_BORDER_RECT_WIDTH 5
#define RIVER_MIN_SEGMENT_LENGTH 70
#define RIVER_MAX_SEGMENT_LENGTH 120
#define RIVER_MAX_SEGMENT_WIDTH 30
#define RIVER_START_Y_OFFSET (-200)
#define RIVER_COLOR_R 0
#define RIVER_COLOR_G 101
#define RIVER_COLOR_B 120
#define RIVER_BORDER_COLOR_R 37
#define RIVER_BORDER_COLOR_G 66
#define RIVER_BORDER_COLOR_B 0
#define RIVER_LEFT_BORDER_WIDTH 30
#define RIVER_LEFT_BOUND (-600)
#define RIVER_RIGHT_BOUND 300
#define RIVER_MAX_Y_RIGHT_AIRPORT (-500)
#define RIVER_MIN_Y_LEFT_AIRPORT 200
#define RIVER_AIRPORT_AVOID_DISTANCE 3000

#define AIRPORT_LEFT_Y (-300)
#define AIRPORT_RIGHT_Y 100
#define AIRPORT_MIN_DISTANCE 4000
#define AIRPORT_MAX_DISTANCE 5000
#define AIRPORT_WIDTH 290
#define AIRPORT_LENGTH 1700
#define AIRPORT_START_X 1000
#define AIRPORT_TEXTURE_WIDTH 1500
#define AIRPORT_TEXTURE_HEIGHT (AIRPORT_TEXTURE_WIDTH * 0.786)

#endif //BLUE_MAX_DEFS_H
