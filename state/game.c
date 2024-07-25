#include "game.h"
#include "objects/base.h"
#include "ui/win.h"

#include "types/state_types.h"

bool game_init(struct game_state *gs) {
  gs->running = true;
  gs->paused = false;
  gs->current_level.loaded = false;
  return win_init(&gs->w, 640, 480);
}

bool game_render(struct game_state *gs) {
  if (gs->current_level.loaded) {
    for (int i = 0; i < gs->current_level.objects.len; ++i) {
      struct base *tmp = &gs->current_level.objects.object_data[i];
      if (!tmp->render(gs, tmp, gs->w.renderer)) {
        fprintf(stderr, "object failed to render\n");
      }
    }
  }
  return true;
}

bool game_copy(struct game_state*src, struct game_state*dest) {
  dest->w = src->w;
  dest->paused = src->paused;
  dest->running = src->running;
  level_copy(&src->current_level, &dest->current_level);
  return true;
}

void game_free(struct game_state *gs) {
  level_free(&gs->current_level);
  win_free(&gs->w);
}

bool level_init(struct level_state *lvl) {
  lvl->loaded = false;
  lvl->completed = false;
  if (!init_object_array(&lvl->objects, 1)) {
    fprintf(stderr, "level's object array failed to initialize\n");
    return false;
  }
  return true;
}

bool level_copy(struct level_state *src, struct level_state *dest) {
  dest->loaded = src->loaded;
  dest->completed = src->completed;
  for (int i = 0; i < src->objects.len; ++i) {
    struct base obj;
    struct base *orig = &src->objects.object_data[i];
    orig->copy(orig, &obj);
    insert_object_array(&dest->objects, obj);
  }
  return true;
}

int level_add_object(struct level_state *lvl, struct base b) {
  insert_object_array(&lvl->objects, b);
  return lvl->objects.len - 1;
}

void level_free(struct level_state *lvl) {
  if (lvl->objects.object_data != NULL) {
    free_object_array(&lvl->objects);
  }
}

