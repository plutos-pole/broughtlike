#ifndef MAP_H
#define MAP_H
#include <stdbool.h>


typedef struct mapspace {
    int w;
    int h;
    int *floor_space;
    int n_rooms;
    int *rooms_x;
    int *rooms_y;
} Mapspace;


Mapspace *init_mapspace(void);
int      init_rooms(Mapspace *map);
int xy2flat(int y, int x);
bool is_walkable(Mapspace *map, int x, int y);

#endif
