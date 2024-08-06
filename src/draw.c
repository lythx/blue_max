#include "draw.h"
#include "config.h"

void translate_vector(Vector* v) {
  double vx = v->x;
  v->x = v->y;
  v->y = WINDOW_HEIGHT - vx + v->z * HEIGHT_Y_OFFSET;
}

void draw_point(const App* app, const Vector* p) {
  Vector t = vector_copy(p);
  translate_vector(&t);
  SDL_RenderDrawPoint(app->renderer, (int) t.x, (int) t.y);
}

void draw_line(const App* app, const Vector* a, const Vector* b) {
  Vector at = vector_copy(a);
  translate_vector(&at);
  Vector bt = vector_copy(b);
  translate_vector(&bt);
  SDL_RenderDrawLine(app->renderer, (int) at.x, (int) at.y, (int) bt.x, (int) bt.y);
}

void draw_box(const App* app, const Box* b) {
  Vector down1, down2, down3, down4, up1, up2, up3, up4;

  down1 = vector_create(b->x, b->y, b->z);
  down2 = vector_create(b->x, b->y + b->width, b->z);
  down4 = vector_create(b->x + b->length, b->y, b->z);
  vector_rotate_about_origin(&down4, &down1);
  down3 = vector_create(down4.x, down4.y + b->width, down4.z);

  double z = b->z + b->height;
  up1 = vector_create(down1.x, down1.y, z);
  up2 = vector_create(down2.x, down2.y, z);
  up3 = vector_create(down3.x, down3.y, z);
  up4 = vector_create(down4.x, down4.y, z);

  draw_line(app, &down1, &down2);
  draw_line(app, &down2, &down3);
  draw_line(app, &down3, &down4);
  draw_line(app, &down4, &down1);

  draw_line(app, &down1, &up1);
  draw_line(app, &down2, &up2);
  draw_line(app, &down3, &up3);
  draw_line(app, &down4, &up4);

  draw_line(app, &up1, &up2);
  draw_line(app, &up2, &up3);
  draw_line(app, &up3, &up4);
  draw_line(app, &up4, &up1);
}