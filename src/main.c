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
#include "input.h"
#include "textures.h"

Plane planes[MAX_PLANES];
uint8_t plane_count = 0;
Projectile player_projectiles[MAX_PROJECTILES];
uint8_t player_projectile_count = 0;
Projectile plane_projectiles[MAX_PROJECTILES];
uint8_t plane_projectile_count = 0;
Building buildings[MAX_BUILDINGS];
uint8_t building_count = 0;
Tree trees[MAX_TREES];
uint8_t tree_count = 0;

int main(int argc, char* argv[]) {
  srand(time(NULL));
  if (DEBUG_MODE == 1){
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
  }
  App app;
  init_SDL(&app);
  init_textures(&app);
  SDL_Event event;
  Vector center = vector_create((double) WINDOW_HEIGHT / 2, (double) WINDOW_WIDTH / 2, 0);
  Vector player_init_pos = vector_create(100, 300, 200);
  Player player = player_create(&player_init_pos);
  int running = 1;

  while (running) {
    running = handle_input(&event, &player, player_projectiles, &player_projectile_count);

    generate_plane_shots(planes, &plane_count, plane_projectiles, &plane_projectile_count);
    generate_plane(&center, planes, &plane_count);
    generate_building(&center, buildings, &building_count);
    generate_trees(&center, trees, &tree_count, buildings, building_count);

    if (update_all(&center, &player,
                   buildings, &building_count,
                   planes, &plane_count,
                   player_projectiles, &player_projectile_count,
                   plane_projectiles, &plane_projectile_count,
                   trees, &tree_count)) {
      break;
    }

    render_all(&app, &center, &player,
               buildings, building_count,
               planes, plane_count,
               player_projectiles, player_projectile_count,
               plane_projectiles, plane_projectile_count,
               trees, tree_count);

    SDL_Delay(10);
  }

  quit_SDL(&app);
  return 0;
}
