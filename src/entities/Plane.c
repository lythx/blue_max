#include <time.h>
#include "Plane.h"
#include "../init_SDL.h"

Plane plane_create(const App* app, Vector* pos, PLANE_DIRECTION direction) {
  Box body_hb = box_create_around_center(pos, PLANE_BODY_LENGTH,
                                         PLANE_BODY_WIDTH, PLANE_BODY_HEIGHT);
  Box wings_hb = box_create_around_center(pos, PLANE_WINGS_LENGTH,
                                          PLANE_WINGS_WIDTH, PLANE_WINGS_HEIGHT);
  Box* hitboxes = malloc(sizeof(Box) * 2);
  hitboxes[0] = body_hb;
  hitboxes[1] = wings_hb;
  SDL_Texture* texture = load_texture(app, "../assets/player.png");
  return (Plane) {*pos, hitboxes, direction, 0, texture};
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

Projectile plane_shoot(const App* app, Plane* plane) {
  Vector pos = vector_copy(&plane->pos);
  plane->last_shot_timestamp = time(NULL);
  return projectile_create(app, &pos, plane->direction == PLANE_UP ? PROJECTILE_PLANE_UP : PROJECTILE_PLANE_DOWN);
}

void plane_destroy(Plane* plane) {
  free(plane->hitboxes);
}
