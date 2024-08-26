#ifndef BLUE_MAX_TREE_H
#define BLUE_MAX_TREE_H

#include "../geometry.h"
#include "../defs.h"

typedef struct {
    double x;
    double y;
    SDL_Texture* texture;
} Tree;

Tree tree_create(double x, double y);

Box tree_hitbox(const Tree* tree);

#endif //BLUE_MAX_TREE_H
