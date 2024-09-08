#include "scene.h"

void init_scene(App* app) {
  int w, h;
  SDL_GetWindowSize(app->window, &w, &h);
  app->window_width = w;
  app->window_height = h;
  if ((double) w / h >= SCENE_WIDTH_TO_HEIGHT_RATIO) {
      app->scene_height = h;
      app->scene_width = (int) (h * SCENE_WIDTH_TO_HEIGHT_RATIO);
  } else {
    app->scene_width = w;
    app->scene_height = (int) ((double) w / SCENE_WIDTH_TO_HEIGHT_RATIO);
  }
  app->left_padding = (int) ((double) (app->window_width - app->scene_width) / 2);
  app->right_padding = (int) ((double) (app->window_width - app->scene_width) / 2);
  app->top_padding = (int) ((double) (app->window_height - app->scene_height) / 2);
  app->bottom_padding = (int) ((double) (app->window_height - app->scene_height) / 2);
  app->center = vector_create(app->right_padding + (double) app->scene_width / 2,
                              app->top_padding + (double) app->scene_height / 2, 0);
}
