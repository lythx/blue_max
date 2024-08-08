#ifndef BLUE_MAX_PLAYER_H
#define BLUE_MAX_PLAYER_H

#include "geometry.h"

typedef struct {
  Vector pos;
  Box* hitboxes;
} Player;

Player player_create(Vector* pos);

#endif //BLUE_MAX_PLAYER_H
