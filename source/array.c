//
// Created by Hans Fredrik Brastad on 06/11/15.
//



#include "../headers/array.h"

const int RESIZE_FACTOR_ARRAY = 2;


Array new_array(int size){
    Array array;
    array.numbers = malloc(size * sizeof(int));
    array.usedLength = 0;
    array.length = size;
    array.currentIndex = 0;
    return  array;
}

void add_int(Array *pArray, int element){
    if (pArray->usedLength == pArray->length) {
        resize_array(pArray);
    }
    pArray->numbers[pArray->usedLength] = element;
    pArray->usedLength++;
}

void resize_array(Array *pArray){
    pArray->length *= RESIZE_FACTOR_ARRAY ;
    pArray->numbers= realloc(pArray->numbers, pArray->length * sizeof(int));

    if(pArray->numbers== NULL){
        printf("\nProgram couldn't reallocate more memory, freeing memory and exiting!\n");
        free_array_memory(pArray);
        exit(0);
    }
}


void free_array_memory(Array *pArray){
    free(pArray->numbers);
    pArray->numbers= NULL;
    pArray->length = 0;
    pArray->usedLength = 0;
}
