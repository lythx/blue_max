#include "render.h"
#include "config.h"
#include "ui.h"

typedef enum {
    TEXTURE = 1,
    TREE = 2
} DRAW_TYPE;

typedef struct {
    DRAW_TYPE type;
    double dist_to_camera;
    SDL_Texture* texture;
    Vector pos;
    int width;
    int height;
    const Tree* tree;
} Entity;

Entity all_entities[MAX_TREES + MAX_BUILDINGS + MAX_PLANES + MAX_PROJECTILES + 1];
int entity_count = 0;

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

int compare_entities(const void* a, const void* b) {
  Entity* e1 = (Entity*) a;
  Entity* e2 = (Entity*) b;
  return e1->dist_to_camera < e2->dist_to_camera ? 1 : -1;
}

void sort_entities() {
  qsort(all_entities, entity_count, sizeof(Entity), compare_entities);
}

void draw_entities(const App* app, const Vector* center) {
  for (int i = 0; i < entity_count; i++) {
    switch (all_entities[i].type) {
      case TEXTURE:
        draw_texture(app, center, all_entities[i].texture, &all_entities[i].pos,
                     all_entities[i].width, all_entities[i].height);
        break;
      case TREE:
        draw_tree(app, center, all_entities[i].tree);
        break;
    }
  }
}

void render_textures(const App* app, const Vector* center, const Player* player,
                     const Building* buildings, uint8_t building_count,
                     const Plane* planes, uint8_t plane_count,
                     const Projectile* player_projectiles, uint8_t player_projectile_count,
                     const Projectile* plane_projectiles, uint8_t plane_projectile_count,
                     const Tree* trees, uint8_t tree_count) {
  Vector camera_pos = get_camera_pos(center);
  int w, h;
  SDL_Texture* texture = player_get_texture(player, &w, &h);
  double dist = vector_point_distance(&camera_pos, &player->pos);
  Vector entity_pos;
  entity_count = 0;
  all_entities[entity_count++] = (Entity) {TEXTURE, dist, texture, player->pos,
                                    PLANE_TEXTURE_WIDTH, PLANE_TEXTURE_HEIGHT};
  for (uint8_t i = 0; i < building_count; i++) {
    entity_pos = vector_create(buildings[i].x, buildings[i].y, buildings[i].height / 2);
    texture = building_get_texture(&buildings[i], &w, &h);
    dist = vector_point_distance(&camera_pos, &entity_pos);
    all_entities[entity_count++] = (Entity) {TEXTURE, dist, texture, vector_copy(&entity_pos), w, h};
  }
  for (uint8_t i = 0; i < tree_count; i++) {
    entity_pos = vector_create(trees[i].x, trees[i].y, (double) TREE_HEIGHT / 2);
    dist = vector_point_distance(&camera_pos, &entity_pos);
    all_entities[entity_count++] = (Entity) {TREE, dist, texture,
                                             0, 0, 0, 0, 0, &trees[i]};
  }
  for (uint8_t i = 0; i < player_projectile_count; i++) {
    dist = vector_point_distance(&camera_pos, &player_projectiles[i].pos);
    all_entities[entity_count++] = (Entity) {TEXTURE, dist, player_projectiles[i].texture,
                                      player_projectiles[i].pos, PROJECTILE_TEXTURE_WIDTH, PROJECTILE_TEXTURE_HEIGHT};
  }
  for (uint8_t i = 0; i < plane_projectile_count; i++) {
    dist = vector_point_distance(&camera_pos, &player_projectiles[i].pos);
    all_entities[entity_count++] = (Entity) {TEXTURE, dist, plane_projectiles[i].texture,
                                      plane_projectiles[i].pos, PROJECTILE_TEXTURE_WIDTH, PROJECTILE_TEXTURE_HEIGHT};
  }
  for (uint8_t i = 0; i < plane_count; i++) {
    dist = vector_point_distance(&camera_pos, &planes[i].pos);
    texture = plane_get_texture(&planes[i]);
    all_entities[entity_count++] = (Entity) {TEXTURE, dist, texture, planes[i].pos,
                                      PLANE_TEXTURE_WIDTH, PLANE_TEXTURE_HEIGHT};
  }
  sort_entities();
  draw_entities(app, center);
}

void render_padding(const App* app) {
  SDL_SetRenderDrawColor(app->renderer, 0,  0, 0, 255);
  SDL_RenderFillRect(app->renderer, &(SDL_Rect) {0, 0, app->left_padding, app->window_height});
  SDL_RenderFillRect(app->renderer, &(SDL_Rect) {0, 0, app->window_width, app->top_padding});
  SDL_RenderFillRect(app->renderer, &(SDL_Rect) {app->window_width - app->right_padding, 0,
                                                 app->right_padding, app->window_height});
  SDL_RenderFillRect(app->renderer, &(SDL_Rect) {0, app->window_height - app->bottom_padding,
                                                 app->window_width, app->bottom_padding});
}

void render_all(const App* app, const Player* player,
                const Building* buildings, uint8_t building_count,
                const Plane* planes, uint8_t plane_count,
                const Projectile* player_projectiles, uint8_t player_projectile_count,
                const Projectile* plane_projectiles, uint8_t plane_projectile_count,
                const Tree* trees, uint8_t tree_count) {
  SDL_SetRenderDrawColor(app->renderer, COLOR_GRASS_R, COLOR_GRASS_G, COLOR_GRASS_B, 255);
  SDL_RenderClear(app->renderer);
  render_textures(app, &app->center, player, buildings, building_count, planes, plane_count, player_projectiles,
                  player_projectile_count, plane_projectiles, plane_projectile_count, trees, tree_count);
  if (app->display_hitboxes == 1) {
    render_hitboxes(app, &app->center, player, buildings, building_count, planes, plane_count, player_projectiles,
                    player_projectile_count, plane_projectiles, plane_projectile_count, trees, tree_count);
  }
  render_padding(app);
  ui_render(app, player);
  SDL_RenderPresent(app->renderer);
}
