#ifndef DRAW_H
#define DRAW_H

struct SDL_Window;
struct SDL_Surface;
struct Cell;

struct SDL_Window* init_SDL();
void draw_cells(struct SDL_Surface* surface, struct Cell* cells);

#endif
