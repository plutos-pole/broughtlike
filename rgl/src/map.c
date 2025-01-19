#include "../lib/map.h"
#include "../lib/shared.h"
#include <stdio.h>
#include <stdlib.h>



static void fill_map(Mapspace *map) {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        map->floor_space[i] = FLOOR_WALL; 
    }
}

Mapspace *init_mapspace(void) {
    Mapspace *map = malloc(sizeof(*map));

    if (map == NULL) {
        fprintf(stderr, "Memory allocation failed for <map>\n");
    }

    map->w = WIDTH;
    map->h = HEIGHT;

    map->floor_space = malloc(sizeof(*map->floor_space) *  WIDTH * HEIGHT);

    if (map->floor_space == NULL) {
        fprintf(stderr, "Memory allocation failed for <floor_space>\n");
    }

    map->n_rooms = 0;
    map->rooms_x = NULL;
    map->rooms_y = NULL;
    
    fill_map(map);

    return map;
}

