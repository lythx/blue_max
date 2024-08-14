#ifndef BLUE_MAX_BOX_H
#define BLUE_MAX_BOX_H

#include "Vector.h"
#include "SDL.h"

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

Box box_create_around_center(const Vector* center,
                             double length, double width, double height);

int box_intersects(const Box* b1, const Box* b2);

int box_point_intersects(const Box* b, const Vector* p);

int box_intersects_array(const Box* arr1, uint8_t size1, const Box* arr2, uint8_t size2);

void box_print(const Box* b);

#endif //BLUE_MAX_BOX_H
