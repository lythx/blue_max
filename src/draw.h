#ifndef BLUE_MAX_DRAW_H
#define BLUE_MAX_DRAW_H

#include "geometry.h"
#include "defs.h"
#include "entities/Tree.h"

void draw_point(const App* app, const Vector* center, const Vector* p);

void draw_line(const App* app, const Vector* center, const Vector* a, const Vector* b);

void draw_box(const App* app, const Vector* center, const Box* b);

void draw_hitboxes(const App* app, const Vector* center, const Box* hitboxes, size_t size);

void draw_texture(const App* app, const Vector* center, SDL_Texture *texture, const Vector* pos, int width, int height);

void draw_tree(const App* app, const Vector* center, const Tree* tree);

SDL_Rect draw_text(const App* app, int x, int y, const char* text, const Color* color);

void draw_text_line(const App* app, int x, int y, int count, char** texts, Color** colors);

#endif //BLUE_MAX_DRAW_H
