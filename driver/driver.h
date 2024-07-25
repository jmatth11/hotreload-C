#ifndef DRIVER_H
#define DRIVER_H

#include <SDL2/SDL_events.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void* init();
void update(void*);
void event(SDL_Event*, void*);
bool is_running(void*);
void render(void*);
void deinit(void*);

#ifdef __cplusplus
}
#endif

#endif
