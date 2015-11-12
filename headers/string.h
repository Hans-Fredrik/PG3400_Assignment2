//
// Created by Hans Fredrik Brastad on 31/10/15.
//

#ifndef INNLEVERING2_ARRAYLIST_H
#define INNLEVERING2_ARRAYLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "map.h"


const int ARRAY_RESIZE_FACTOR;


typedef struct{
    char    *characters;
    int     used;
    int     length;
}String;



String new_string(int startSize, int *mallocError);
void add_char(String *pString, char element, int *mallocError);
void add_word(String *pString, const char *word, size_t length, int *mallocError);
void resize_string(String *pString, int *mallocError);
void free_string_memory(String *pString);
void print_string(String *pString);



#endif //INNLEVERING2_ARRAYLIST_H
