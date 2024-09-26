#include "draw.h"
#include "SDL_ttf.h"
#include "font.h"
#include "math.h"

void translate_vector(Vector* v, const App* app, const Vector* center) {
  double vx = v->x;
  v->x = app->left_padding + v->y - center->y + (double) app->scene_width / 2;
  v->y = app->top_padding + app->scene_height * 0.5 - vx + v->z * HEIGHT_Y_OFFSET + center->x;
}

void draw_point(const App* app, const Vector* center, const Vector* p) {
  Vector t = vector_copy(p);
  translate_vector(&t, app, center);
  SDL_RenderDrawPoint(app->renderer, (int) t.x, (int) t.y);
}

void draw_line(const App* app, const Vector* center, const Vector* a, const Vector* b) {
  Vector at = vector_copy(a);
  translate_vector(&at, app, center);
  Vector bt = vector_copy(b);
  translate_vector(&bt, app, center);
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

void draw_texture(const App* app, const Vector* center, SDL_Texture *texture, const Vector* pos, int width, int height) {
  Vector pos_copy = vector_copy(pos);
  translate_vector(&pos_copy, app, center);
  SDL_Rect dest;
  dest.x = (int) pos_copy.x - width / 2;
  dest.y = (int) pos_copy.y - height / 2;
  dest.w = width;
  dest.h = height;
  SDL_RenderCopy(app->renderer, texture, NULL, &dest);
}

void draw_tree(const App* app, const Vector* center, const Tree* tree) {
  Vector pos = vector_create(tree->x, tree->y, 0);
  translate_vector(&pos, app, center);
  pos.x -= (double) TREE_TEXTURE_WIDTH / 3;
  pos.y -= (double) TREE_TEXTURE_HEIGHT * (3.0 / 2);
  int rows = TREE_GRID_ROWS;
  int cols = TREE_GRID_COLUMNS;
  double dx = (double) TREE_TEXTURE_WIDTH / rows;
  double dy = (double) TREE_TEXTURE_HEIGHT / cols;
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
        SDL_SetRenderDrawColor(app->renderer, TREE_COLOR_R, TREE_COLOR_G, TREE_COLOR_B, 255);
      } else if (tree->color_grid [i][j] == BLACK) {
        SDL_SetRenderDrawColor(app->renderer, TREE_ROOT_COLOR_R, TREE_ROOT_COLOR_G, TREE_ROOT_COLOR_B, 255);
      }
      SDL_RenderFillRect(app->renderer, &rect);
    }
  }
}

SDL_Rect draw_text(const App* app, int x, int y, const char* text, const Color* color) {
  TTF_Font* font = get_font();
  SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text, (SDL_Color){color->r, color->g, color->b, 255});
  SDL_Texture* texture = SDL_CreateTextureFromSurface(app->renderer, surface);
  SDL_Rect dest = {x, y, surface->w, surface->h};
  SDL_RenderCopy(app->renderer, texture, NULL, &dest);
  return dest;
}

void draw_text_line(const App* app, int x, int y, int count, char** texts, Color** colors) {
  SDL_Rect rect;
  for (int i = 0; i < count; i++) {
    rect = draw_text(app, x, y, texts[i], colors[i]);
    x += rect.w;
  }
}

void draw_river(const App* app, const Vector* river) {
  SDL_Rect rect;
  rect.w = RIVER_WIDTH - RIVER_LEFT_BORDER_WIDTH;
  SDL_Rect border_rect;
  border_rect.w = RIVER_LEFT_BORDER_WIDTH;
  Vector diff, v;
  int square_count;
  for (int i = 0; i < RIVER_SEGMENT_COUNT - 1; i++) {
    diff = vector_copy(&river[i + 1]);
    vector_subtract(&diff, &river[i]);
    square_count = ceil(diff.y / RIVER_BORDER_SQUARE_WIDTH);
    diff.x = diff.x / square_count + 1;
    diff.y = diff.y / square_count + 1;
    rect.h = (int) diff.y + 1;
    border_rect.h = rect.h;
    v = vector_copy(&river[i]);
    diff.y = -diff.y;
    translate_vector(&v, app, &app->center);
    for (int j = 0; j < square_count; j++) {
      border_rect.x = (int) v.x;
      border_rect.y = (int) v.y;
      rect.x = border_rect.x + border_rect.w;
      rect.y = border_rect.y;
      SDL_SetRenderDrawColor(app->renderer, RIVER_BORDER_COLOR_R, RIVER_BORDER_COLOR_G, RIVER_BORDER_COLOR_B, 255);
      SDL_RenderFillRect(app->renderer, &border_rect);
      SDL_SetRenderDrawColor(app->renderer, RIVER_COLOR_R, RIVER_COLOR_G, RIVER_COLOR_B, 255);
      SDL_RenderFillRect(app->renderer, &rect);
      vector_sum(&v, &diff);
    }
  }
}

