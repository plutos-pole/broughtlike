#ifndef PLAYER_H
#define PLAYER_H
#include "map.h"


typedef struct Entity {
    int x;
    int y; 
    char form;
} Entity;

void display_player(Entity *player);
Entity *init_player(Mapspace *map);
void move_player(Mapspace *map, Entity *player, const int n_x, const int n_y);


#endif
