//
// Created by Hans Fredrik Brastad on 01/11/15.
//

#ifndef INNLEVERING2_ARRAYLIST_H
#define INNLEVERING2_ARRAYLIST_H

#include <stdlib.h>
#include <stdio.h>

const int RESIZE_FACTOR = 2;

typedef struct{
    int     *array;
    int     used;
    int     length;
}ArrayList;

ArrayList new_array(int startSize);
void add_int(ArrayList *pArray, int num);
void resize_array(ArrayList *a);
void free_array_memory(ArrayList *pArray);
void print_array_list(ArrayList *pArray);


#endif //INNLEVERING2_ARRAYLIST_H


