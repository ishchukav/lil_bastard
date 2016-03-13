#include "spider.h"
#include <ctime>
#include <cstdlib>


Spider::Spider() {
    name = "Spider";
    texture = "img/spider.png";
    srand(time(NULL));
}


Spider::~Spider() {
    //dtor
}


void Spider::set_rand_xy(Field &field) {
    int cell = rand() % field.get_cells_amount();
    if (field.get_cell_val(cell) == 0) {
        pos_x = field.get_cell_x_pixel(cell);
        pos_y = field.get_cell_y_pixel(cell);
    } else {
        set_rand_xy(field);
    }
}

