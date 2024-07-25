#ifndef SGF_WIN_H
#define SGF_WIN_H

#include <SDL2/SDL_rect.h>
#include <stdbool.h>

// forward declare
struct win;

/**
 * Initialize window with given size.
 */
bool win_init(struct win*, int w, int h);
/**
 * Get the current size of the window.
 */
SDL_Rect win_cur_size(struct win*);
/**
 * Free the window.
 */
void win_free(struct win*);

#endif
