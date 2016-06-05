#include "character.h"
#include <iostream>


Character::Character() {
    name = "Charname";
    texture = "img/man.png";
    pos_x = 0;
    pos_y = 0;
    tile_size = 0;
}


Character::~Character() {
}


std::string Character::get_texture() {
    return texture;
}


std::string Character::get_name() {
    return name;
}


int Character::get_x() {
    return pos_x;
}


int Character::get_y() {
    return pos_y;
}


void Character::set_x(int x) {
    pos_x = x;
}


void Character::set_y(int y) {
    pos_y = y;
}


void Character::set_tile_size(int t_size) {
    tile_size = t_size;
}


void Character::print_location() {
    std::cout << name << " location is: [x=" << pos_x << ", y=" << pos_y << "]" << std::endl;
}
