#ifndef SGF_GAME_STATE_H
#define SGF_GAME_STATE_H

#include <stdbool.h>

#include "objects/base.h"

struct game_state;
struct level_state;

bool game_init(struct game_state*);
bool game_render(struct game_state *);
bool game_copy(struct game_state*src, struct game_state*dest);
void game_free(struct game_state*);

bool level_init(struct level_state*);
int level_add_object(struct level_state *, struct base);
bool level_copy(struct level_state *src, struct level_state *dest);
void level_free(struct level_state*);

#endif
