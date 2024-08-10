#include "init_SDL.h"
#include "config.h"
#include "SDL_image.h"

void init_SDL(App* app) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Error while initializing SDL: %s", SDL_GetError());
    exit(1);
  }

  app->window = SDL_CreateWindow("Blue Max", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                 WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (!app->window) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Error while creating window: %s\n", SDL_GetError());
    SDL_Quit();
    exit(1);
  }

  app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
  if (!app->renderer) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Error while creating renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(app->window);
    SDL_Quit();
    exit(1);
  }

  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

void quit_SDL(App* app) {
  IMG_Quit();
  SDL_DestroyRenderer(app->renderer);
  SDL_DestroyWindow(app->window);
  SDL_Quit();
}

SDL_Texture* load_texture(const App* app, const char* filename) {
  SDL_Texture *texture;
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Loading %s", filename);
  texture = IMG_LoadTexture(app->renderer, filename);
  return texture;
}
