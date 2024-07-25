#ifndef SGF_BASE_OBJECT_H
#define SGF_BASE_OBJECT_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>

/**
 * Mask types.
 */
enum object_masks {
  NONE = 0,
  PLAYER = 1,
  ENEMY = 2,
};

/**
 * Simple character object.
 */
struct character {
  int health;
  char *name;
  SDL_FPoint velocity;
};

// forward declare
struct game_state;

/**
 * Base object to keep track of general properties and methods.
 */
struct base {
  void *__internal;
  SDL_Color color;
  SDL_Rect frame;
  SDL_Rect collision;
  uint64_t collision_mask;
  uint64_t mask_type;
  /**
   * Render method for how your object should be rendered.
   */
  bool (*render)(struct game_state *, struct base*, SDL_Renderer*);
  /**
   * Reload method for when the game state is hot-reloaded.
   */
  bool (*reload)(struct game_state *, struct base*);
  /**
   * Copy method.
   */
  bool (*copy)(struct base*src, struct base*dest);
};

/**
 * Base object copy function.
 */
bool base_copy(struct base *src, struct base *dest);

#endif
