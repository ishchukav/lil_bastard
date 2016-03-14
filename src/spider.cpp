#include "spider.h"
#include <ctime>
#include <cstdlib>
#include <SDL.h>

Spider::Spider() {
}


Spider::Spider(Field *f) {
    name = "Spider";
    texture = "img/spider.png";
    srand(time(NULL));
    tile_size = 40;
    move_time_old = 0;
    move_delay = 1000;
    field = f;
}


Spider::~Spider() {
    //dtor
}


void Spider::set_rand_xy() {
    bool success = false;
    while (!success) {
        int cell = rand() % field->get_cells_amount();
        if (field->get_cell_val(cell) == 0) {
            pos_x = field->get_cell_x_pixel(cell);
            pos_y = field->get_cell_y_pixel(cell);
            success = true;
        }
    }
}


void Spider::move() {
    move_time_curr = SDL_GetTicks();
    if (move_time_curr > move_time_old + move_delay) {
        bool success = false;
        enum direction {UP, DOWN, LEFT, RIGHT};
        int dir;
        while (!success) {
            dir = rand() % 10;
            switch(dir) {
                case(UP):
                    if (field->get_cell_val(pos_x, pos_y - tile_size) == 0 && pos_y > 0) {
                        pos_y -= tile_size;
                        success = true;
                    }
                    break;
                case(DOWN):
                    if (field->get_cell_val(pos_x, pos_y + tile_size) == 0 && pos_y < field->HEIGHT - field->TILE_SIZE) {
                        pos_y += tile_size;
                        success = true;
                    }
                    break;
                case(LEFT):
                    if (field->get_cell_val(pos_x - tile_size, pos_y) == 0 && pos_x > 0) {
                        pos_x -= tile_size;
                        success = true;
                    }
                    break;
                case(RIGHT):
                    if (field->get_cell_val(pos_x + tile_size, pos_y) == 0 && pos_x < field->WIDTH - field->TILE_SIZE) {
                        pos_x += tile_size;
                        success = true;
                    }
                    break;
                default:
                    success = true;
                    break;
            }
        }
        move_time_old = move_time_curr;
    }
}
