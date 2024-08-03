#ifndef BLUE_MAX_BOX_H
#define BLUE_MAX_BOX_H

#include "Vector.h"

typedef struct {
    double min_x;
    double min_y;
    double min_z;
    double max_x;
    double max_y;
    double max_z;
} Box;

Box box_create(double min_x, double min_y, double min_z,
                     double max_x, double max_y, double max_z);

Box box_create_from_vectors(const Vector* min, const Vector* max);

int box_intersects(const Box* b1, const Box* b2);

int box_point_intersects(const Box* b, const Vector* p);

void box_print(const Box* b);

#endif //BLUE_MAX_BOX_H
