#include "Tree.h"
#include "math.h"
#include "../utils.h"

double grid_probability[TREE_GRID_ROWS][TREE_GRID_COLUMNS] = {
    {0.05, 0.1, 0.5, 0.7, 0.7, 0.5, 0.1, 0.05},
    {0.1, 0.3, 0.6, 0.9, 0.9, 0.6, 0.3, 0.1},
    {0.2, 0.4, 0.7, 0.9, 0.9, 0.7, 0.4, 0.2},
    {0.5, 0.8, 0.9, 0.9, 0.9, 0.9, 0.8, 0.5},
    {0.8, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.8},
    {0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9},
    {0.8, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.8},
    {0.5, 0.8, 0.9, 0.9, 0.9, 0.9, 0.8, 0.5},
    {0.2, 0.5, 0.9, 0.9, 0.9, 0.9, 0.4, 0.2},
    {0.1, 0.4, 0.9, 0.9, 0.9, 0.9, 0.4, 0.1},
    {0.05, 0.1, 0.8, 0.9, 0.9, 0.8, 0.1, 0.05},
    {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
};

uint8_t get_tile_color(int x, int y) {
  double r = rand_0_1();
  if (r > grid_probability[x][y]) {
    return NONE;
  }
  if (r / grid_probability[x][y] > 0.03) {
    return GREEN;
  }
  return BLACK;
}

Tree tree_create(double x, double y) {
  Tree tree;
  tree.x = x;
  tree.y = y;
  for (uint8_t i = 0; i < TREE_GRID_ROWS; i++) {
    for (uint8_t j = 0; j < TREE_GRID_COLUMNS; j++) {
      tree.color_grid[i][j] = get_tile_color(i, j);
    }
  }
  for (uint8_t i = 0; i < TREE_GRID_ROWS; i++) {
    for (uint8_t j = 0; j < TREE_GRID_COLUMNS; j++) {
      if ((i == 0 || tree.color_grid[i - 1][j] == NONE) &&
          (j == 0 || tree.color_grid[i][j - 1] == NONE) &&
          (i == TREE_GRID_ROWS - 1 || tree.color_grid[i + 1][j] == NONE) &&
          (j == TREE_GRID_COLUMNS - 1 || tree.color_grid[i][j + 1] == NONE)) {
        tree.color_grid[i][j] = NONE;
      }
    }
  }
  tree.color_grid[TREE_GRID_ROWS - 1][TREE_GRID_COLUMNS / 2 - 1] = BLACK;
  tree.color_grid[TREE_GRID_ROWS - 1][TREE_GRID_COLUMNS / 2] = BLACK;
  if (rand_0_1() > 0.2) {
    tree.color_grid[TREE_GRID_ROWS - 2][TREE_GRID_COLUMNS / 2 - 1] = BLACK;
  } else{
    tree.color_grid[TREE_GRID_ROWS - 2][TREE_GRID_COLUMNS / 2 - 1] = GREEN;
  }
  if (rand_0_1() > 0.2) {
    tree.color_grid[TREE_GRID_ROWS - 2][TREE_GRID_COLUMNS / 2] = BLACK;
  } else{
    tree.color_grid[TREE_GRID_ROWS - 2][TREE_GRID_COLUMNS / 2] = GREEN;
  }
  return tree;
}

Box tree_hitbox(const Tree* tree) {
  Vector center = vector_create(tree->x, tree->y, (double) TREE_HEIGHT / 2);
  return box_create_around_center(&center, TREE_WIDTH, TREE_WIDTH, TREE_HEIGHT);
}
