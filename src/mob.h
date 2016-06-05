#ifndef MOB_H
#define MOB_H

#include "character.h"
#include "field.h"
#include "random.h"


class Mob : public Character {
	public:
		Mob();
        Mob(Field *);
		virtual ~Mob();
        void set_rand_xy();
        void move();
    protected:
        unsigned move_time_old, move_time_curr, move_delay;
        Random random;
        Field *field;

};

#endif // MOB_H
