#ifndef CELLS_H
#define CELLS_H
#include <stdbool.h>
#include <stdlib.h>
#include <SDL3/SDL_main.h>
typedef struct Cell
{
  int x, y;
  bool active;
  Uint32 color;

} Cell;

Cell* init_cells();

int count_alive_neighbors(const Cell* cells, int row, int col);

#endif
