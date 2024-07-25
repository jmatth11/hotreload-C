#include "driver.h"
#include "state/game.h"
#include "objects/player.h"
#include "types/state_types.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

static bool reload = true;

static void reload_game_state(struct game_state *gs) {
  if (reload) {
    object_array *arr = &gs->current_level.objects;
    for (int i = 0; i < arr->len; ++i) {
      struct base *obj = &arr->object_data[i];
      if (!obj->reload(gs, obj)) {
        fprintf(stderr, "object failed to reload\n");
      }
    }
    reload = false;
  }
}

void* init() {
  reload = false;
  struct game_state *gs = malloc(sizeof(struct game_state));
  if (!game_init(gs)) {
    fprintf(stderr, "game state failed to initialize\n");
    exit(1);
  }
  struct level_state lvl1;
  if (!level_init(&lvl1)) {
    fprintf(stderr, "level 1 failed to initialize\n");
    exit(1);
  }
  gs->current_level = lvl1;
  struct base player;
  if (!player_new(&player)) {
    fprintf(stderr, "player failed to initialize\n");
    exit(1);
  }
  level_add_object(&gs->current_level, player);
  gs->current_level.loaded = true;
  return gs;
}

void update(void* ctx) {
}

void event(SDL_Event *e, void* ctx) {
  struct game_state *gs = (struct game_state*)ctx;
  reload_game_state(gs);
  if (e->type == SDL_QUIT) {
    gs->running = false;
  }
}

bool is_running(void* ctx) {
  struct game_state *gs = (struct game_state*)ctx;
  reload_game_state(gs);
  return gs->running;
}

void render(void* ctx) {
  struct game_state *gs = (struct game_state*)ctx;
  reload_game_state(gs);
  SDL_SetRenderDrawColor(gs->w.renderer, 0, 0, 0, 0xFF);
  SDL_RenderClear(gs->w.renderer);
  if (!game_render(gs)) {
    fprintf(stderr, "game failed to render.\n");
  }
  SDL_RenderPresent(gs->w.renderer);
}

void deinit(void *ctx) {
  struct game_state *gs = (struct game_state*)ctx;
  reload_game_state(gs);
  game_free(gs);
  free(gs);
}
