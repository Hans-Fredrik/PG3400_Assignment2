//
// Created by Hans Fredrik Brastad on 10/11/15.
//

#include "../headers/array_list.h"
#include "../headers/string.h"

ArrayList new_array_list(int size, int *mallocError){
    ArrayList arrayList;
    arrayList.strings = malloc(size * sizeof(String));

    if(arrayList.strings == NULL) {
        *mallocError = 1;
    }

    arrayList.length = size;
    arrayList.usedLength = 0;

    return arrayList;
}

void add_string(ArrayList *pArray, String element, int *mallocError){
    if(pArray->usedLength == pArray->length){
        if(!*mallocError) 
        resize_array_list(pArray, mallocError);
    }

    if(!*mallocError){
        pArray->strings[pArray->usedLength] = element;
        pArray->usedLength++;
    }
}

void resize_array_list(ArrayList *pArray, int *mallocError){
    pArray->length *= 2 ;
    pArray->strings = realloc(pArray->strings, pArray->length * sizeof(String));

    if(pArray->strings == NULL){
        *mallocError = 1;
    }
}

void free_array_list_memory(ArrayList *pArray){
    for(int i = 0; i < pArray->usedLength; i++){
        free_string_memory(&pArray->strings[i]);
    }
    free(pArray->strings);
    pArray->strings = NULL;
    pArray->length = 0;
    pArray->usedLength = 0;
}
