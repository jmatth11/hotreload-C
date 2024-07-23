#ifndef SGF_PLAYER_H
#define SGF_PLAYER_H

#include <stdbool.h>

struct base;

bool player_new(struct base *);
bool player_copy(struct base *src, struct base *dest);
void player_free(struct base *);

#endif
