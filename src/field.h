#ifndef FIELD_H
#define FIELD_H

#include <vector>

class Field {
    public:
        Field();
        virtual ~Field();
        int get_cell_val(int);
        int get_cell_x_pixel(int);
        int get_cell_y_pixel(int);
        int get_cells_amount();
        const int WIDTH = 640;
        const int HEIGHT = 480;
        const int TILE_SIZE = 40;

    private:
        std::vector<int> grid;
};

#endif // FIELD_H
