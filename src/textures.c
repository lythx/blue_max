#include "textures.h"
#include "SDL_image.h"

#define TEXTURE_COUNT 9

SDL_Texture* textures[TEXTURE_COUNT];

SDL_Texture* load_texture(const App* app, const char* filename) {
  SDL_Texture *texture;
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Loading %s", filename);
  texture = IMG_LoadTexture(app->renderer, filename);
  return texture;
}

void init_textures(const App* app) {
  textures[TEXTURE_PLAYER] = load_texture(app, "../assets/player.png");
  textures[TEXTURE_PLAYER_LEFT] = load_texture(app, "../assets/player.png");
  textures[TEXTURE_PLAYER_RIGHT] = load_texture(app, "../assets/player.png");
  textures[TEXTURE_PLANE] = load_texture(app, "../assets/player.png");
  textures[TEXTURE_PLANE_LEFT] = load_texture(app, "../assets/player.png");
  textures[TEXTURE_PLANE_RIGHT] = load_texture(app, "../assets/player.png");
  textures[TEXTURE_TREE] = load_texture(app, "../assets/player.png");
  textures[TEXTURE_PROJECTILE] = load_texture(app, "../assets/player.png");
  textures[TEXTURE_BUILDING] = load_texture(app, "../assets/player.png");
}

SDL_Texture* get_texture(TEXTURE texture) {
  return textures[texture];
}
