#ifndef CELLS_H
#define CELLS_H
#include <stdbool.h>
#include <stdlib.h>

typedef struct Cell
{
  int x, y;
  int color;
  bool active;

} Cell;

Cell* init_cells();

int count_alive_neighbors(const Cell* cells, int row, int col);

#endif
