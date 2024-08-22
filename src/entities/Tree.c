#include "Tree.h"
#include "../init_SDL.h"

Tree tree_create(const App* app, double x, double y) {
  SDL_Texture* texture = load_texture(app, "../assets/player.png");
  return (Tree) {x, y, texture};
}

Box tree_hitbox(const Tree* tree) {
  Vector center = vector_create(tree->x, tree->y, (double) TREE_HEIGHT / 2);
  return box_create_around_center(&center, TREE_WIDTH, TREE_WIDTH, TREE_HEIGHT);
}
