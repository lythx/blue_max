#ifndef BLUE_MAX_DRAW_H
#define BLUE_MAX_DRAW_H

#include "Vector.h"
#include "Box.h"
#include "defs.h"

void draw_point(const App* app, const Vector* p);

void draw_line(const App* app, const Vector* a, const Vector* b);

void draw_box(const App* app, const Box* b);

#endif //BLUE_MAX_DRAW_H
