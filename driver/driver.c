#include "driver.h"
#include "state/game.h"
#include "objects/light.h"
#include "objects/player.h"
#include "types/state_types.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct game_state gs;

void update_game_state(struct game_state *local) {
  if (gs.running == false) {
    game_copy(local, &gs);
    game_free(local);
  } else if (gs.w.window == NULL) {
    gs.w = local->w;
  }
}

struct game_state init() {
  if (!game_init(&gs)) {
    fprintf(stderr, "game state failed to initialize\n");
    exit(1);
  }
  struct level_state lvl1;
  if (!level_init(&lvl1)) {
    fprintf(stderr, "level 1 failed to initialize\n");
    exit(1);
  }
  gs.current_level = lvl1;
  struct base player;
  if (!player_new(&player)) {
    fprintf(stderr, "player failed to initialize\n");
    exit(1);
  }
  level_add_object(&gs.current_level, player);
  //struct base light;
  //if (!light_source_init(&light)) {
  //  fprintf(stderr, "light failed to initialize\n");
  //  exit(1);
  //}
  //level_add_object(&gs.current_level, light);
  gs.current_level.loaded = true;
  return gs;
}

struct game_state update(struct game_state ctx) {
  update_game_state(&ctx);

  return gs;
}

struct game_state event(SDL_Event *e, struct game_state ctx) {
  update_game_state(&ctx);
  if (e->type == SDL_QUIT) {
    gs.running = false;
  } else if (e->type == SDL_KEYDOWN) {
    //handle_keydown(&d, &e);
  }
  return gs;
}

bool is_running() {
  return gs.running;
}

struct game_state render(struct game_state ctx) {
  update_game_state(&ctx);
  SDL_SetRenderDrawColor(gs.w.renderer, 0, 0, 0, 0xFF);
  SDL_RenderClear(gs.w.renderer);
  if (!game_render(&gs)) {
    fprintf(stderr, "game failed to render.\n");
  }
  SDL_RenderPresent(gs.w.renderer);
  return gs;
}

void deinit() {
  game_free(&gs);
}
