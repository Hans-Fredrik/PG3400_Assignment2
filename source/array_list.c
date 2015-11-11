//
// Created by Hans Fredrik Brastad on 10/11/15.
//

#include "../headers/array_list.h"
#include "../headers/string.h"

ArrayList new_array_list(int size){
    ArrayList arrayList;
    arrayList.strings = malloc(size * sizeof(String));
    arrayList.length = size;
    arrayList.usedLength = 0;

    return arrayList;
}

void add_string(ArrayList *pArray, String element){
    if(pArray->usedLength == pArray->length){
        resize_array_list(pArray);
    }

    pArray->strings[pArray->usedLength] = element;
    pArray->usedLength++;
}

void resize_array_list(ArrayList *pArray){
    pArray->length *= 2 ;
    pArray->strings = realloc(pArray->strings, pArray->length * sizeof(String));

    if(pArray->strings == NULL){
        printf("\nFROM ARRAYLIST: Program couldn't reallocate more memory, freeing memory and exiting!\n");
        free_array_list_memory(pArray);
        exit(0);
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
