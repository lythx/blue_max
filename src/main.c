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
Projectile up_projectiles[MAX_PROJECTILES];
uint8_t up_projectile_count = 0;
Projectile down_projectiles[MAX_PROJECTILES];
uint8_t down_projectile_count = 0;

int handle_input(const App* app, SDL_Event* event, Player* player);
void move_planes_and_projectiles(Player* player);
int handle_collisions(Player* player);

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

    move_planes_and_projectiles(&player);
    if (handle_collisions(&player)) {
      break;
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

void move_planes_and_projectiles(Player* player) {
  player_move(player);
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
  return 0;
}
