//
// Created by Hans Fredrik Brastad on 09/11/15.
//

#include "../headers/search_util.h"

/*
struct NumberFromFile binary_arraylist_search(struct ArrayList *pArray, int keyElement){
    struct NumberFromFile valueAndIndex = {0,-1, -1};
    int minIndex = 0;
    int maxIndex = pArray->used-1;
    int midIndex = 0;

    while (minIndex <= maxIndex) {
        midIndex = (minIndex+maxIndex)/2;

        if(pArray->array[midIndex].number == keyElement){
            valueAndIndex.number = pArray->array[midIndex].number;
            valueAndIndex.index = midIndex;
            valueAndIndex.file_index = pArray->array[midIndex].file_index;
            return valueAndIndex;
        }
        else if (pArray->array[midIndex].number < keyElement){
            minIndex = midIndex + 1;
        }
        else if(pArray->array[midIndex].number > keyElement){
            maxIndex = midIndex - 1;
        }
    }

    return valueAndIndex;
}
*/