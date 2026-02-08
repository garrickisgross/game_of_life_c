#ifndef EVENT_H
#define EVENT_H
#include <stdbool.h>
#include <SDL3/SDL.h>

struct Cell;
/// Define the event stuff

void processMouseClick(SDL_Event* event, struct Cell* cells);

void processKeys(SDL_Event* event, struct Cell* cells, bool* running, bool* reset);


bool poll_event();

#endif
