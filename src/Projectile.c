#include "Projectile.h"
#include "init_SDL.h"

Projectile projectile_create(const App* app, Vector* pos) {
  Box hitbox = box_create_around_center(pos, PROJECTILE_LENGTH,
                                         PROJECTILE_DIAMETER, PROJECTILE_DIAMETER);
  SDL_Texture* texture = load_texture(app, "../assets/player.png");
  return (Projectile) {*pos, hitbox, texture};
}

void projectile_move(Projectile* projectile, PROJECTILE_ORIGIN origin) {
  Vector diff;
  if (origin == PROJECTILE_PLAYER) {
    diff = vector_create(PROJECTILE_SPEED_PLAYER, 0, 0);
  } else if (origin == PROJECTILE_PLANE_UP) {
    diff = vector_create(PROJECTILE_SPEED_UP, 0, 0);
  } else {
    diff = vector_create(-PROJECTILE_SPEED_DOWN, 0, 0);
  }
  vector_rotate(&diff);
  vector_sum(&projectile->pos, &diff);
  projectile->hitbox.x += diff.x;
  projectile->hitbox.y += diff.y;
}
