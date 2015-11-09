//
// Created by Hans Fredrik Brastad on 31/10/15.
//

#ifndef INNLEVERING2_ARRAYLIST_H
#define INNLEVERING2_ARRAYLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "../headers/map.h"


const int ARRAY_RESIZE_FACTOR;


typedef struct{
    char    *characters;
    int     used;
    int     length;
}String;


String new_string(int startSize);
void add_char(String *pString, char element);
void add_word(String *pString, const char *word, size_t length);
void resize_string(String *pString);
void free_string_memory(String *pString);

void print_string(String *pString);
int encode_string(String *key, String *message, String *encodedOutput, int d);
int get_char_position_in_map(Map *pMap, char target, int d);
void add_int_as_indiviudal_chars(String *encodedOutput, int number);
void decode_string(String *key, String *message, String *decodeOutput);
char get_char_at_position(String *pString, int pos);
int verify_adjacent_code(Item *item, int d);

    int char_lower(char chr);
int char_upper(char chr);
int check_map_for_a_z(Map *map);


#endif //INNLEVERING2_ARRAYLIST_H
