#include "../lib/disp.h"
#include "../lib/map.h"
#include "../lib/shared.h"
#include "../lib/player.h"
#include <stdio.h>
#include <ncurses.h>

char floor_symb[] = {'.', '#', '.', '.'};

static char get_map_symb(Mapspace *map, int row, int col);


char get_map_symb(Mapspace *map, int row, int col) {
    
    return floor_symb[*(map->floor_space + xy2flat(row, col))];
}

void display_map(Mapspace *map) {
    clear();
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            mvprintw(row, col, "%c", get_map_symb(map, row, col));
        }
    }
    refresh();
}

void display_entity(Entity *entity) {
    int x = entity->x;
    int y = entity->y;
    char form = entity->form;

    mvprintw(y, x, "%c", form);

}

void init_ncurses() {
    initscr();
}

void kill_ncurses() {
    endwin();
}

