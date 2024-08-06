#ifndef BLUE_MAX_BOX_H
#define BLUE_MAX_BOX_H

#include "Vector.h"

typedef struct {
    double x;
    double y;
    double z;
    double length;
    double width;
    double height;
} Box;

Box box_create(double x, double y, double z,
                     double length, double width, double height);

int box_intersects(const Box* b1, const Box* b2);

int box_point_intersects(const Box* b, const Vector* p);

void box_print(const Box* b);

#endif //BLUE_MAX_BOX_H
