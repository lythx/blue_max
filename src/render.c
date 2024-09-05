#include "render.h"
#include "config.h"

Vector get_camera_pos(const Vector* center) {
  Vector camera_pos = vector_copy(center);
  camera_pos.x += CAMERA_CENTER_OFFSET_X;
  camera_pos.y += CAMERA_CENTER_OFFSET_Y;
  camera_pos.z += CAMERA_CENTER_OFFSET_Z;
  return camera_pos;
}

void render_hitboxes(const App* app, const Vector* center, const Player* player,
                     const Building* buildings, uint8_t building_count,
                     const Plane* planes, uint8_t plane_count,
                     const Projectile* player_projectiles, uint8_t player_projectile_count,
                     const Projectile* plane_projectiles, uint8_t plane_projectile_count,
                     const Tree* trees, uint8_t tree_count) {
  SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);
  draw_hitboxes(app, center, player->hitboxes, 2);
  for (uint8_t i = 0; i < plane_count; i++) {
    draw_hitboxes(app, center, planes[i].hitboxes, 2);
  }
  for (uint8_t i = 0; i < player_projectile_count; i++) {
    draw_box(app, center, &player_projectiles[i].hitbox);
  }
  for (uint8_t i = 0; i < plane_projectile_count; i++) {
    draw_box(app, center, &plane_projectiles[i].hitbox);
  }
  for (uint8_t i = 0; i < building_count; i++) {
    Box building_hb = building_hitbox(&buildings[i]);
    draw_box(app, center, &building_hb);
  }
  for (uint8_t i = 0; i < tree_count; i++) {
    Box tree_hb = tree_hitbox(&trees[i]);
    draw_box(app, center, &tree_hb);
  }
  draw_point(app, center, center);
}

void render_textures(const App* app, const Vector* center, const Player* player,
                     const Building* buildings, uint8_t building_count,
                     const Plane* planes, uint8_t plane_count,
                     const Projectile* player_projectiles, uint8_t player_projectile_count,
                     const Projectile* plane_projectiles, uint8_t plane_projectile_count,
                     const Tree* trees, uint8_t tree_count) {
  int w, h;
  SDL_Texture* texture;
  for (uint8_t i = 0; i < building_count; i++) {
    Vector building_pos = vector_create(buildings[i].x, buildings[i].y, (double) BUILDING_HEIGHT / 2);
    texture = building_get_texture(&buildings[i], &w, &h);
    draw_texture(app, center, texture, &building_pos, w, h);
  }
  for (uint8_t i = 0; i < tree_count; i++) {
    draw_tree(app, center, &trees[i]);
  }
  for (uint8_t i = 0; i < player_projectile_count; i++) {
    draw_texture(app, center, player_projectiles[i].texture, &player_projectiles[i].pos, PROJECTILE_TEXTURE_WIDTH, PROJECTILE_TEXTURE_HEIGHT);
  }
  for (uint8_t i = 0; i < plane_projectile_count; i++) {
    draw_texture(app, center, plane_projectiles[i].texture, &plane_projectiles[i].pos, PROJECTILE_TEXTURE_WIDTH, PROJECTILE_TEXTURE_HEIGHT);
  }
  for (uint8_t i = 0; i < plane_count; i++) {
    texture = plane_get_texture(&planes[i]);
    draw_texture(app, center, texture, &planes[i].pos, PLANE_TEXTURE_WIDTH, PLANE_TEXTURE_HEIGHT);
  }
  texture = player_get_texture(player, &w, &h);
  draw_texture(app, center, texture, &player->pos, w, h);
}

void render_all(const App* app, const Vector* center, const Player* player,
                const Building* buildings, uint8_t building_count,
                const Plane* planes, uint8_t plane_count,
                const Projectile* player_projectiles, uint8_t player_projectile_count,
                const Projectile* plane_projectiles, uint8_t plane_projectile_count,
                const Tree* trees, uint8_t tree_count) {
  SDL_SetRenderDrawColor(app->renderer, COLOR_GRASS_R,  COLOR_GRASS_G, COLOR_GRASS_B, 255);
  SDL_RenderClear(app->renderer);
  render_textures(app, center, player, buildings, building_count, planes, plane_count, player_projectiles,
                  player_projectile_count, plane_projectiles, plane_projectile_count, trees, tree_count);
  if (DEBUG_MODE == 1) {
    render_hitboxes(app, center, player, buildings, building_count, planes, plane_count, player_projectiles,
                    player_projectile_count, plane_projectiles, plane_projectile_count, trees, tree_count);
  }
  SDL_RenderPresent(app->renderer);
}
