#include "draw.h"
#include "game.h"
#include "cells.h"
#include <SDL3/SDL.h>
#include <stdlib.h>



SDL_Window* init_SDL()
{
   bool init = SDL_Init(SDL_INIT_VIDEO);
   if (init)
  {
     SDL_Window* window = SDL_CreateWindow(TITLE,WIDTH + WIN_PAD,HEIGHT + WIN_PAD,0);
     if (window == NULL) 
    {
      SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error initializing window: %s\n", SDL_GetError());
      exit(-1);
    }

     return window;
  }

  else 
  {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error Initializing SDL: %s\n", SDL_GetError());
    exit(-1);
  }
  
}



void draw_cells(SDL_Surface* surface, Cell* cells){

  for (int i = 0; i < NUM_ROWS * NUM_COLS; i++){
    SDL_Rect rect;
    rect.x = cells[i].x + WIN_PAD/2 + 1;
    rect.y = cells[i].y + WIN_PAD/2 + 1;
    rect.w = CELL_SIZE - 1;
    rect.h = CELL_SIZE - 1;
    
    SDL_Rect edge_rect;
    edge_rect.x = cells[i].x + WIN_PAD/2;
    edge_rect.y = cells[i].y + WIN_PAD/2;
    edge_rect.w = CELL_SIZE + 1;
    edge_rect.h = CELL_SIZE + 1;
    
    SDL_FillSurfaceRect(surface, &edge_rect, COLOR_WHITE);
    SDL_FillSurfaceRect(surface, &rect, cells[i].color);
  }

}


