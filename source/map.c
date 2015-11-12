//
// Created by Hans Fredrik Brastad on 04/11/15.
//

#include "../headers/map.h"

const int RESIZE_FACTOR = 2;

Map new_map(int size, int *mallocError){
    Map map;
    map.items = malloc(size * sizeof(Item));
    if(map.items == NULL) *mallocError = 1;

    map.used = 0;
    map.length = size;
    return  map;
}

void put(Map *pMap, Item item, int *mallocError){
    if (pMap->used == pMap->length) {
        resize_map(pMap, mallocError);
    }
    pMap->items[pMap->used] = item;
    pMap->used++;
}


int get_index_for_key(Map *pMap, char key){
    for(int i = 0; i < pMap->used; i++){
        if(pMap->items[i].key == key){
            return  i;
        }
    }
    return -1;
}


void add_int_on_key(Map *pMap, char key, int number, int *mallocError){
    for(int i = 0; i < pMap->used; i++){
        if(pMap->items[i].key == key){
            add_int(&pMap->items[i].value, number, mallocError);
        }
    }
}

void resize_map(Map *pMap, int *mallocError){
    pMap->length *= RESIZE_FACTOR ;
    pMap->items = realloc(pMap->items, pMap->length * sizeof(Item));

    if(pMap->items == NULL){
        *mallocError = 1;
        free_map_memory(pMap);
    }
}


void free_map_memory(Map *pMap){
    for(int i = 0; i < pMap->used; i++){
        free_array_memory(&pMap->items[i].value);
    }

    free(pMap->items);
    pMap->items= NULL;
    pMap->length = 0;
    pMap->used = 0;
}