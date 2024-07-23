#include <dlfcn.h>

#include "command.h"

bool command_init(struct command *cmd) {
  cmd->handler = NULL;
  cmd->init = NULL;
  cmd->render = NULL;
  cmd->event = NULL;
  cmd->update = NULL;
  cmd->is_running = NULL;
  cmd->deinit = NULL;
  return true;
}

bool command_load(struct command *cmd, const char *lib) {
  if (cmd->handler != NULL) {
    return true;
  }
  void *handle = dlopen(lib, RTLD_LAZY);
  if (handle == NULL) {
    fprintf(stderr, "could not load shared library\n");
    return false;
  }
  // these functions aren't necessary
  cmd->init = dlsym(handle, "init");
  if (cmd->init == NULL) {
    fprintf(stderr, "init failed\n");
    return false;
  }
  cmd->update = dlsym(handle, "update");
  if (cmd->update == NULL) {
    fprintf(stderr, "update failed\n");
    return false;
  }
  cmd->render = dlsym(handle, "render");
  if (cmd->render == NULL) {
    fprintf(stderr, "render failed\n");
    return false;
  }
  cmd->event = dlsym(handle, "event");
  if (cmd->event == NULL) {
    fprintf(stderr, "event failed\n");
    return false;
  }
  cmd->is_running = dlsym(handle, "is_running");
  if (cmd->is_running == NULL) {
    fprintf(stderr, "is_running failed\n");
    return false;
  }
  cmd->deinit = dlsym(handle, "deinit");
  if (cmd->deinit == NULL) {
    fprintf(stderr, "deinit failed\n");
    return false;
  }
  cmd->handler = handle;
  return true;
}

bool command_unload(struct command *cmd) {
  if (cmd->handler != NULL) {
    dlclose(cmd->handler);
  }
  command_init(cmd);
  return true;
}
