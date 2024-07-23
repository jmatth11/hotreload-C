#ifndef DRIVER_H
#define DRIVER_H

#include <SDL2/SDL_events.h>
#include <stdbool.h>

#include "types/state_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct game_state init();
struct game_state update(struct game_state);
struct game_state event(SDL_Event*, struct game_state);
bool is_running();
struct game_state render(struct game_state);
void deinit();

#ifdef __cplusplus
}
#endif

#endif
