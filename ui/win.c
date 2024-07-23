#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "types/win_types.h"
#include "win.h"

bool win_init(struct win *win, int w, int h) {
  if (SDL_CreateWindowAndRenderer(
      w, h, SDL_WINDOW_ALLOW_HIGHDPI, &win->window, &win->renderer
  ) != 0) {
    fprintf(stderr, "window creation error: %s\n", SDL_GetError());
    return false;
  }
  return true;
}

SDL_Rect win_cur_size(struct win *win) {
  int winw, winh;
  SDL_GetWindowSize(win->window, &winw, &winh);
  return (SDL_Rect){
    .x = 0,
    .y = 0,
    .w = winw,
    .h = winh,
  };
}

void win_free(struct win *win) {
  SDL_DestroyRenderer(win->renderer);
  SDL_DestroyWindow(win->window);
}
