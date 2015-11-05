//
// Created by Hans Fredrik Brastad on 04/11/15.
//

#ifndef INNLEVERING2_MAP_H
#define INNLEVERING2_MAP_H



#include <stdlib.h>
#include "../source/array.h"

const int RESIZE_FACTOR = 2;

typedef struct{
    char      key;
    Array     value;
}Item;


typedef struct{
    Item    *items;
    int     length;
    int     used;
}Map;


Map new_map(int size);
void put(Map *pMap, Item item);
int cointains_key(Map *pMap, char key);
void resize_map(Map *pMap);
void free_map_memory(Map *pMap);


Item new_item(int size);

#endif //INNLEVERING2_MAP_H
