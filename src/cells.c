#include "cells.h"
#include "game.h"
#include <stdlib.h>

#define CELL_INDEX(r, c) ((r) * NUM_COLS + (c))

Cell* init_cells(){
  // Allocating an array of size Cell * Area of cells based on cell size. 
  Cell cell;
  int size = (NUM_COLS) * (NUM_ROWS);
  Cell* cells = (Cell*) malloc(sizeof(cell) * size);

  if (!cells){
    exit(-1);
  }



  // Loop through and create the cells.
  int i = 0;
  for (int row = 0; row < NUM_ROWS; row++) {
    for (int col = 0; col < NUM_COLS; col++) {
      int x = col * CELL_SIZE;
      int y = row * CELL_SIZE;
      cells[i] = (Cell) { x, y, false, INACTIVE_COLOR };
      i++;
    }
  } 

  return cells;
}

static const int NEIGHBORS[8][2] = {
  {-1, -1}, {-1, 0}, {-1, 1},
  { 0, -1},          { 0, 1},
  { 1, -1}, { 1, 0}, { 1, 1}
};

int count_alive_neighbors(const Cell* cells, int row, int col)
{
  int count = 0;
  
  for (int n = 0; n < 8; n++){
    int nr = row + NEIGHBORS[n][0];
    int nc = col + NEIGHBORS[n][1];

    if (nr < 0 || nr > NUM_ROWS - 1 || nc < 0 || nc > NUM_COLS - 1) continue;

    if (cells[CELL_INDEX(nr, nc)].active) count++;
  }

  return count;
}

