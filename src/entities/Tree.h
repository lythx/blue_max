#ifndef BLUE_MAX_TREE_H
#define BLUE_MAX_TREE_H

#include "../geometry.h"
#include "../defs.h"

typedef enum {
    NONE = 0,
    GREEN = 1,
    BLACK = 2
} TREE_COLOR;

typedef struct {
    double x;
    double y;
    uint8_t color_grid[TREE_GRID_ROWS][TREE_GRID_COLUMNS];
} Tree;

Tree tree_create(double x, double y);

Box tree_hitbox(const Tree* tree);

#endif //BLUE_MAX_TREE_H
