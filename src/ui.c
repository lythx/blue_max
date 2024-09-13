#include "ui.h"
#include "draw.h"
#include "stdio.h"



void ui_render(const App* app, const Player* player) {
  int x = app->left_padding + UI_LEFT_PADDING;
  int y = app->window_height - app->bottom_padding + UI_TOP_PADDING;
  Color c1 = {UI_COLOR_1_R, UI_COLOR_1_G, UI_COLOR_1_B};
  Color c2 = {UI_COLOR_2_R, UI_COLOR_2_G, UI_COLOR_2_B};
  Color* colors[4] = {&c1, &c2, &c1, &c2};
  char fuel[10], bombs[10], speed[10], alt[10], score[10];
  sprintf(fuel, "%03d  ", 300);
  sprintf(bombs, "%02d", 30);
  sprintf(speed, "%03d  ", 300);
  sprintf(alt, "%03d  ", (int) player->pos.z);
  sprintf(score, "%04d", 0);
  char* line1[4] = {"F : ", fuel, "B : ", bombs};
  draw_text_line(app, x, y, 4, line1, colors);
  y += UI_TEXT_LINE_HEIGHT;
  char* line2[4] = {"SPD : ", speed, "ALT : ", alt};
  draw_text_line(app, x, y, 4, line2, colors);
  y += UI_TEXT_LINE_HEIGHT;
  char* line3[2] = {"SCORE : ", score};
  draw_text_line(app, x, y, 2, line3, colors);
}


