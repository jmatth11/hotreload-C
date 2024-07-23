#include "player.h"
#include "objects/base.h"
#include "types/state_types.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include "ui/win.h"

bool player_render(struct game_state *gs, struct base *b, SDL_Renderer *rend) {
  SDL_Rect win_rect = win_cur_size(&gs->w);
  struct character *local = (struct character *)b->__internal;
  b->frame.x += local->velocity.x;
  b->frame.y += local->velocity.y;
  if ((b->frame.y + b->frame.h) >= win_rect.h) local->velocity.y = -local->velocity.y;
  if ((b->frame.x + b->frame.w) >= win_rect.w) local->velocity.x = -local->velocity.x;
  if (b->frame.y <= 0) local->velocity.y = -local->velocity.y;
  if (b->frame.x <= 0) local->velocity.x = -local->velocity.x;
  SDL_SetRenderDrawColor(rend, b->color.r, 255, b->color.b, b->color.a);
  SDL_RenderFillRect(rend, &b->frame);
  return true;
}

bool player_new(struct base *b) {
  b->color = (SDL_Color){255,0,0,255};
  b->frame = (SDL_Rect){20, 20, 40, 40};
  b->mask_type = PLAYER;
  struct character *local = malloc(sizeof(struct character));
  local->health = 100;
  local->name = NULL;
  local->velocity = (SDL_FPoint){
    .x = 1,
    .y = 1,
  };
  b->__internal = local;
  b->render = player_render;
  b->copy = player_copy;
  return true;
}

bool player_copy(struct base *src, struct base *dest) {
  if (!base_copy(src, dest)) return false;
  struct character *src_local = (struct character *)src->__internal;
  struct character *local = malloc(sizeof(struct character));
  local->health = src_local->health;
  local->name = src_local->name;
  local->velocity = src_local->velocity;
  dest->__internal = local;
  dest->render = player_render;
  dest->copy = player_copy;
  return true;
}

void player_free(struct base *b) {
  if (b->__internal != NULL) {
    struct character *local = (struct character *)b->__internal;
    if (local->name != NULL) {
      free(local->name);
    }
    free(b->__internal);
  }
}
