#ifndef BLUE_MAX_INIT_SDL_H
#define BLUE_MAX_INIT_SDL_H

#include "defs.h"

void init_SDL(App* app);

void quit_SDL(App* app);

SDL_Texture* load_texture(const App* app, const char* filename);

#endif //BLUE_MAX_INIT_SDL_H
