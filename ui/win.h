#ifndef SGF_WIN_H
#define SGF_WIN_H

#include <SDL2/SDL_rect.h>
#include <stdbool.h>

// forward declare
struct win;

bool win_init(struct win*, int w, int h);
SDL_Rect win_cur_size(struct win*);
void win_free(struct win*);

#endif
