#include "SDL.h"
#include "config.h"
#include "init_SDL.h"
#include "geometry.h"
#include "draw.h"
#include "Player.h"
#include "Plane.h"
#include "Projectile.h"
#include "Building.h"
#include "stdlib.h"
#include "time.h"
#include "generate.h"

Plane planes[MAX_PLANES];
uint8_t plane_count = 0;
Projectile player_projectiles[MAX_PROJECTILES];
uint8_t player_projectile_count = 0;
Projectile up_projectiles[MAX_PROJECTILES];
uint8_t up_projectile_count = 0;
Projectile down_projectiles[MAX_PROJECTILES];
uint8_t down_projectile_count = 0;
Building buildings[MAX_BUILDINGS];
uint8_t building_count = 0;

int handle_input(const App* app, SDL_Event* event, Player* player);
void move_center_and_entities(Player* player, Vector* center);
int handle_collisions(Player* player);

int main(int argc, char* argv[]) {
  srand(time(NULL));
  if (DEBUG_MODE == 1){
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
  }

  App app;
  init_SDL(&app);
  Vector center = vector_create((double) WINDOW_HEIGHT / 2, (double) WINDOW_WIDTH / 2, 0);
  SDL_Event event;
  Vector pos = vector_create(300, 300, 0);
  Vector enemy_pos = vector_create(500, 500, 100);
  Vector enemy_pos2 = vector_create(400, 300, 100);
  buildings[0] = building_create(&app, 300, 200, 100, 100, 100);
  building_count = 1;
  Player player = player_create(&app, &pos);
  planes[0] = plane_create(&app, &enemy_pos, PLANE_DOWN);
  planes[1] = plane_create(&app, &enemy_pos2, PLANE_UP);
  plane_count = 2;
  int running = 1;

  while (running) {
    running = handle_input(&app, &event, &player);

    generate_plane(&app, &center, planes, &plane_count);
    generate_building(&app, &center, buildings, &building_count);

    move_center_and_entities(&player, &center);
    if (handle_collisions(&player)) {
      break;
    }

    SDL_SetRenderDrawColor(app.renderer, 0,  80, 0, 255);
    SDL_RenderClear(app.renderer);
    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
    draw_texture(&app, &center, player.texture, &player.pos);
    draw_hitboxes(&app, &center, player.hitboxes, 2);
    for (uint8_t i = 0; i < plane_count; i++) {
      draw_texture(&app, &center, planes[i].texture, &planes[i].pos);
      draw_hitboxes(&app, &center, planes[i].hitboxes, 2);
    }
    for (uint8_t i = 0; i < player_projectile_count; i++) {
      draw_texture(&app, &center, player_projectiles[i].texture, &player_projectiles[i].pos);
      draw_box(&app, &center, &player_projectiles[i].hitbox);
    }
    for (uint8_t i = 0; i < building_count; i++) {
      Vector building_pos = vector_create(buildings[i].x, buildings[i].y, 0);
      draw_texture(&app, &center, buildings[i].texture, &building_pos);
      Box building_hb = building_hitbox(&buildings[i]);
      draw_box(&app, &center, &building_hb);
    }
    draw_point(&app, &center, &center);

    SDL_RenderPresent(app.renderer);
    SDL_Delay(10);
  }

  quit_SDL(&app);
  return 0;
}

int handle_input(const App* app, SDL_Event* event, Player* player) {
  while (SDL_PollEvent(event)) {
    switch (event->type)
    {
      case SDL_QUIT:
        return 0;
      case SDL_KEYDOWN:
        if (event->key.keysym.scancode == SDL_SCANCODE_SPACE) {
          player_projectiles[player_projectile_count] = player_shoot(app, player);
          player_projectile_count++;
          break;
        }
        else if (event->key.repeat == 0) {
          player_handle_keydown(player, event->key.keysym.scancode);
        }
        break;
      case SDL_KEYUP:
        if (event->key.repeat == 0) {
          player_handle_keyup(player, event->key.keysym.scancode);
        }
        break;
    }
  }
  return 1;
}

void move_center_and_entities(Player* player, Vector* center) {
  player_move(player, center);
  for (uint8_t i = 0; i < plane_count; i++) {
    plane_move(&planes[i]);
  }
  for (uint8_t i = 0; i < player_projectile_count; i++) {
    projectile_move(&player_projectiles[i], PROJECTILE_PLAYER);
  }
  for (uint8_t i = 0; i < up_projectile_count; i++) {
    projectile_move(&up_projectiles[i], PROJECTILE_PLANE_UP);
  }
  for (uint8_t i = 0; i < down_projectile_count; i++) {
    projectile_move(&down_projectiles[i], PROJECTILE_PLANE_DOWN);
  }
}

int handle_collisions(Player* player) {
  for (uint8_t i = 0; i < plane_count; i++) {
    if (box_intersects_array(player->hitboxes, 2, planes[i].hitboxes, 2)) {
      plane_destroy(&planes[i]);
      return 1;
    }
  }
  for (uint8_t i = 0; i < player_projectile_count; i++) {
    for (uint8_t j = 0; j < plane_count; j++) {
      if (box_intersects_array(&player_projectiles[i].hitbox, 1, planes[j].hitboxes, 1)) {
        plane_destroy(&planes[j]);
        planes[j] = planes[plane_count - 1];
        plane_count--;
        j--;
      }
    }
  }
  for (uint8_t i = 0; i < up_projectile_count; i++) {
    if (box_intersects_array(&up_projectiles[i].hitbox, 1, player->hitboxes, 2)) {
      return 1;
    }
  }
  for (uint8_t i = 0; i < down_projectile_count; i++) {
    if (box_intersects_array(&down_projectiles[i].hitbox, 1, player->hitboxes, 2)) {
      return 1;
    }
  }
  for (uint8_t i = 0; i < building_count; i++) {
    Box building_hb = building_hitbox(&buildings[i]);
    if (box_intersects_array(&building_hb, 1, player->hitboxes, 2)) {
      return 1;
    }
  }
  return 0;
}
