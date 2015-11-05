//
// Created by Hans Fredrik Brastad on 04/11/15.
//

#include <stdio.h>
#include "../headers/map.h"


Map new_map(int size){
    Map map;
    map.items = malloc(size * sizeof(Item));
    map.used = 0;
    map.length = size;
    return  map;
}

void put(Map *pMap, Item item){
    if (pMap->used == pMap->length) {
        resize_map(pMap);
    }
    pMap->items[pMap->used] = item;
    pMap->used++;
}

void resize_map(Map *pMap){
    pMap->length *= RESIZE_FACTOR ;
    pMap->items = realloc(pMap->items, pMap->length * sizeof(Item));

    if(pMap->items == NULL){
        printf("\nProgram couldn't reallocate more memory, freeing memory and exiting!\n");
        free_map_memory(pMap);
        exit(0);
    }
}


void free_map_memory(Map *pMap){
    for(int i = 0; i < pMap->used; i++){
        free(pMap->items[i].value);
        pMap->items[i].value = NULL;
        pMap->items[i].value_length = 0;
        pMap->items[i].value_used = 0;
    }

    free(pMap->items);
    pMap->items= NULL;
    pMap->length = 0;
    pMap->used = 0;
}
