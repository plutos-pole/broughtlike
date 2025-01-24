#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include "../lib/map.h"
#include "../lib/rand.h"
#include "../lib/disp.h"
#include "../lib/player.h"

#include <ncurses.h>

int main (void) {
    srand(time(NULL));

    Mapspace *map = init_mapspace(); 

    if (map == NULL || map->floor_space == NULL) {
        return 1;
    }
    int failed  = init_rooms(map);
    if (failed) {
        return 1;
    }

    Entity *player = init_player(map);
    if (player == NULL) {
        return 1;
    }


    init_ncurses();
    
    int ch;
    
    while (1) {
        display_map(map);
        display_entity(player);
        ch = getch();
        if (ch == 'q') break;

        switch(ch) {
            case 'w':
            case 'W':
                    move_player(map, player, player->x, player->y - 1);
                    break;
            case 'd':
            case 'D':
                    move_player(map, player, player->x + 1, player->y);
                    break;
            case 's':
            case 'S':
                    move_player(map, player, player->x, player->y + 1);
                    break;
            case 'a':
            case 'A':
                    move_player(map, player, player->x - 1, player->y);
                    break;

       } 
    }
    kill_ncurses();
}
