#include "Tree.h"
#include "../textures.h"

Tree tree_create(double x, double y) {
  SDL_Texture* texture = get_texture(TEXTURE_TREE);
  return (Tree) {x, y, texture};
}

Box tree_hitbox(const Tree* tree) {
  Vector center = vector_create(tree->x, tree->y, (double) TREE_HEIGHT / 2);
  return box_create_around_center(&center, TREE_WIDTH, TREE_WIDTH, TREE_HEIGHT);
}
