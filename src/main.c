#include "SDL.h"
#include "init_SDL.h"
#include "entities.h"
#include "stdlib.h"
#include "time.h"
#include "generate.h"
#include "update.h"
#include "render.h"
#include "input.h"
#include "textures.h"
#include "scene.h"
#include "font.h"
#include "river.h"
#include "airport.h"

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

  if (DEBUG_LOG == 1){
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
  }

  App app;
  app.display_hitboxes = 0;

  init_SDL(&app);
  init_scene(&app);
  init_textures(&app);
  init_font();
  app.center = vector_create(app.right_padding + (double) app.scene_width / 2,
                              app.top_padding + (double) app.scene_height / 2, 0);

  SDL_Event event;
  Vector player_init_pos = vector_create(100, 300, 200);
  Player player = player_create(&player_init_pos);
  river_initialize(&app.center);
  airport_initialize();
  int running = 1;

  while (running) {
    running = handle_input(&app, &event, &player, player_projectiles, &player_projectile_count);

    generate_plane_shots(planes, &plane_count, plane_projectiles, &plane_projectile_count);
    generate_plane(&app, planes, &plane_count);
    generate_building(&app, buildings, &building_count);
    generate_trees(&app, trees, &tree_count, buildings, building_count);

    if (update_all(&app, &player,
                   buildings, &building_count,
                   planes, &plane_count,
                   player_projectiles, &player_projectile_count,
                   plane_projectiles, &plane_projectile_count,
                   trees, &tree_count)) {
      break;
    }

    render_all(&app, &player,
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
