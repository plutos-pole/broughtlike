#include "../lib/player.h"
#include "../lib/map.h"
#include "../lib/rand.h"
#include "../lib/shared.h"
#include <ncurses.h>
#include <stdlib.h>


Entity *init_player(Mapspace *map) {

    Entity *player = malloc(sizeof(*player));
    if (player == NULL) {
        fprintf(stderr, "Memory allocation failed for <player>\n");
        return NULL;
    }
    int rnd_room = randRange(0, map->n_rooms - 1);
    int offset_x = *(map->rooms_x + rnd_room) + MIN_ROOM_W / 2;
    int offset_y = *(map->rooms_y + rnd_room) + MIN_ROOM_H / 2;
    
    player->x = offset_x;
    player->y = offset_y;
    player->form = '@';
    player->cov = MIN_CONE_OF_VISION;
    return player; 

}

void move_player(Mapspace *map, Entity *player, const int n_x, const int n_y) {
    if (is_walkable(map, n_x, n_y)) {
        player->x = n_x;
        player->y = n_y;
    }
}
