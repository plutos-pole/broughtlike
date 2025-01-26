#ifndef MAP_H
#define MAP_H
#include <stdbool.h>

struct Entity;

typedef struct Mapspace {
    int w;
    int h;
    int *floor_space;
    int *visibility;
    int n_rooms;
    int *rooms_x;
    int *rooms_y;
} Mapspace;


Mapspace *init_mapspace(void);
int      init_rooms(Mapspace *map);
int xy2flat(int y, int x);
bool is_walkable(Mapspace *map, int x, int y);
bool in_bounds(int x, int y);
void apply_cov(Mapspace *map, struct Entity *ent);
char *inspect_map(Mapspace *map, int x, int y);

#endif
