// Grid.h
#ifndef GRID_H
#define GRID_H

#include <stdbool.h>
#include "global.h"  // 確保 WIDTH / HEIGHT 可用

#define GRID_SIZE 48
#define GRID_ROWS (HEIGHT / GRID_SIZE)
#define GRID_COLS (WIDTH / GRID_SIZE)

// 儲存哪些格子可以放塔
extern bool can_place[GRID_ROWS][GRID_COLS];

void Grid_init();
void Grid_draw();
bool Grid_is_placeable(int grid_row, int grid_col);
void Grid_set_unplaceable(int grid_row, int grid_col);

#endif
