//
// Created by Hans Fredrik Brastad on 01/11/15.
//

#ifndef INNLEVERING2_ARRAYLIST_H
#define INNLEVERING2_ARRAYLIST_H
#include <stdlib.h>
#include <stdio.h>
#include "dynamic_char_array.h"

const int ARRAY_RESIZE_FACTOR = 2;

typedef union Data {
    char character;
    int number;

} Data;


typedef struct{
    Data *array;
    int used;
    int length;

}ArrayList;

void create_new_array(ArrayList *pArray, int startSize);
void add_char(ArrayList *pArray, char chr);
void add_int(ArrayList *pArray, int num);
void resize_array(ArrayList *a);
void free_array_memory(ArrayList *pArray);
void print_array_list(ArrayList *pArray);


#endif //INNLEVERING2_ARRAYLIST_H


