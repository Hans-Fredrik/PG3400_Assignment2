//
// Created by Hans Fredrik Brastad on 04/11/15.
//

#include "../headers/map.h"

const int RESIZE_FACTOR = 2;

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

int contains_key(Map *pMap, char key){
    for(int i = 0; i < pMap->used; i++){
        if(pMap->items[i].key == key){
            return 1;
        }
    }
    return 0;
}

int get_index_for_key(Map *pMap, char key){
    for(int i = 0; i < pMap->used; i++){
        if(pMap->items[i].key == key){
            return  i;
        }
    }
    return -1;
}


void add_int_on_key(Map *pMap, char key, int number){
    for(int i = 0; i < pMap->used; i++){
        if(pMap->items[i].key == key){
            add_int(&pMap->items[i].value, number);
        }
    }
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
        free_array_memory(&pMap->items[i].value);
    }

    free(pMap->items);
    pMap->items= NULL;
    pMap->length = 0;
    pMap->used = 0;
}