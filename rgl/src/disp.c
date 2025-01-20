#include "../lib/disp.h"
#include "../lib/map.h"
#include "../lib/shared.h"
#include <stdio.h>

char floor_symb[] = {'.', '#', '.', '.'};


static char get_map_symb(Mapspace *map, int row, int col) {
    
    return floor_symb[*(map->floor_space + xy2flat(row, col))];
}

void display_map(Mapspace *map) {

    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            printf("%c", get_map_symb(map, row, col));
        }
        printf("\n");
    }
}
