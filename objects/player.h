#ifndef SGF_PLAYER_H
#define SGF_PLAYER_H

#include <stdbool.h>

// forward declare
struct base;

/**
 * Initialize.
 */
bool player_new(struct base *);
/**
 * Free player.
 */
void player_free(struct base *);

#endif
