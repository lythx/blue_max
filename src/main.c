#include "SDL.h"
#include "config.h"
#include "init_SDL.h"
#include "geometry.h"
#include "draw.h"
#include "Player.h"

int handle_input(SDL_Event* event, Player* player);

int main(int argc, char* argv[]) {
  if (DEBUG_MODE == 1){
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
  }

  App app;
  init_SDL(&app);

  SDL_Event event;
  Vector pos = vector_create(300, 300, 0);
  Player player = player_create(&pos);
  int running = 1;
  while (running) {
    running = handle_input(&event, &player);

    player_move(&player);

    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);
    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
    draw_hitboxes(&app, player.hitboxes, 2);
    SDL_RenderPresent(app.renderer);
  }

  quit_SDL(&app);
  return 0;
}

int handle_input(SDL_Event* event, Player* player) {
  while (SDL_PollEvent(event)) {
    switch (event->type)
    {
      case SDL_QUIT:
        return 0;
      case SDL_KEYDOWN:
        if (event->key.repeat == 0) {
          player_handle_keydown(player, event->key.keysym.scancode);
        }
        break;
      case SDL_KEYUP:
        if (event->key.repeat == 0) {
          player_handle_keyup(player, event->key.keysym.scancode);
        }
    }
  }
  return 1;
}
