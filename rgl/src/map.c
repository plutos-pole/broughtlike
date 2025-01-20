#include "../lib/map.h"
#include "../lib/shared.h"
#include "../lib/rand.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



int xy2flat(int row, int col) {
    
    return row * WIDTH + col;

}

static void fill_map(Mapspace *map) {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        map->floor_space[i] = FLOOR_WALL; 
    }
}
static bool check_rooms_bounds(Mapspace *map, int x, int y) {

    return true;
}

static void carve_rooms(Mapspace *map) {
    int n_rooms = map->n_rooms;
    int pos_x, pos_y;
    for (int i = 0; i < n_rooms; i++) {
        pos_x = *(map->rooms_x + i);
        pos_y = *(map->rooms_y + i);
        printf("pos-x: %d, pos-y: %d",pos_x, pos_y);
        *(map->floor_space + xy2flat(pos_y, pos_x)) = FLOOR_ROOM;
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

int init_rooms(Mapspace *map, int n_rooms) {
    map->n_rooms = n_rooms;
    
    map->rooms_x = malloc(sizeof(*map->rooms_x) * n_rooms); 
    map->rooms_y = malloc(sizeof(*map->rooms_y) * n_rooms); 
    if (map->rooms_x == NULL || map->rooms_y == NULL) {
        fprintf(stderr, "Memory allocation failed for <map->rooms[x|y]>\n");
        return 1;
    }

    for (int i = 0; i < n_rooms; i++) {
        int pos_x, pos_y;
        do {
            pos_x = randRange(MIN_ROOM_W, WIDTH - MAX_ROOM_W);
            pos_y = randRange(MAX_ROOM_H, HEIGHT - MAX_ROOM_H);
        } while (check_rooms_bounds(map, pos_x, pos_y) != true);
        *(map->rooms_x + i) = pos_x;
        *(map->rooms_y + i) = pos_y;
    } 
    carve_rooms(map);
    return 0;
}
