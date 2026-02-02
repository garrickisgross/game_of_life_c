#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdlib.h>
#include <stdbool.h>


#define TITLE "Conway's Game of Life"
#define WIDTH 900
#define HEIGHT 600
#define CELL_SIZE 20
#define COLOR_WHITE 0xffffff
#define ACTIVE_COLOR 0x80c775
#define INACTIVE_COLOR 0x434543
#define CELL_EDGE_COLOR 0xedf2ed
#define NUM_ROWS HEIGHT/CELL_SIZE
#define NUM_COLS WIDTH/CELL_SIZE
#define WIN_PAD 250
#define CELL_INDEX(r, c) ((r) * NUM_COLS + (c))


typedef struct Cell {
  int x, y; 
  bool active;
  Uint32 color;
} Cell;

Cell* init_cells(){
  // Allocating an array of size Cell * Area of cells based on cell size. 
  Cell cell;
  int size = (NUM_COLS) * (NUM_ROWS);
  Cell* cells = (Cell*) malloc(sizeof(cell) * size);

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

void processMouseClick(SDL_Event* event, Cell* cells){
  int x = (int)event->button.x;
  int y = (int)event->button.y;

  int grid_x = x - (WIN_PAD/2);
  int grid_y = y - (WIN_PAD/2);

  if (grid_x < 0 || grid_x >= WIDTH || grid_y < 0 || grid_y >= HEIGHT) return;

  int col = grid_x / CELL_SIZE;
  int row = grid_y / CELL_SIZE;

  int index = row * NUM_COLS + col;

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

static const int NEIGHBORS[8][2] = {
  {-1, -1}, {-1, 0}, {-1, 1},
  { 0, -1},          { 0, 1},
  { 1, -1}, { 1, 0}, { 1, 1}
};

int count_alive_neighbors(Cell* cells, int row, int col){
  int count = 0;
  
  for (int n = 0; n < 8; n++){
    int nr = row + NEIGHBORS[n][0];
    int nc = col + NEIGHBORS[n][1];

    if (nr < 0 || nr > NUM_ROWS - 1 || nc < 0 || nc > NUM_COLS - 1) continue;

    if (cells[CELL_INDEX(nr, nc)].active) count++;
  }

  return count;
}

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

void reset_game(Cell* cells){

  for (int row = 0; row < NUM_ROWS; row++){
    for (int col = 0; col < NUM_COLS; col++){
      int i = CELL_INDEX(row, col);
      cells[i].active = false;
      cells[i].color = INACTIVE_COLOR;
    }
  }

}

int main(){
  bool init = SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window;
  bool done = false;
  if (init){
    window = SDL_CreateWindow(TITLE,WIDTH + WIN_PAD,HEIGHT + WIN_PAD,0);
    if (window == NULL) {
      SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
      return 1;
    }
  } else {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error Initializing SDL: %s\n", SDL_GetError());
    return 1;
  }
  
  Cell* cells = init_cells();
  bool running = false;
  bool reset = false; 
  // Main Loop
  while (!done) {
    SDL_Event event;


    while (SDL_PollEvent(&event)){
      
      if (event.type == SDL_EVENT_QUIT){
        done = true;
      }

      processKeys(&event, cells, &running, &reset);

    }
    
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
