#include "base.h"
#include "light.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

bool light_render(struct game_state* gs, struct base *b, SDL_Renderer *rend) {
  SDL_SetRenderDrawColor(rend, b->color.r, b->color.g, b->color.b, b->color.a);
  SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
  SDL_RenderFillRect(rend, &b->frame);
  return true;
}

bool light_source_copy(struct base *src, struct base *dest) {
  dest->render = light_render;
  dest->copy = light_source_copy;
  return base_copy(src, dest);
}

bool light_source_init(struct base *b) {
  b->frame = (SDL_Rect){0,0,100,100};
  b->color = (SDL_Color){255, 255, 255, 190};
  b->render = light_render;
  b->copy = light_source_copy;
  return true;
}
