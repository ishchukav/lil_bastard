#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character {
    public:
        Character();
        virtual ~Character();
        std::string get_texture();
        std::string get_name();
        int get_x();
        int get_y();
        void set_x(int);
        void set_y(int);
        void set_tile_size(int);
        void print_location();

    protected:
        std::string name;
        std::string texture;
        int pos_x;
        int pos_y;
        int tile_size;
};

#endif // CHARACTER_H
