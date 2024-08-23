#include "render.h"
#include "config.h"

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
  draw_texture(app, center, player->texture, &player->pos);
  for (uint8_t i = 0; i < plane_count; i++) {
    draw_texture(app, center, planes[i].texture, &planes[i].pos);
  }
  for (uint8_t i = 0; i < player_projectile_count; i++) {
    draw_texture(app, center, player_projectiles[i].texture, &player_projectiles[i].pos);
  }
  for (uint8_t i = 0; i < plane_projectile_count; i++) {
    draw_texture(app, center, plane_projectiles[i].texture, &plane_projectiles[i].pos);
  }
  for (uint8_t i = 0; i < building_count; i++) {
    Vector building_pos = vector_create(buildings[i].x, buildings[i].y, 0);
    draw_texture(app, center, buildings[i].texture, &building_pos);
  }
  for (uint8_t i = 0; i < tree_count; i++) {
    Vector tree_pos = vector_create(trees[i].x, trees[i].y, 0);
    draw_texture(app, center, trees[i].texture, &tree_pos);
  }
}

void render_all(const App* app, const Vector* center, const Player* player,
                const Building* buildings, uint8_t building_count,
                const Plane* planes, uint8_t plane_count,
                const Projectile* player_projectiles, uint8_t player_projectile_count,
                const Projectile* plane_projectiles, uint8_t plane_projectile_count,
                const Tree* trees, uint8_t tree_count) {
  SDL_SetRenderDrawColor(app->renderer, COLOR_GRASS_R,  COLOR_GRASS_G, COLOR_GRASS_B, 255);
  SDL_RenderClear(app->renderer);
  if (DEBUG_MODE == 1) {
    render_hitboxes(app, center, player, buildings, building_count, planes, plane_count, player_projectiles,
                    player_projectile_count, plane_projectiles, plane_projectile_count, trees, tree_count);
  }
  render_textures(app, center, player, buildings, building_count, planes, plane_count, player_projectiles,
                  player_projectile_count, plane_projectiles, plane_projectile_count, trees, tree_count);
  SDL_RenderPresent(app->renderer);
}
