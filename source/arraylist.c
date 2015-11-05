//
// Created by Hans Fredrik Brastad on 01/11/15.
//

#include "../headers/arraylist.h"

ArrayList new_array(int startSize){
    ArrayList arrayList;
    arrayList.array = malloc(startSize * sizeof(int));
    arrayList.used = 0;
    arrayList.length = startSize;
    return arrayList;
}


void add_int(ArrayList *pArray, int num) {
    if (pArray->used == pArray->length) {
        resize_array(pArray);
    }
    pArray->array[pArray->used] = num;
    pArray->used++;
}



void resize_array(ArrayList *a){
    a->length *= RESIZE_FACTOR ;
    a->array = realloc(a->array, a->length * sizeof(int));

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
        printf("[%d] \t", pArray->array[i]);
    }
}

