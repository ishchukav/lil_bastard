#include "spider.h"
#include <SDL2/SDL.h>


Spider::Spider() {
}


Spider::Spider(Field *f) {
    name = "Spider";
    texture = "img/spider.png";
    health = 100;
    min_damage = 2;
    max_damage = 5;
    field = f;
}


Spider::~Spider() {
    //dtor
}
