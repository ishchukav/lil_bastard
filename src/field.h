#ifndef FIELD_H
#define FIELD_H


class Field {
    public:
        Field();
        virtual ~Field();
        const int WIDTH = 640;
        const int HEIGHT = 480;
        const int TILE_SIZE = 40;
};

#endif // FIELD_H
