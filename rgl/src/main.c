#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include "../lib/map.h"
#include "../lib/rand.h"
#include "../lib/disp.h"

int main (void) {
    srand(time(NULL));

    Mapspace *map = init_mapspace(); 

    if (map == NULL || map->floor_space == NULL) {
        return 1;
    }

    int failed  = init_rooms(map, 6);
    if (failed) {
        return 1;
    }

    display_map(map);
}
