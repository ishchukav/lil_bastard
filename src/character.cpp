#include "character.h"
#include <iostream>


Character::Character() {
    name = "Charname";
    texture = "img/man.png";
    health = 0;
    min_damage = 0;
    max_damage = 0;
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


int Character::get_health() {
    return health;
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


void Character::set_health(int h) {
    health = h;
}


void Character::print_location() {
    std::cout << name << " location is: [x=" << pos_x << ", y=" << pos_y << "]" << std::endl;
}


void Character::set_min_damage(int dmg) {
    min_damage = dmg;
}


void Character::set_max_damage(int dmg) {
    max_damage = dmg;
}


void Character::set_damage(int dmg) {
    if (dmg < min_damage || dmg > max_damage) {
        std::cout << "Damage value is out of available range!\n";
    } else {
        damage = dmg;
    }
}


void Character::attack(Character *enemy) {
    set_damage(random.gen_rand_int(min_damage, max_damage));
    enemy->set_health(enemy->get_health() - damage);
    std::cout << this->get_name() << " attacks " << enemy->get_name()
        << " by " << damage << " points.\n"
        << enemy->get_name() << " health is " << enemy->get_health() << std::endl;
}
