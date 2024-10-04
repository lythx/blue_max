#include "scene.h"

void init_scene(App* app) {
  int w, h, display_h, vertical_margin;
  SDL_GetWindowSize(app->window, &w, &h);
  app->window_width = w;
  app->window_height = h;
  if ((double) w / h >= DISPLAY_WIDTH_TO_HEIGHT_RATIO) {
    display_h = h;
    app->scene_width = (int) (h * DISPLAY_WIDTH_TO_HEIGHT_RATIO);
    vertical_margin = 0;
  } else {
    app->scene_width = w;
    display_h = (int) ((double) w / DISPLAY_WIDTH_TO_HEIGHT_RATIO);
    vertical_margin = (int) ((double) (h - display_h) / 2);
  }
  app->scene_height = (int) (display_h * FLEX_SCENE);
  app->left_padding = (int) ((double) (app->window_width - app->scene_width) / 2);
  app->right_padding = (int) ((double) (app->window_width - app->scene_width) / 2);
  app->top_padding = (int) (display_h * FLEX_TOP_PADDING) + vertical_margin;
  app->bottom_padding = (int) (display_h * FLEX_BOTTOM_UI) + vertical_margin;
  app->center = vector_create(app->right_padding + (double) app->scene_width / 2,
                              app->top_padding + (double) app->scene_height / 2, 0);
  app->display_scale = (double) app->window_width / DEFAULT_WINDOW_WIDTH;
}
