#include "../lib/disp.h"
#include "../lib/map.h"
#include "../lib/shared.h"
#include "../lib/player.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdbool.h>

char floor_symb[] = {'.', '#', '.', '.'};

static char get_map_symb(Mapspace *map, int row, int col);
static bool is_visible_on(Mapspace *map, int row, int col);


char get_map_symb(Mapspace *map, int row, int col) {
    
    return floor_symb[*(map->floor_space + xy2flat(row, col))];
}

void display_map(Mapspace *map) {
    clear();
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            if (is_visible_on(map, row, col)) {
                mvprintw(row, col, "%c", get_map_symb(map, row, col));
            }    
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
    raw();
    noecho();
    keypad(stdscr, true);
    curs_set(0);
}

void kill_ncurses() {
    endwin();
}

bool is_visible_on(Mapspace *map, int row, int col) {
    return *(map->visibility + xy2flat(row, col)) == VISIBLE;
}
