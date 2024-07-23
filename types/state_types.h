#ifndef SGF_STATE_TYPES_H
#define SGF_STATE_TYPES_H

#include <stdbool.h>
#include "objects/base.h"
#include "win_types.h"

#include "deps/array_template/array_template.h"

generate_array_template(object, struct base)

struct level_state {
  bool completed;
  bool loaded;
  object_array objects;
};

struct game_state {
  bool running;
  bool paused;
  struct win w;
  struct level_state current_level;
};

#endif
