//
// Created by Hans Fredrik Brastad on 04/11/15.
//

#ifndef INNLEVERING2_MAP_H
#define INNLEVERING2_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "array.h"

const int RESIZE_FACTOR;

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
int contains_key(Map *pMap, char key);
void add_int_on_key(Map *pMap, char key, int number);
int get_index_for_key(Map *pMap, char key);
void resize_map(Map *pMap);
void free_map_memory(Map *pMap);

#endif //INNLEVERING2_MAP_H
