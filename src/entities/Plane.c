#include "../utils.h"
#include "Plane.h"
#include "../textures.h"

Plane plane_create(Vector* pos, PLANE_DIRECTION direction) {
  Box body_hb = box_create_around_center(pos, PLANE_BODY_LENGTH,
                                         PLANE_BODY_WIDTH, PLANE_BODY_HEIGHT);
  Box wings_hb = box_create_around_center(pos, PLANE_WINGS_LENGTH,
                                          PLANE_WINGS_WIDTH, PLANE_WINGS_HEIGHT);
  Box* hitboxes = malloc(sizeof(Box) * 2);
  hitboxes[0] = body_hb;
  hitboxes[1] = wings_hb;
  return (Plane) {*pos, hitboxes, direction, 0, 0};
}

void plane_move(Plane* plane) {
  Vector diff = vector_create(plane->direction == PLANE_UP ? PLANE_UP_SPEED : -PLANE_DOWN_SPEED, 0, 0);
  vector_rotate(&diff);
  vector_sum(&plane->pos, &diff);
  plane->hitboxes[0].x += diff.x;
  plane->hitboxes[0].y += diff.y;
  plane->hitboxes[1].x += diff.x;
  plane->hitboxes[1].y += diff.y;
}

Projectile plane_shoot(Plane* plane) {
  Vector pos = vector_copy(&plane->pos);
  plane->last_shot_timestamp = time_ms();
  return projectile_create(&pos, plane->direction == PLANE_UP ? PROJECTILE_PLANE_UP : PROJECTILE_PLANE_DOWN);
}

SDL_Texture* plane_get_texture(const Plane* plane) {
  if (plane->texture_type == 1) {
    return get_texture(TEXTURE_PLANE_1);
  } else { // plane->texture_type == 2
    return get_texture(TEXTURE_PLANE_2);
  }
}

void plane_destroy(Plane* plane) {
  free(plane->hitboxes);
}
