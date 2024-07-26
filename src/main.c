#include "SDL.h"
#include "SDL_image.h"

int main(int argc, char* argv[]) {
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
  SDL_Quit();
  IMG_Quit();
  return 0;
}