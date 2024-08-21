#include "SDL.h"
#include "config.h"
#include "init_SDL.h"
#include "geometry.h"
#include "entities.h"
#include "stdlib.h"
#include "time.h"
#include "generate.h"
#include "update.h"
#include "render.h"

Plane planes[MAX_PLANES];
uint8_t plane_count = 0;
Projectile player_projectiles[MAX_PROJECTILES];
uint8_t player_projectile_count = 0;
Projectile plane_projectiles[MAX_PROJECTILES];
uint8_t plane_projectile_count = 0;
Building buildings[MAX_BUILDINGS];
uint8_t building_count = 0;

int handle_input(const App* app, SDL_Event* event, Player* player);

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

    generate_plane_shots(&app, planes, &plane_count, plane_projectiles, &plane_projectile_count);
    generate_plane(&app, &center, planes, &plane_count);
    generate_building(&app, &center, buildings, &building_count);

    if (update_all(&center, &player,
                   buildings, &building_count,
                   planes, &plane_count,
                   player_projectiles, &player_projectile_count,
                   plane_projectiles, &plane_projectile_count)) {
      break;
    }

    render_all(&app, &center, &player,
               buildings, building_count,
               planes, plane_count,
               player_projectiles, player_projectile_count,
               plane_projectiles, plane_projectile_count);

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