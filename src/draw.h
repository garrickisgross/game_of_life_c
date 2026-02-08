#ifndef DRAW_H
#define DRAW_H
#include <SDL3/SDL.h>
#include "cells.h"

struct SDL_Window* init_SDL();
void draw_cells(SDL_Surface* surface, Cell* cells);

#endif
