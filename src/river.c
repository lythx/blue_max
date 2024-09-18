#include "river.h"

#include <stdio.h>

#include "defs.h"

Vector river[RIVER_SEGMENT_COUNT];
int start_index = 0;

void river_initialize(const Vector* center)
{
    Vector v = vector_create(-SPAWN_DISTANCE_TO_CENTER, 0, 0);
    vector_rotate(&v);
    vector_sum(&v, center);
    Vector diff = vector_create(SPAWN_DISTANCE_TO_CENTER * 2.0 / RIVER_SEGMENT_COUNT, 0, 0);
    double y_offset = -100;
    for (size_t i = 0; i < RIVER_SEGMENT_COUNT; i++)
    {
        river[i] = vector_create(v.x - y_offset, v.y, 0);
        vector_sum(&v, &diff);
    }
}

void river_generate_next(const Vector* center);

void river_point_intersection(const Vector* p);

Vector* river_get()
{
    return river;
}
