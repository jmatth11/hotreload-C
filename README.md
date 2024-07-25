# Hot-Reloading in C

This is a simple project to demonstrate how you can have a hot-reloading project in C.

I structure my program around SDL2 with a "game" concept, but the general idea should be transferrable.

## Main Loop

The core portion of this project is located in `main.c` and `driver/command.[h|c]`.
Main does general setup of SDL2 internals and handling the main loop.
We load in our shared library and have a simple even handler for the 'r' key to hotreload. (This should be able to be implmented in different ways, we use this for simplicity.)

## Driver

The rest of our application is behind a "driver" file. Ours is located in `driver/driver.[h|c]`.
This is where we implement the expected functions defined in `driver/command.h` for our application.

We have a little setup at the beginning of most functions to handle if we are hotreloaded at any instance.
Technically with our setup it only needs to be in the `event` function (as this is the next function that is called after hotreloading) but with different setups it could be setup
to hotreload at any instance.

## Running this Project

Steps to running this project:
- Run `install_deps.sh` file.
- Run `make` to build the project.
- Run `./bin/hotreload` to run the executable.
- Make a change in `objects/player.c` in the render function.
- Run `make shared` to recompile the shared library.
- In the main application press the 'r' key to hot reload and your changes should show.

## Demo

The demo is slightly older before I cleaned up the project, so ignore the old executable name.

https://github.com/user-attachments/assets/0ad69384-b061-440d-ac01-609439396c96
