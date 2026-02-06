#include <stdio.h> 
#include <SDL3/SDL.h> 
#include <SDL3/SDL_main.h>
#include <stdlib.h>
#include <stdbool.h>


#include "./main.h"
#include "./draw.h"
#include "./event.h"
#include "./cells.h"


void gol(Cell* cells){
  for (int row = 0; row < NUM_ROWS; row++){
    for (int col = 0; col < NUM_COLS; col++){
      int index = CELL_INDEX(row, col);

      int alive = count_alive_neighbors(cells, row, col);
      int dead = 8 - alive;
      
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

int main(){
  bool done = false;
  SDL_Window window = init_SDL(); 
  Cell* cells = init_cells();
  bool running = false;
  bool reset = false; 
  // Main Loop
  while(!done)
  {
    done = poll_event()
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    if (running){
      gol(cells);
    }

    if (reset){
      reset_game(cells);
      running = false;
      reset = false;
    }
    
    // Draw cells
    draw_cells(surface, cells);

    // Update window
    SDL_UpdateWindowSurface(window);
   
    // Refresh rate.
    SDL_Delay(60);
  }
  
  //Cleanup
  free(cells);
  cells = NULL;
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
