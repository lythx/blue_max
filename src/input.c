#include "input.h"

int handle_input(App* app, SDL_Event* event, Player* player,
                 Projectile* player_projectiles, uint8_t* player_projectile_count) {
  while (SDL_PollEvent(event)) {
    switch (event->type)
    {
      case SDL_QUIT:
        return 0;
      case SDL_KEYDOWN:
        if (event->key.keysym.scancode == SDL_SCANCODE_SPACE) {
          if (player_can_shoot(player))
          {
            player_projectiles[*player_projectile_count] = player_shoot(player);
            (*player_projectile_count)++;
          }
          break;
        } else if (event->key.keysym.scancode == SDL_SCANCODE_B) {
          app->display_hitboxes = app->display_hitboxes == 0 ? 1 : 0;
          break;
        } else if (event->key.repeat == 0) {
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
