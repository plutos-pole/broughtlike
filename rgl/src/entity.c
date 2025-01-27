#include <stdlib.h>
#include "../lib/entity.h"
#include "../lib/enemy.h"




Entity **create_entities(int lvl) {
    // TODO: lvl should decide on number of entities
    int num_of_entities = lvl;
    Entity **ents_array = malloc(sizeof(*ents_array) * num_of_entities);

    for (int i = 0; i < num_of_entities; i++) {
        ents_array[i] = create_humanoid();
    }
    return ents_array;
}
