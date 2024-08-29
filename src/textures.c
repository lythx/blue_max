#include "textures.h"
#include "SDL_image.h"

#define TEXTURE_COUNT 20

SDL_Texture* textures[TEXTURE_COUNT];

SDL_Texture* load_texture(const App* app, const char* filename) {
  SDL_Texture *texture;
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Loading %s", filename);
  texture = IMG_LoadTexture(app->renderer, filename);
  return texture;
}

void init_textures(const App* app) {
  textures[TEXTURE_PLAYER_1] = load_texture(app, "../assets/player1.png");
  textures[TEXTURE_PLAYER_LEFT_1] = load_texture(app, "../assets/player_left1.png");
  textures[TEXTURE_PLAYER_RIGHT_1] = load_texture(app, "../assets/player_right1.png");
  textures[TEXTURE_PLAYER_2] = load_texture(app, "../assets/player2.png");
  textures[TEXTURE_PLAYER_LEFT_2] = load_texture(app, "../assets/player_left2.png");
  textures[TEXTURE_PLAYER_RIGHT_2] = load_texture(app, "../assets/player_right2.png");
  textures[TEXTURE_PLANE_1] = load_texture(app, "../assets/plane1.png");
  textures[TEXTURE_PLANE_2] = load_texture(app, "../assets/plane2.png");
  textures[TEXTURE_PLANE_LEFT] = load_texture(app, "../assets/player1.png");
  textures[TEXTURE_PLANE_RIGHT] = load_texture(app, "../assets/player1.png");
  textures[TEXTURE_TREE] = load_texture(app, "../assets/player1.png");
  textures[TEXTURE_PROJECTILE] = load_texture(app, "../assets/player1.png");
  textures[TEXTURE_BUILDING] = load_texture(app, "../assets/player1.png");
}

SDL_Texture* get_texture(TEXTURE texture) {
  return textures[texture];
}
