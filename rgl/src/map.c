#include "../lib/map.h"
#include "../lib/shared.h"
#include "../lib/rand.h"
#include "../lib/player.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "ncurses.h"




static int check_distance(int x1, int y1, int x2, int y2);
static void place_rooms(Mapspace *map);
static void fill_map(Mapspace *map);
static void carve_rooms(Mapspace *map, int width, int height, int pos_x, int pos_y);
static void carve_path(Mapspace *map, int x, int y);
static void bsp_partition(Mapspace *map, int l_w, int h_w, int l_h, int h_h, int *n_rooms, int deep, int dir);
static void make_path(Mapspace *map, int x1, int y1, int x2, int y2);
static void reveal_tiles(Mapspace *map, int cx, int cy, int max_cov);

enum DIR {NORTH, EAST, SOUTH, WEST};


void connect_rooms(Mapspace *map);

Mapspace *init_mapspace(void) {
    Mapspace *map = malloc(sizeof(*map));

    if (map == NULL) {
        fprintf(stderr, "Memory allocation failed for <map>\n");
    }

    map->w = WIDTH;
    map->h = HEIGHT;

    map->floor_space = malloc(sizeof(*map->floor_space) *  WIDTH * HEIGHT);

    if (map->floor_space == NULL) {
        fprintf(stderr, "Memory allocation failed for <floor_space>\n");
    }

    map->visibility = malloc(sizeof(*map->visibility) * WIDTH * HEIGHT);

    if (map->visibility == NULL) {
        fprintf(stderr, "Memory allocation failed for <map_visibility>\n");
    }

    // Entities matrix
    
    map->entities = malloc(sizeof(*map->entities) * WIDTH * HEIGHT);

    if (map->entities == NULL) {
        fprintf(stderr, "Memory allocation failed for <map_entities>\n");
    }
    // FIXME:
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        map->entities[i] = NULL;
    }

    map->n_rooms = 0;
    map->rooms_x = NULL;
    map->rooms_y = NULL;
    
    fill_map(map);

    return map;
}

void destroy_mapspace(Mapspace *map) {

    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        if (*(map->entities + i) != NULL) {
           free(*(map->entities + i));
        }
    }
    free(map->visibility);
    free(map->floor_space);
    free(map->rooms_x);
    free(map->rooms_y);
    free(map);
}

int init_rooms(Mapspace *map) {
    map->n_rooms = MAX_ROOMS;
    
    map->rooms_x = malloc(sizeof(*map->rooms_x) * MAX_ROOMS); 
    map->rooms_y = malloc(sizeof(*map->rooms_y) * MAX_ROOMS); 
    if (map->rooms_x == NULL || map->rooms_y == NULL) {
        fprintf(stderr, "Memory allocation failed for <map->rooms[x|y]>\n");
        return 1;
    }

    int curr_rooms = 0;
    bsp_partition(map, 0, WIDTH, 0, HEIGHT, &curr_rooms, 0, 0);
    place_rooms(map);
    connect_rooms(map);
    return 0;
}

int check_distance(int x1, int y1, int x2, int y2) {

   int dx = x1 - x2;
   int dy = y1 - y2;

   return dx * dx + dy * dy; 

}
void fill_map(Mapspace *map) {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        map->visibility[i] = INVISIBLE;
        map->floor_space[i] = FLOOR_WALL; 
    }
}


int xy2flat(int row, int col) {
    return row * WIDTH + col;
}

void place_rooms(Mapspace *map) {
    int n_rooms = map->n_rooms;
    int pos_x, pos_y;
    for (int i = 0; i < n_rooms; i++) {
        pos_x = *(map->rooms_x + i);
        pos_y = *(map->rooms_y + i);
        *(map->floor_space + xy2flat(pos_y, pos_x)) = FLOOR_ROOM;
    }
}


/* BSP algo */

void bsp_partition(Mapspace *map, int l_w, int h_w, int l_h, int h_h, int *n_rooms, int deep, int dir) {
    // Partition the screen untill there is 2^3 slices or the slice is 1/4 of
    // the screen
    if (h_w - l_w <= WIDTH / 4 ||  h_h - l_h <= HEIGHT / 4 || deep == 3) {
        int rand_width = randRange(MIN_ROOM_W, MAX_ROOM_W);
        int rand_height = randRange(MIN_ROOM_H, MAX_ROOM_H);
        int min_pos_w = l_w + 1;
        int max_pos_w = h_w - rand_width - 1;
        int min_pos_h = l_h + 1;
        int max_pos_h = h_h - rand_height - 1;
        // Ensures that there is a space from the left border to the right
        // border with account to random width and the size of the current slice
        // The margin from borders is set to 1 char. This ensures that we are
        // not on the edge of the map as well as not on the edge of the slice,
        // to remove possibility of overlapping rooms
        if (max_pos_w < min_pos_w || max_pos_h < min_pos_h) {
            return;
        }
        int pos_x = randRange(min_pos_w, max_pos_w);
        int pos_y = randRange(min_pos_h, max_pos_h);
        *(map->rooms_x + *n_rooms) = pos_x;
        *(map->rooms_y + *n_rooms) = pos_y;
        *n_rooms += 1;
        carve_rooms(map, rand_width, rand_height, pos_x, pos_y);
        return;

    }
    // Alternate between Horizontal slicing and Vertical slicing
    if (dir == 0) {
        int w_bound = ((l_w + h_w) / 2);
        bsp_partition(map, l_w, w_bound, l_h, h_h, n_rooms, deep + 1, dir^1);
        bsp_partition(map, w_bound, h_w, l_h, h_h, n_rooms, deep + 1, dir^1);
    } else {
        int h_bound = (l_h + h_h) / 2;
        bsp_partition(map, l_w, h_w, l_h, h_bound, n_rooms, deep + 1, dir^1);
        bsp_partition(map, l_w, h_w, h_bound, h_h, n_rooms, deep + 1, dir^1);
     }
}
void carve_rooms(Mapspace *map, int width, int height, int pos_x, int pos_y) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int converted_pos = xy2flat(pos_y + i, pos_x + j);
                *(map->floor_space + converted_pos) = FLOOR_ROOM;
                
            }
        }
}

