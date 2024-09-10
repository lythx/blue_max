#include "ui.h"
#include "draw.h"



void ui_render(const App* app) {
  SDL_Rect rect;
  int x = app->left_padding + UI_LEFT_PADDING;
  int y = app->window_height - app->bottom_padding + UI_TOP_PADDING;
  char* s1 = "F:";
  char* s2 = "300";
  char* s3 = "B:";
  char* s4 = "10";
  char* texts[4] = {s1, s2, s3, s4};
  Color c1 = {255, 0, 0};
  Color c2 = {0, 255, 0};
  Color* colors[4] = {&c1, &c2, &c1, &c2};
  draw_text_line(app, x, y, 4, texts, colors);
}


