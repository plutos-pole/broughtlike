#ifndef DISP_H
#define DISP_H
#include "map.h"
#include "player.h"

void display_map(Mapspace *map);
void init_ncurses(void);
void kill_ncurses(void);
void resresh_ncruses(void);
void display_entity(Entity *entity);

#endif
