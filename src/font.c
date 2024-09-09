#include "font.h"

#include "defs.h"

TTF_Font* font;

void init_font() {
  font = TTF_OpenFont("../assets/7px3bus.ttf", UI_FONT_SIZE);
}

TTF_Font* get_font() {
  return font;
}
