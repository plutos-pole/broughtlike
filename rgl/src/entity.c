#include <stdlib.h>
#include <stdio.h>
#include "../lib/entity.h"
#include "../lib/enemy.h"




Entity **create_entities(int lvl) {
    // TODO: lvl should decide on number of entities
    int num_of_entities = lvl;
    Entity **ents_array = malloc(sizeof(*ents_array) * num_of_entities);
    if (ents_array == NULL) {
        fprintf(stderr, "Memory allocation failed for <ents_array> __FILE__ __LINE__");
        free(ents_array);
    }
    for (int i = 0; i < num_of_entities; i++) {
        ents_array[i] = create_humanoid();
        if (ents_array[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(ents_array[j]);
            }
            free(ents_array);
            return NULL;
        }
    }
    return ents_array;
}
