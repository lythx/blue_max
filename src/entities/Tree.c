#include "Tree.h"
#include "math.h"
#include "../utils.h"

TREE_COLOR get_tile_color(int x, int y) {
  double dx = fabs((double) x / TREE_GRID_COLUMNS) * 2;
  double x_probability = -pow(dx, 8) + 1;
  double dy = fabs((double) y / TREE_GRID_ROWS) * 2;
  double y_probability = -pow(dy, 16) + 1;
  double probability = x_probability * y_probability;
  double r = rand_0_1();
  if (r > probability) {
    return NONE;
  }
  if (r / probability > 0.15) {
    return GREEN;
  }
  return BLACK;
}

Tree tree_create(double x, double y) {
  Tree tree;
  tree.x = x;
  tree.y = y;
  int rows = TREE_GRID_ROWS;
  int cols = TREE_GRID_COLUMNS;
  tree.color_grid[rows - 1][cols / 2 - 1] = BLACK;
  tree.color_grid[rows - 1][cols / 2] = BLACK;
  tree.color_grid[rows - 2][cols / 2 - 1] = BLACK;
  tree.color_grid[rows - 2][cols / 2] = BLACK;
  for (uint8_t i = 0; i < TREE_GRID_ROWS - 1; i++) {
    for (uint8_t j = 0; j < TREE_GRID_COLUMNS; j++) {
      tree.color_grid[i][j] = get_tile_color(i, j);
    }
  }
  return tree;
}

Box tree_hitbox(const Tree* tree) {
  Vector center = vector_create(tree->x, tree->y, (double) TREE_HEIGHT / 2);
  return box_create_around_center(&center, TREE_WIDTH, TREE_WIDTH, TREE_HEIGHT);
}
