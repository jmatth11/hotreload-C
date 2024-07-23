#include "base.h"

bool base_copy(struct base *src, struct base *dest) {
  dest->color = src->color;
  dest->frame = src->frame;
  dest->mask_type = src->mask_type;
  dest->collision = src->collision;
  dest->collision_mask = src->collision_mask;
  return true;
}
