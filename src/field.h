#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <string>

class Field {
    public:
        Field();
        virtual ~Field();
        int get_cell_val(int);
        int get_cell_val(int, int);
        int get_cell_x_pixel(int);
        int get_cell_y_pixel(int);
        int get_cells_amount();
        std::string get_tex_road();
        std::string get_tex_wall();
        const int WIDTH = 640;
        const int HEIGHT = 480;
        const int TILE_SIZE = 40;

    private:
        std::vector<int> grid;
        const std::string tex_wall = "img/wall.png";
        const std::string tex_road = "img/road.png";
};

#endif // FIELD_H
