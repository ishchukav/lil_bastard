#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "random.h"

class Character {
    public:
        Character();
        virtual ~Character();
        std::string get_texture();
        std::string get_name();
        int get_x();
        int get_y();
        int get_health();
        void set_x(int);
        void set_y(int);
        void set_tile_size(int);
        void set_health(int);
        void print_location();
        void attack(Character *);

    protected:
        std::string name;
        std::string texture;
        int health;
        int min_damage;
        int max_damage;
        int damage;
        int pos_x;
        int pos_y;
        int tile_size;
        Random random;
        void set_min_damage(int);
        void set_max_damage(int);
        void set_damage(int);
};

#endif // CHARACTER_H
