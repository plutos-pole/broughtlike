#ifndef PLAYER_H
#define PLAYER_H
#include "map.h"
#include "entity.h"


void display_player(Entity *player);
Entity *init_player(Mapspace *map);
void destroy_player(Entity *player);
void move_player(Mapspace *map, Entity *player, const int n_x, const int n_y);


#endif
