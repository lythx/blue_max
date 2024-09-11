#include "ui.h"
#include "draw.h"
#include "stdio.h"



void ui_render(const App* app, const Player* player) {
  int x = app->left_padding + UI_LEFT_PADDING;
  int y = app->window_height - app->bottom_padding + UI_TOP_PADDING;
  Color c1 = {255, 0, 0};
  Color c2 = {0, 255, 0};
  Color* colors[4] = {&c1, &c2, &c1, &c2};
  char fuel[10], bombs[10], speed[10], alt[10], score[10];
  sprintf(fuel, "%d  ", 300);
  sprintf(bombs, "%d", 10);
  sprintf(speed, "%d  ", 300);
  sprintf(alt, "%d  ", (int) player->pos.z);
  sprintf(score, "%d", 0);
  char* line1[4] = {"F : ", fuel, "B : ", bombs};
  draw_text_line(app, x, y, 4, line1, colors);
  y += UI_TEXT_LINE_HEIGHT;
  char* line2[4] = {"SPD : ", speed, "ALT : ", alt};
  draw_text_line(app, x, y, 4, line2, colors);
  y += UI_TEXT_LINE_HEIGHT;
  char* line3[2] = {"SCORE : ", score};
  draw_text_line(app, x, y, 2, line3, colors);
}


