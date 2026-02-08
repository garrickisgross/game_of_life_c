#include "event.h"
#include "game.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "cells.h"
#include <stdio.h>


#define CELL_INDEX(r, c) ((r) * NUM_COLS + (c))

void processMouseClick(SDL_Event* event, Cell* cells){
  int x = (int)event->button.x;
  int y = (int)event->button.y;


  int grid_x = x - (WIN_PAD/2);
  int grid_y = y - (WIN_PAD/2);


  if (grid_x < 0 || grid_x >= WIDTH || grid_y < 0 || grid_y >= HEIGHT) return;

  int col = grid_x / CELL_SIZE;
  int row = grid_y / CELL_SIZE;


  int index = CELL_INDEX(row, col);

  cells[index].active = !cells[index].active;
  cells[index].color = cells[index].active ? ACTIVE_COLOR : INACTIVE_COLOR;
  
}

void processKeys(SDL_Event* event, Cell* cells, bool* running, bool* reset){

  if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) processMouseClick(event,cells);

  if (event->type == SDL_EVENT_KEY_UP){
    SDL_Keycode key = event->key.key;

    if (key == SDLK_SPACE){
      *running = !(*running);
    }

    if (key == SDLK_RETURN){
      *reset = !(*reset);

    }
  }
}

// returns true if need to quit 
bool poll_event(SDL_Event* event, Cell* cells, bool* running, bool* reset) { 
  while (SDL_PollEvent(event))
  {
      
    if (event->type == SDL_EVENT_QUIT)
    {
      return true;
    }
      processKeys(event, cells, running, reset);
  }
  return false;
}

