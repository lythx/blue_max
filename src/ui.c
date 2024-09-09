#include "ui.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "font.h"
#include "draw.h"

void ui_render(const App* app) {
  TTF_Font* font = get_font();
  SDL_Surface* surface = TTF_RenderUTF8_Solid(font, "test", (SDL_Color){255, 255, 255, 255});
  SDL_Texture* texture = SDL_CreateTextureFromSurface(app->renderer, surface);
  int w, h;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  Vector pos = vector_create(900, 900, 0);
  draw_texture(app, &app->center, texture, &pos, w, h);
}
