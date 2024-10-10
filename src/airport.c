#include "airport.h"
#include "utils.h"
#include "defs.h"
#include "textures.h"

Airport airport;

void airport_initialize() {
  airport = (Airport) {AIRPORT_START_X, AIRPORT_RIGHT};
}

Vector airport_get_pos(const App* app) {
  Vector v;
  Vector mid = vector_create(AIRPORT_LENGTH * 0.5, AIRPORT_WIDTH * 0.5, 0);
  vector_rotate(&mid);
  v.x = airport.x + mid.x;
  double tan = ROTATION_SIN / ROTATION_COS;
  double center_y = (airport.x - app->center.x) * tan + app->center.y;
  if (airport.side == AIRPORT_LEFT) {
    v.y = center_y + AIRPORT_LEFT_Y;
  } else {
    v.y = center_y + AIRPORT_RIGHT_Y;
  }
  v.y += mid.y;
  v.z = 0;
  return v;
}

Box airport_get_hitbox(const App* app) {
  Vector pos = airport_get_pos(app);
  return box_create_around_center(&pos, AIRPORT_LENGTH, AIRPORT_WIDTH, 1);
}

void airport_update(const App* app) {
  if (app->center.x - airport.x - AIRPORT_LENGTH > UNLOAD_DISTANCE_TO_CENTER) {
    double dist = rand_min_max(AIRPORT_MIN_DISTANCE, AIRPORT_MAX_DISTANCE);
    double x = airport.x + dist;
    AIRPORT_SIDE side = rand_0_1() > 0.5 ? AIRPORT_LEFT : AIRPORT_RIGHT;
    airport = (Airport) {x, side};
  }
}

SDL_Texture* airport_get_texture(int* width, int* height) {
  *width = AIRPORT_TEXTURE_WIDTH;
  *height = AIRPORT_TEXTURE_HEIGHT;
  return get_texture(TEXTURE_AIRPORT);
}
