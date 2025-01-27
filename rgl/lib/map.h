#ifndef MAP_H
#define MAP_H
#include <stdbool.h>

struct Entity;

typedef struct Mapspace {
    int w;
    int h;
    int *floor_space;
    int *visibility;
  struct Entity **entities;
    int n_rooms;
    int *rooms_x;
    int *rooms_y;
    int num_enemies;
} Mapspace;


Mapspace *init_mapspace(void);
void destroy_mapspace(Mapspace *map);
int      init_rooms(Mapspace *map);
int xy2flat(int y, int x);
bool in_bounds(int x, int y);
void apply_cov(Mapspace *map, struct Entity *ent);
char *inspect_map(Mapspace *map, int x, int y);
bool is_walkable(Mapspace *map, int x, int y);
bool is_entity(Mapspace *map, int x, int y); 
struct Entity **spawn_enemies(Mapspace *map, int lvl);

#endif
