#include "Projectile.h"
#include "../textures.h"

Projectile projectile_create(Vector* pos, PROJECTILE_ORIGIN origin) {
  Box hitbox = box_create_around_center(pos, PROJECTILE_LENGTH,
                                         PROJECTILE_DIAMETER, PROJECTILE_DIAMETER);
  SDL_Texture* texture = get_texture(TEXTURE_PROJECTILE);
  return (Projectile) {*pos, hitbox, texture, origin};
}

void projectile_move(Projectile* projectile) {
  Vector diff;
  if (projectile->origin == PROJECTILE_PLAYER) {
    diff = vector_create(PROJECTILE_SPEED_PLAYER, 0, 0);
  } else if (projectile->origin == PROJECTILE_PLANE_UP) {
    diff = vector_create(PROJECTILE_SPEED_UP, 0, 0);
  } else {
    diff = vector_create(-PROJECTILE_SPEED_DOWN, 0, 0);
  }
  vector_rotate(&diff);
  vector_sum(&projectile->pos, &diff);
  projectile->hitbox.x += diff.x;
  projectile->hitbox.y += diff.y;
}
