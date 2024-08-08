#ifndef BLUE_MAX_DRAW_H
#define BLUE_MAX_DRAW_H

#include "geometry.h"
#include "defs.h"

void draw_point(const App* app, const Vector* p);

void draw_line(const App* app, const Vector* a, const Vector* b);

void draw_box(const App* app, const Box* b);

void draw_hitboxes(const App* app, const Box* hitboxes, size_t size);

#endif //BLUE_MAX_DRAW_H
