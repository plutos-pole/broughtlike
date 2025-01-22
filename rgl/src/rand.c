#include <stdlib.h>
#include "../lib/rand.h"


int randRange(int low, int high) {
    if (low == high) {
        return low;
    }
    return (rand() % (high - low + 1) + low);
}
