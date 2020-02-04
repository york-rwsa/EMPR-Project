#include <lpc_types.h>

#include "grid.h"
#include "motors.h"
#include "serial.h"

static Grid_t grid = {GRID_MAX_X, GRID_MAX_Y, GRID_X_OFFSET, GRID_Y_OFFSET, 0, 0, 0};

void grid_home() {
    home_x();
    home_y();
    home_z();
    movex(grid.x_offset);
    movey(grid.y_offset);
    grid.x = 0;
    grid.y = 0;
    grid.z = 0;
}

void grid_move_to_point(uint16_t x, uint16_t y) {
    if (x > grid.max_x) {
        x = grid.max_x;
    }

    if (y > grid.max_y) {
        y = grid.max_y;
    }

    motor_move_blocking(x - grid.x, y - grid.y, 0);

    grid.x = x;
    grid.y = y;
}

void grid_x_steps(int steps) {
    if (movex(steps) != -1)
        grid.x += steps;
}

void grid_y_steps(int steps) {
    if (movey(steps) != -1)
        grid.y += steps;
}

void grid_z_steps(int steps) {
    if (movez(steps < 0 ? steps * 8 : steps) != -1)
        grid.z += steps;
}

uint32_t grid_get_x() {
    return grid.x;
}

uint32_t grid_get_y() {
    return grid.y;
}

uint32_t grid_get_z() {
    return grid.z;
}
