#ifndef COMMAND_H
#define COMMAND_H

#include <SDL2/SDL_events.h>
#include <stdbool.h>

#include "types/state_types.h"

struct command {
  void *handler;
  struct game_state (*init)();
  struct game_state (*update)(struct game_state);
  struct game_state (*event)(SDL_Event*, struct game_state);
  bool (*is_running)();
  struct game_state (*render)(struct game_state);
  void (*deinit)();
};

bool command_init(struct command *cmd);
bool command_load(struct command *cmd, const char *lib);
bool command_unload(struct command *cmd);

#endif
