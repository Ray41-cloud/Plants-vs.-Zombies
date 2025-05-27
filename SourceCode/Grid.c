// Grid.c
#include "Grid.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h> // ✅ 要搭配 al_init_primitives_addon()
#include "global.h"

// 格子狀態
bool can_place[GRID_ROWS][GRID_COLS];

void Grid_init() {
    for (int i = 0; i < GRID_ROWS; ++i)
        for (int j = 0; j < GRID_COLS; ++j)
            can_place[i][j] = false;

    // ✅ 複製貼上這段
    can_place[1][7] = true;
    can_place[2][7] = true;
    can_place[3][7] = true;
    can_place[4][6] = true;
    can_place[5][5] = true;
    can_place[6][4] = true;

    can_place[6][2] = true;
    can_place[7][2] = true;
    can_place[8][2] = true;

    can_place[9][2] = true;
    can_place[10][2] = true;

    can_place[10][3] = true;
    can_place[11][3] = true;
}


void Grid_draw() {
    for (int i = 0; i < GRID_ROWS; ++i) {
        for (int j = 0; j < GRID_COLS; ++j) {
            if (can_place[i][j]) {
                // ✅ 畫格子底（淡灰半透明）
                al_draw_filled_rectangle(
                    j * GRID_SIZE,
                    i * GRID_SIZE,
                    (j + 1) * GRID_SIZE,
                    (i + 1) * GRID_SIZE,
                    al_map_rgba(100, 100, 100, 15) // 非常淡的灰
                );

                // ✅ 畫格子邊框（黑色細線）
                al_draw_rectangle(
                    j * GRID_SIZE,
                    i * GRID_SIZE,
                    (j + 1) * GRID_SIZE,
                    (i + 1) * GRID_SIZE,
                    al_map_rgb(0, 0, 0),
                    1
                );
            }
        }
    }
}

bool Grid_is_placeable(int row, int col) {
    if (row < 0 || row >= GRID_ROWS || col < 0 || col >= GRID_COLS) return false;
    return can_place[row][col];
}

void Grid_set_unplaceable(int row, int col) {
    if (row >= 0 && row < GRID_ROWS && col >= 0 && col < GRID_COLS)
        can_place[row][col] = false;
}
