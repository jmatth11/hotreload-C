#include "driver/command.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <time.h>

static void sdl_init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "couldn't load video\n");
    exit(1);
  }
  if (TTF_Init() == -1) {
    fprintf(stderr, "failed ttf init\n");
    exit(1);
  }
}

static void sdl_deinit() {
  TTF_Quit();
  SDL_Quit();
}

static void load_lib(struct command *cmd) {
  if (!command_load(cmd, "bin/libdriver.so\0")) {
    fprintf(stderr, "command could not be loaded.\n");
    exit(1);
  }
}

int main(int argc, char **argv) {
  sdl_init();
  struct command cmd;
  command_init(&cmd);
  load_lib(&cmd);
  void* state = cmd.init();
  clock_t init;
  SDL_Event e;
  while(cmd.is_running(state)) {
    init = clock();
    while(SDL_PollEvent(&e)) {
      if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_r) {
          if (!command_unload(&cmd)) {
            fprintf(stderr, "could not unload command.\n");
            exit(1);
          }
          load_lib(&cmd);
        }
      }
      cmd.event(&e, state);
    }
    cmd.update(state);
    cmd.render(state);
    double cur_exec_time = ((clock() - init) / (double)CLOCKS_PER_SEC);
    double tick = 1000.0 / 60;
    if (cur_exec_time < tick) {
      double delay = tick - cur_exec_time;
      SDL_Delay(delay);
    }
  }
  cmd.deinit(state);
  command_unload(&cmd);
  sdl_deinit();
  return 0;
}
