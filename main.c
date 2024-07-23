#include "driver/command.h"
#include "types/state_types.h"
#include "types/win_types.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_ttf.h>
#include "ui/win.h"

#include <stdbool.h>
#include <time.h>

void sdl_init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "couldn't load video\n");
    exit(1);
  }
  if (TTF_Init() == -1) {
    fprintf(stderr, "failed ttf init\n");
    exit(1);
  }
}

void sdl_deinit() {
  TTF_Quit();
  SDL_Quit();
}

void load_lib(struct command *cmd) {
  if (!command_load(cmd, "bin/libdriver.so")) {
    fprintf(stderr, "command could not be loaded.\n");
    exit(1);
  }
}

void update_state(struct game_state *gs, struct win *w) {
  if (gs->w.window == NULL) {
    gs->w = *w;
  }
}

int main(int argc, char **argv) {
  sdl_init();
  struct command cmd;
  command_init(&cmd);
  load_lib(&cmd);
  struct win w;
  win_init(&w, 640, 480);
  struct game_state state = cmd.init();
  state.w = w;
  clock_t init;
  SDL_Event e;
  while(cmd.is_running()) {
    init = clock();
    while(SDL_PollEvent(&e)) {
      if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_r) {
          command_unload(&cmd);
          load_lib(&cmd);
        }
      }
      state = cmd.event(&e, state);
      update_state(&state, &w);
    }
    state = cmd.update(state);
    update_state(&state, &w);
    state = cmd.render(state);
    update_state(&state, &w);
    double cur_exec_time = ((clock() - init) / (double)CLOCKS_PER_SEC);
    double tick = 1000.0 / 60;
    if (cur_exec_time < tick) {
      double delay = tick - cur_exec_time;
      SDL_Delay(delay);
    }
  }
  cmd.deinit();
  command_unload(&cmd);
  win_free(&w);
  sdl_deinit();
  return 0;
}
