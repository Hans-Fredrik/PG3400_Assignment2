//
// Created by Hans Fredrik Brastad on 10/11/15.
//

#ifndef INNLEVERING2_ARRAY_LIST_H
#define INNLEVERING2_ARRAY_LIST_H


#include "string.h"

typedef struct{
    String         *strings;
    int         usedLength;
    int         length;
}ArrayList;

ArrayList new_array_list(int size);

void add_string(ArrayList *pArray, String element);

void resize_array_list(ArrayList *pArray);

void free_array_list_memory(ArrayList *pArray);



#endif //INNLEVERING2_ARRAY_LIST_H
