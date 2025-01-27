#ifndef DISP_H
#define DISP_H
#include "map.h"
#include "player.h"

void display_map(Mapspace *map);
void init_ncurses(void);
void kill_ncurses(void);
void resresh_ncruses(void);
void display_entity(Entity *entity);
void display_entities(Entity **enemy_group, Mapspace *map);
void inspect_mode(Mapspace *map, int x, int y);

#endif
