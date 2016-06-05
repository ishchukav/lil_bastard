#include "player.h"


Player::Player() {
    name = "Vasia";
    texture = "img/man.png";
    health = 100;
    min_damage = 7;
    max_damage = 12;
    pos_x = 0;
    pos_y = 0;
}


Player::~Player() {
    //dtor
}
