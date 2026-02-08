#include "game.h"
#include "cells.h"
#include "event.h"
#include "draw.h"
#include <SDL3/SDL.h>


#define CELL_INDEX(r, c) ((r) * NUM_COLS + (c))

void gol(Cell* cells){
  for (int row = 0; row < NUM_ROWS; row++){
    for (int col = 0; col < NUM_COLS; col++){
      int index = CELL_INDEX(row, col);

      int alive = count_alive_neighbors(cells, row, col);
      /* int dead = 8 - alive; */
      
      bool toggle = false;
      if (cells[index].active){
        
        if (alive < 2 || alive > 3){
           toggle = true;
        }


      } else {
        
        if (alive == 3){
          toggle = true;
        }
      }

      if (toggle){
        cells[index].active = !cells[index].active;
        cells[index].color = cells[index].active ? ACTIVE_COLOR : INACTIVE_COLOR;
      }
    }
  }
}


void reset_game(Cell* cells){
  for (int row = 0; row < NUM_ROWS; row++){
    for (int col = 0; col < NUM_COLS; col++){
      int i = CELL_INDEX(row, col);
      cells[i].active = false;
      cells[i].color = INACTIVE_COLOR;
    }
  }
}

