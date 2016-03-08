#ifndef FIELD_H
#define FIELD_H

#include <vector>

class Field {
    public:
        Field();
        virtual ~Field();
        int get_cell (int);
        const int WIDTH = 640;
        const int HEIGHT = 480;
        const int TILE_SIZE = 40;

    private:
        std::vector<int> grid;
};

#endif // FIELD_H
