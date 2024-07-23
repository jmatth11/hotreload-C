#ifndef SGF_BASE_OBJECT_H
#define SGF_BASE_OBJECT_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>

enum object_masks {
  NONE = 0,
  PLAYER = 1,
  ENEMY = 2,
};

struct character {
  int health;
  char *name;
  SDL_FPoint velocity;
};

struct game_state;

struct base {
  void *__internal;
  SDL_Color color;
  SDL_Rect frame;
  SDL_Rect collision;
  uint64_t collision_mask;
  uint64_t mask_type;
  bool (*render)(struct game_state *, struct base*, SDL_Renderer*);
  bool (*copy)(struct base*src, struct base*dest);
};

bool base_copy(struct base *src, struct base *dest);

#endif
