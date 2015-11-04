//
// Created by Hans Fredrik Brastad on 01/11/15.
//

#include "../headers/arraylist.h"

void create_new_array(ArrayList *pArray, int startSize){
    pArray->array = malloc(startSize * sizeof(Data));
    pArray->used = 0;
    pArray->length = startSize;
}


void add_char(ArrayList *pArray, char chr) {
    if (pArray->used == pArray->length) {
        resize_array(pArray);
    }
    pArray->array[pArray->used].character = chr;
    pArray->used++;
}

void add_int(ArrayList *pArray, int num) {
    if (pArray->used == pArray->length) {
        resize_array(pArray);
    }
    pArray->array[pArray->used].number = num;
    pArray->used++;
}



void resize_array(ArrayList *a){
    a->length *= ARRAY_RESIZE_FACTOR;
    a->array = realloc(a->array, a->length * sizeof(Data));

    if(a->array == NULL){
        printf("\nProgram couldn't reallocate more memory, freeing memory and exiting!\n");
        free_array_memory(a);
        exit(0);
    }
}


void free_array_memory(ArrayList *pArray) {
    free(pArray->array);
    pArray->array = NULL;
    pArray->length = 0;
    pArray->used = 0;
}


void print_array_list(ArrayList *pArray){
    for(int i = 0; i < pArray->used; i++){
        printf("[%d] \t", pArray->array[i].number);
    }
}

