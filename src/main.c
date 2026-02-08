#include "game.h"
#include "cells.h"
#include "event.h"
#include "draw.h"
#include <SDL3/SDL.h>


int main(){
  bool done = false;
  SDL_Window* window = init_SDL(); 
  Cell* cells = init_cells();
  bool running = false;
  bool reset = false; 

  // Main Loop
  while(!done)
  {
    SDL_Event event;

    done = poll_event(&event, cells, &running, &reset);

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
