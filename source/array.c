//
// Created by Hans Fredrik Brastad on 06/11/15.
//



#include "../headers/array.h"

const int RESIZE_FACTOR_ARRAY = 2;


Array new_array(int size, int  *mallocError){
    Array array;
    array.numbers = malloc(size * sizeof(int));

    if(array.numbers == NULL) *mallocError = 1;

    array.usedLength = 0;
    array.length = size;
    array.currentIndex = 0;
    return  array;
}

void add_int(Array *pArray, int element, int *mallocError){
    if (pArray->usedLength == pArray->length) {
        if(!*mallocError)
        resize_array(pArray, mallocError);
    }
    if(!*mallocError){
        pArray->numbers[pArray->usedLength] = element;
        pArray->usedLength++;
    }
}

void resize_array(Array *pArray, int *mallocError){
    pArray->length *= RESIZE_FACTOR_ARRAY ;
    pArray->numbers= realloc(pArray->numbers, pArray->length * sizeof(int));

    if(pArray->numbers== NULL){
        *mallocError = 1;
    }
}


void free_array_memory(Array *pArray){
    free(pArray->numbers);
    pArray->numbers= NULL;
    pArray->length = 0;
    pArray->usedLength = 0;
}
