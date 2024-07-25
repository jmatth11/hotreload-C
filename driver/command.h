#ifndef COMMAND_H
#define COMMAND_H

#include <SDL2/SDL_events.h>
#include <stdbool.h>

/**
 * Command interface.
 * This defines the expected functions in the loaded shared object to have
 * for normal operation. All functions are required.
 */
struct command {
  /**
   * The shared library handler.
   */
  void *handler;
  /**
   * Initialize shared library state and return the global state object
   * you want to persist.
   */
  void* (*init)();
  /**
   * Update function called right before render.
   */
  void (*update)(void*);
  /**
   * Event function called before update.
   * This sends the SDL_Event object to be handled.
   */
  void (*event)(SDL_Event*, void*);
  /**
   * Simple function to control the running state.
   */
  bool (*is_running)(void*);
  /**
   * Handle all rendering logic here.
   */
  void (*render)(void*);
  /**
   * At the very end, handle freeing and general tear down.
   */
  void (*deinit)(void*);
};

/**
 * Initialize the command interface.
 */
bool command_init(struct command *cmd);
/**
 * Load in the shared library into the given command interface.
 */
bool command_load(struct command *cmd, const char *lib);
/**
 * Unload the shared library from the given command interface.
 */
bool command_unload(struct command *cmd);

#endif
