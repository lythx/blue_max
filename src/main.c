#include "SDL.h"
#include "config.h"
#include "init_SDL.h"
#include "geometry.h"
#include "draw.h"
#include "Player.h"
#include "Plane.h"
#include "Projectile.h"

Plane planes[MAX_PLANES];
uint8_t plane_count = 0;
Projectile player_projectiles[MAX_PROJECTILES];
uint8_t player_projectile_count = 0;

int handle_input(const App* app, SDL_Event* event, Player* player);

int main(int argc, char* argv[]) {
  if (DEBUG_MODE == 1){
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
  }

  App app;
  init_SDL(&app);

  SDL_Event event;
  Vector pos = vector_create(300, 300, 0);
  Vector enemy_pos = vector_create(500, 500, 0);
  Vector enemy_pos2 = vector_create(400, 300, 100);
  Player player = player_create(&app, &pos);
  planes[0] = plane_create(&app, &enemy_pos);
  planes[1] = plane_create(&app, &enemy_pos2);
  plane_count = 2;
  int running = 1;

  while (running) {
    running = handle_input(&app, &event, &player);

    player_move(&player);
    for (uint8_t i = 0; i < plane_count; i++) {
      plane_move(&planes[i]);
    }
    for (uint8_t i = 0; i < player_projectile_count; i++) {
      projectile_move(&player_projectiles[i], PROJECTILE_PLAYER);
    }

    SDL_SetRenderDrawColor(app.renderer, 0,  80, 0, 255);
    SDL_RenderClear(app.renderer);
    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
    draw_texture(&app, player.texture, &player.pos);
    draw_hitboxes(&app, player.hitboxes, 2);
    for (uint8_t i = 0; i < plane_count; i++) {
      draw_texture(&app, planes[i].texture, &planes[i].pos);
      draw_hitboxes(&app, planes[i].hitboxes, 2);
    }
    for (uint8_t i = 0; i < player_projectile_count; i++) {
      draw_texture(&app, player_projectiles[i].texture, &player_projectiles[i].pos);
      draw_box(&app, &player_projectiles[i].hitbox);
    }
    for (uint8_t i = 0; i < plane_count; i++) {
      if (box_intersects(&player.hitboxes[0], &planes[i].hitboxes[0]) ||
          box_intersects(&player.hitboxes[1], &planes[i].hitboxes[0]) ||
          box_intersects(&player.hitboxes[0], &planes[i].hitboxes[1]) ||
          box_intersects(&player.hitboxes[1], &planes[i].hitboxes[1])) {
        plane_destroy(&planes[i]);
        plane_count -= 1;
      }
    }

    SDL_RenderPresent(app.renderer);
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
