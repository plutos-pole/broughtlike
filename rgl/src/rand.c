#include <stdlib.h>
#include "../lib/rand.h"


int randRange(int low, int high) {

    return (rand() % (high - low + 1) + low);
}
