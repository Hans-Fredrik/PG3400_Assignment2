//
// Created by Hans Fredrik Brastad on 06/11/15.
//

#ifndef INNLEVERING2_STRING_UTIL_H
#define INNLEVERING2_STRING_UTIL_H

#define KNRM  "\x1B[0m"
#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE  "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CYAN  "\x1B[36m"
#define WHITE  "\x1B[37m"
#define RESET "\033[0m"

#define OUTPUT_FILE_ERROR(MSG, DATA) printf("%s %s [%s] %s", RED, MSG, DATA, RESET)
#define OUTPUT_ERROR(MSG) printf("%s %s %s", RED, MSG, RESET)
#define OUTPUT_WARNING(MSG) printf("%s %s %s \n", GREEN, MSG, RESET)
#define OUTPUT_COMPLETE(MSG) printf("%s %s %s \n", GREEN, MSG, RESET)

#include "../headers/string.h"


void remove_string_content(String *pString);

int encode_string(String *key, String *message, String *encodedOutput, int d, int *memoryError);

int get_char_position_in_map(Map *pMap, char target, int d);

void add_int_as_indiviudal_chars(String *encodedOutput, int number, int *memoryError);

void decode_string(String *key, String *message, String *decodeOutput, int *memoryError);

char get_char_at_position(String *pString, int pos);

int verify_adjacent_code(Item *item, int d);

int char_lower(char chr);

int char_upper(char chr);

int check_map_for_a_z(Map *map);


#endif //INNLEVERING2_STRING_UTIL_H
