#include "random.h"
#include <ctime>
#include <cstdlib>


Random::Random() {}

Random::~Random() {}

int Random::gen_rand_int(int min, int max) {
    static bool flag;
    if (!flag) {
        srand(time(NULL));
        flag = true;
    }
    return min + rand() % (max - min);
}
