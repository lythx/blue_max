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

int search_compare(void* a, void* b)
{
    return ((Vector*) a)->x <= ((Vector*) b)->x ? 1 : -1;
}

int river_point_intersection(const Vector* p)
{
    Vector* v1 = bsearch(p, river, RIVER_SEGMENT_COUNT, sizeof(Vector), search_compare);
    Vector* v2 = v1 + 1;
    Vector slope = vector_copy(v2);
    vector_subtract(&slope, v1);
    double y_min = v1->y + (p->x - v1->x) * slope.y / slope.x;
    return y_min <= p->y && p->y <= y_min + RIVER_WIDTH;
}

Vector* river_get()
{
    return river;
}
