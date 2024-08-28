#include "draw.h"
#include "config.h"
#include "SDL_image.h"

void translate_vector(Vector* v, const Vector* center) {
  double vx = v->x;
  v->x = v->y - center->y + (double) WINDOW_WIDTH / 2;
  v->y = WINDOW_HEIGHT * 0.5 - vx + v->z * HEIGHT_Y_OFFSET + center->x;
}

void draw_point(const App* app, const Vector* center, const Vector* p) {
  Vector t = vector_copy(p);
  translate_vector(&t, center);
  SDL_RenderDrawPoint(app->renderer, (int) t.x, (int) t.y);
}

void draw_line(const App* app, const Vector* center, const Vector* a, const Vector* b) {
  Vector at = vector_copy(a);
  translate_vector(&at, center);
  Vector bt = vector_copy(b);
  translate_vector(&bt, center);
  SDL_RenderDrawLine(app->renderer, (int) at.x, (int) at.y, (int) bt.x, (int) bt.y);
}

void draw_box(const App* app, const Vector* center, const Box* b) {
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

  draw_line(app, center, &down1, &down2);
  draw_line(app, center, &down2, &down3);
  draw_line(app, center, &down3, &down4);
  draw_line(app, center, &down4, &down1);

  draw_line(app, center, &down1, &up1);
  draw_line(app, center, &down2, &up2);
  draw_line(app, center, &down3, &up3);
  draw_line(app, center, &down4, &up4);

  draw_line(app, center, &up1, &up2);
  draw_line(app, center, &up2, &up3);
  draw_line(app, center, &up3, &up4);
  draw_line(app, center, &up4, &up1);
}

void draw_hitboxes(const App* app, const Vector* center, const Box* hitboxes, size_t size) {
  for(size_t i = 0; i < size; i++) {
    draw_box(app, center, &hitboxes[i]);
  }
}

void draw_texture(const App* app, const Vector* center, SDL_Texture *texture, const Vector* pos) {
  Vector pos_copy = vector_copy(pos);
  translate_vector(&pos_copy, center);
  SDL_Rect dest;
  dest.x = (int) pos_copy.x;
  dest.y = (int) pos_copy.y;
  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
  dest.x -= dest.w / 2;
  dest.y -= dest.h / 2;
  SDL_RenderCopy(app->renderer, texture, NULL, &dest);
}

void draw_tree(const App* app, const Vector* center, const Tree* tree) {
  Vector pos = vector_create(tree->x, tree->y, 0);
  translate_vector(&pos, center);
  int rows = TREE_GRID_ROWS;
  int cols = TREE_GRID_COLUMNS;
  double dx = (double) TREE_WIDTH / rows;
  double dy = (double) TREE_HEIGHT / cols;
  SDL_Rect rect;
  rect.w = (int) dx + 1;
  rect.h = (int) dy + 1;
  for (uint8_t i = 0; i < TREE_GRID_ROWS; i++) {
    for (uint8_t j = 0; j < TREE_GRID_COLUMNS; j++) {
      if (tree->color_grid[i][j] == NONE) {
        continue;
      }
      rect.x = (int) (pos.x + dx * j);
      rect.y = (int) (pos.y + dy * i);
      if (tree->color_grid[i][j] == GREEN) {
        SDL_SetRenderDrawColor(app->renderer, 0, 100, 0, 255);
      } else if (tree->color_grid [i][j] == BLACK) {
        SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
      }
      SDL_RenderFillRect(app->renderer, &rect);
    }
  }
}