#ifndef ENTITY_H
#define ENTITY_H


typedef struct Entity {
    int x;
    int y; 
    int health;
    int attack;
    int cov;
    char form;
    char *description;
} Entity;

Entity **create_entities(int lvl);

#endif
