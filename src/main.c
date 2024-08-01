#include "SDL.h"
#include "SDL_image.h"
#include "config.h"

int main(int argc, char* argv[]) {
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
  #if DEBUG_MODE == 1
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
  #endif

  SDL_Quit();
  IMG_Quit();
  return 0;
}