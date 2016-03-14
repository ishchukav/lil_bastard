#ifndef SPIDER_H
#define SPIDER_H

#include "character.h"
#include "field.h"


class Spider : public Character {
    public:
        Spider();
        Spider(Field *);
        virtual ~Spider();
        void set_rand_xy();
        void move();

    private:
        unsigned move_time_old, move_time_curr, move_delay;
};

#endif // SPIDER_H
