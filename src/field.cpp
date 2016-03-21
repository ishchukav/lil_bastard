#include "field.h"
#include <iostream>


Field::Field() {
    grid = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
            1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1,
            1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1,
            1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1,
            1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0,
            1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0,
            1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0,
            1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0,
            0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0,
            0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0};
}


Field::~Field() {
    //dtor
}


int Field::get_cell_val(int cell) {
    return grid[cell];
}


int Field::get_cell_val(int x_pos, int y_pos) {
    // tiles per line
    int row_size = WIDTH / TILE_SIZE;
    // target tile position in field array
    int tile_pos = (row_size * (y_pos / TILE_SIZE)) + x_pos / TILE_SIZE;
    // target
    return get_cell_val(tile_pos);
}


int Field::get_cell_x_pixel(int cell) {
    int row_size = WIDTH / TILE_SIZE;
    if (cell < 0) {
        std::cout << "Error: cell is < 0" << std::endl;
        return -1;
    } else if (cell >= row_size)
        return (cell % row_size) * TILE_SIZE;
    else
        return cell * TILE_SIZE;
}


int Field::get_cell_y_pixel(int cell) {
    int row_size = WIDTH / TILE_SIZE;
    if (cell < 0) {
        std::cout << "Error: cell is < 0" << std::endl;
        return -1;
    } else if (cell == row_size) {
        return TILE_SIZE;
    } else if (cell < TILE_SIZE) {
        return 0;
    } else {
        return (cell / row_size) * TILE_SIZE;
    }
}


int Field::get_cells_amount() {
    return (WIDTH / TILE_SIZE) * (HEIGHT / TILE_SIZE);
}


std::string Field::get_tex_road() {
    return tex_road;
}


std::string Field::get_tex_wall() {
    return tex_wall;
}
