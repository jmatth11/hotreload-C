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
  void *handle = dlopen(lib, RTLD_NOW);
  if (handle == NULL) {
    fprintf(stderr, "dlopen error: \"%s\"\n", dlerror());
    return false;
  }
  // these functions are necessary
  cmd->init = dlsym(handle, "init");
  if (cmd->init == NULL) {
    fprintf(stderr, "init failed: %s\n", dlerror());
    return false;
  }
  cmd->update = dlsym(handle, "update");
  if (cmd->update == NULL) {
    fprintf(stderr, "update failed %s\n", dlerror());
    return false;
  }
  cmd->render = dlsym(handle, "render");
  if (cmd->render == NULL) {
    fprintf(stderr, "render failed %s\n", dlerror());
    return false;
  }
  cmd->event = dlsym(handle, "event");
  if (cmd->event == NULL) {
    fprintf(stderr, "event failed %s\n", dlerror());
    return false;
  }
  cmd->is_running = dlsym(handle, "is_running");
  if (cmd->is_running == NULL) {
    fprintf(stderr, "is_running failed %s\n", dlerror());
    return false;
  }
  cmd->deinit = dlsym(handle, "deinit");
  if (cmd->deinit == NULL) {
    fprintf(stderr, "deinit failed %s\n", dlerror());
    return false;
  }
  cmd->handler = handle;
  return true;
}

bool command_unload(struct command *cmd) {
  if (cmd->handler != NULL) {
    if (dlclose(cmd->handler) != 0) {
      fprintf(stderr, "could not close shared library. %s\n", dlerror());
      return false;
    }
  }
  return command_init(cmd);
}
