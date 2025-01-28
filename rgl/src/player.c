#include "../lib/player.h"
#include "../lib/map.h"
#include "../lib/rand.h"
#include "../lib/shared.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>


Entity *init_player(Mapspace *map) {

    Entity *player = malloc(sizeof(*player));
    if (player == NULL) {
        fprintf(stderr, "Memory allocation failed for <player>\n");
        return NULL;
    }

    player->description = malloc(sizeof(*player->description) * 50);

    if (player->description == NULL) {
        fprintf(stderr, "Memory allocation failed for <player_description>\n");
        return NULL;
    }

    int rnd_room = randRange(0, map->n_rooms - 1);
    int offset_x = *(map->rooms_x + rnd_room) + MIN_ROOM_W / 2;
    int offset_y = *(map->rooms_y + rnd_room) + MIN_ROOM_H / 2;
    
    player->x = offset_x;
    player->y = offset_y;

    player->health = 25;
    player->attack = 1;

    player->form = '@';
    player->cov = MIN_CONE_OF_VISION;
    strcpy(player->description, "That's actually you");
    map->entities[xy2flat(player->y, player->x)] = player;
    return player; 

}

void destroy_player(Entity *player) {
    // destroy_map should destroy all entities,
    // including the player. So there's no need to destroy it twice as
    // free(player)
    free(player->description);
}

void move_player(Mapspace *map, Entity *player, const int n_x, const int n_y) {
    if (is_entity(map, n_x, n_y)) {
    //TODO attack(); 
        return;
    }
    if (is_walkable(map, n_x, n_y)) {
    // Update entities matrix and the player itself
        map->entities[xy2flat(player->y, player->x)] = NULL;
        map->entities[xy2flat(n_y, n_x)] = player;
        player->x = n_x;
        player->y = n_y;
        
    }
}
