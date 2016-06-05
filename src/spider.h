#ifndef SPIDER_H
#define SPIDER_H

#include "mob.h"
#include "field.h"


class Spider : public Mob {
    public:
        Spider();
        Spider(Field *);
        ~Spider();
};

#endif // SPIDER_H