void carve_path(Mapspace *map, int x, int y) {
    int converted_pos = xy2flat(y, x);
    *(map->floor_space + converted_pos) = FLOOR_PATH;
}


void make_path(Mapspace *map, int x1, int y1, int x2, int y2) {
        int curr_distance = check_distance(x1, y1, x2, y2);
        while (curr_distance != 0) {
            // NORTH -> EAST -> SOUTH -> WEST
            int dir = randRange(0, 3);
            switch(dir) {
                case NORTH:
                        if (check_distance(x1, y1 - 1, x2, y2) < curr_distance) {
                            y1 -= 1;
                         }
                            break;
                case EAST:
                        if (check_distance(x1 + 1, y1, x2, y2) < curr_distance) {
                            x1 += 1;
                         }
                            break;
                case SOUTH:
                        if (check_distance(x1, y1 + 1, x2, y2) < curr_distance) {
                            y1 += 1;
                         }
                            break;
                case WEST:
                         if (check_distance(x1 - 1, y1, x2, y2) < curr_distance) {
                            x1 -= 1;
                          }
                            break;
            }
            carve_path(map, x1, y1); 
            curr_distance = check_distance(x1, y1, x2, y2);
        }
}

void connect_rooms(Mapspace *map) {
    int n_rooms = map->n_rooms;
    int min_x_mid = MIN_ROOM_W / 2;
    int min_y_mid = MIN_ROOM_H / 2;

    for (int i = 0; i < n_rooms; i++) {
        int pos_x1, pos_y1, pos_x2, pos_y2;
        pos_x1 = *(map->rooms_x + i);
        pos_y1 = *(map->rooms_y + i);
        pos_x2 = *(map->rooms_x + ((i + 1) % n_rooms));
        pos_y2 = *(map->rooms_y + ((i + 1) % n_rooms));

        int adj_x1 = pos_x1 + min_x_mid;
        int adj_y1 = pos_y1 + min_y_mid;
        int adj_x2 = pos_x2 + min_x_mid;
        int adj_y2 = pos_y2 + min_y_mid;
        
        make_path(map, adj_x1, adj_y1, adj_x2, adj_y2);
    }
}

bool is_walkable(Mapspace *map, int x, int y) {
    return *(map->floor_space + xy2flat(y, x)) != FLOOR_WALL;
}


void reveal_tiles(Mapspace *map, int cx, int cy, int max_cov) {
    // Out of the map
    if (cx < 0 || cx >= WIDTH || cy < 0 || cy >= HEIGHT || max_cov < 0) {
        return;
    }
    // If it's a wall, then we want to bounce, mark it and return  
    if (is_walkable(map, cx, cy) == false) {
        *(map->visibility + xy2flat(cy, cx)) = VISIBLE;
        return;
    }
    // If it's a path, then simply mark it
    if (is_walkable(map, cx, cy)) {
        *(map->visibility + xy2flat(cy, cx)) = VISIBLE;
    }
    // 8-way DFS
    reveal_tiles(map, cx, cy - 1, max_cov - 1);
    reveal_tiles(map, cx + 1, cy, max_cov - 1);
    reveal_tiles(map, cx, cy + 1, max_cov - 1);
    reveal_tiles(map, cx - 1, cy, max_cov - 1);
    reveal_tiles(map, cx - 1, cy - 1, max_cov - 1);
    reveal_tiles(map, cx + 1, cy + 1, max_cov - 1);
    reveal_tiles(map, cx - 1, cy + 1, max_cov - 1);
    reveal_tiles(map, cx + 1, cy - 1, max_cov - 1);
}

void apply_cov(Mapspace *map, Entity *ent) {
    int cov = ent->cov;
    int x = ent->x;
    int y = ent->y;
    reveal_tiles(map, x, y, cov);
}

bool in_bounds(int x, int y) {
    return (x > 0 && x < WIDTH && y > 0 && y < HEIGHT);
}

bool is_entity(Mapspace *map, int x, int y) {
    return map->entities[xy2flat(y, x)] != NULL;
}

char *inspect_map(Mapspace *map, int x, int y) {
    if (*(map->visibility + xy2flat(y, x)) == INVISIBLE) {
        return "Nothingness...for now";
    }
    // TODO: check for Entities
    // TODO: check for Items
    // TODO: check for player
    //int pos = xy2flat(y, x);
    if (map->entities[xy2flat(y, x)] != NULL) {
        return map->entities[xy2flat(y, x)]->description;
    }
    //info = map->entities[pos]->description;
    // TODO: check for decoration
    return "Not sure yet";
}
