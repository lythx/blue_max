#include "Building.h"
#include "../textures.h"

Building building_create(double x, double y, double length, double width, double height) {
  SDL_Texture* texture = get_texture(TEXTURE_BUILDING);
  return (Building) {x, y, length, width, height, texture};
}

Box building_hitbox(const Building* building) {
  Vector center = vector_create(building->x, building->y, building->height / 2);
  return box_create_around_center(&center, building->length, building->width, building->height);
}

SDL_Texture* building_get_texture(const Building* building, int* width, int* height) {
  *width = BUILDING_TEXTURE_WIDTH;
  *height = BUILDING_TEXTURE_HEIGHT;
  return building->texture;
}

