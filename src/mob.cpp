#include "mob.h"
#include "engine.h"
#include <SDL2/SDL.h>


Mob::Mob() {
    name = "Mob";
    texture = "img/mob.png";
    tile_size = 40;
    move_time_old = 0;
    move_delay = 1000;
}


Mob::Mob(Field *f) {
    field = f;
}


Mob::~Mob() {
    //dtor
}


void Mob::set_rand_xy() {
    bool success = false;
    while (!success) {
        int cell = random.gen_rand_int(0, field->get_cells_amount() - 1);
        if (field->get_cell_val(cell) == 0) {
            pos_x = field->get_cell_x_pixel(cell);
            pos_y = field->get_cell_y_pixel(cell);
            success = true;
        }
    }
}


void Mob::move() {
    move_time_curr = SDL_GetTicks();
    if (move_time_curr > move_time_old + move_delay) {
        bool success = false;
        enum direction {UP, DOWN, LEFT, RIGHT};
        int dir;
        while (!success) {
            dir = random.gen_rand_int(0, 9);
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
