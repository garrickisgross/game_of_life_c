#ifndef MAIN_H
#define MAIN_H


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

#endif // !MAIN_H

