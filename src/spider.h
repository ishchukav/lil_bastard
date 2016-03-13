#ifndef SPIDER_H
#define SPIDER_H

#include "character.h"
#include "field.h"


class Spider : public Character {
    public:
        Spider();
        virtual ~Spider();
        void set_rand_xy(Field &);
};

#endif // SPIDER_H
