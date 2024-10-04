#include "init_SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "defs.h"

void init_SDL(App* app) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Error while initializing SDL: %s", SDL_GetError());
    exit(1);
  }

  app->window = SDL_CreateWindow("Blue Max", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                 DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_WIDTH / DISPLAY_WIDTH_TO_HEIGHT_RATIO,
                                 SDL_WINDOW_SHOWN);
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

  if (TTF_Init() == -1) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Error while initializing SDL TTF: %s\n", SDL_GetError());
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
    exit(1);
  }
}

void quit_SDL(App* app) {
  TTF_Quit();
  IMG_Quit();
  SDL_DestroyRenderer(app->renderer);
  SDL_DestroyWindow(app->window);
  SDL_Quit();
}
