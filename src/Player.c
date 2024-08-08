#include "Player.h"
#include "defs.h"

Player player_create(Vector* pos) {
  Box body_hb = box_create_around_center(pos, PLANE_BODY_LENGTH,
                                         PLANE_BODY_WIDTH, PLANE_BODY_HEIGHT);
  Box wings_hb = box_create_around_center(pos, PLANE_WINGS_LENGTH,
                                          PLANE_WINGS_WIDTH, PLANE_WINGS_HEIGHT);
  Box* hitboxes = malloc(sizeof(Box) * 2);
  hitboxes[0] = body_hb;
  hitboxes[1] = wings_hb;
  return (Player) {*pos, hitboxes};
}