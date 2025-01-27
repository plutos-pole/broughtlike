#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../lib/enemy.h"
#include "../lib/shared.h"
#include "../lib/entity.h"


Entity *create_humanoid(void) {
    Entity *h = malloc(sizeof(*h));
    if (h == NULL) {
        fprintf(stderr, "Memory allocation failed for <humanoid>\n");
    }
    h->health = 5;
    h->attack = 1;
    h->description = malloc(sizeof(*h->description) * MAX_DESCRIPTION);
    h->description = strdup("Twisted human with malfunctioning tech, with wires and metall errupting from their flesh");
    //TODO: turn it into enums
    h->form = 'h';

    return h;
}

