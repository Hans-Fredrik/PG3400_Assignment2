//
// Created by Hans Fredrik Brastad on 06/11/15.
//

#ifndef INNLEVERING2_ARRAY_H
#define INNLEVERING2_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "string.h"

const int RESIZE_FACTOR_ARRAY;



typedef struct{
    int         *numbers;
    int         usedLength;
    int         length;
    int         currentIndex;
}Array;


Array new_array(int size);

void add_int(Array *pArray, int element);

void resize_array(Array *pArray);

void free_array_memory(Array *pArray);


#endif //INNLEVERING2_ARRAY_H
