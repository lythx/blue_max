#include "Building.h"
#include "init_SDL.h"

Building building_create(const App* app, double x, double y, double length, double width, double height) {
  SDL_Texture* texture = load_texture(app, "../assets/player.png");
  return (Building) {x, y, length, width, height, texture};
}

Box building_hitbox(const Building* building) {
  Vector center = vector_create(building->x, building->y, building->height / 2);
  return box_create_around_center(&center, building->length, building->width, building->height);
}
