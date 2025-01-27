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
static void clear_section(int x, int y);

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

void display_entities(Entity **entities, Mapspace *map) {
    int ent_x, ent_y;
    for (int i = 0; i < map->num_enemies; i++) {

        ent_x = entities[i]->x;
        ent_y = entities[i]->y;

        if (*(map->visibility + xy2flat(ent_y, ent_x)) == VISIBLE) {

             display_entity(entities[i]);
        }
    }
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

void inspect_mode(Mapspace *map, int x, int y) {
    char ch;
    move(y, x);
    curs_set(1);
    
    while ((ch = getch()) != 'q') {
        // Clearing the message part
         clear_section(10, 30);
         move(y, x);

        switch(ch) {
            
            case 'w':
            case 'W':
                      if (in_bounds(x, y - 1)) { 
                        y -= 1;
                        move(y, x);
                      }
                        break;
            case 'd':
            case 'D':
                      if (in_bounds(x + 1, y)) { 
                        x += 1;
                        move(y, x);
                      }
                        break;
            case 's':
            case 'S':
                      if (in_bounds(x, y + 1)) { 
                        y += 1;
                        move(y, x);
                      }
                        break;
            case 'a':
            case 'A':
                      if (in_bounds(x - 1, y)) { 
                        x -= 1;
                        move(y, x);
                      }
                        break;
            case 'i': { 
                         move(30, 10);
                         printw("%s", inspect_map(map, x, y));
                         move(y, x); 
                         break;
                      } 
         }
         refresh();
    }
    curs_set(0);

}

void clear_section(int x, int y) {
    // Message box area
    move(y, x);
    clrtoeol();
}
