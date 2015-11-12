//
// Created by Hans Fredrik Brastad on 09/11/15.
//

#ifndef INNLEVERING2_CRACK_UTIL_H
#define INNLEVERING2_CRACK_UTIL_H

#include <string.h>
#include "../headers/string.h"
#include "../headers/string_util.h"
#include "../headers/file_reader.h"
#include "../headers/array_list.h"
#include "../headers/search_util.h"

int brute_force_right_key(String *crackedKey, char *keyname, String *encodedText, ArrayList *wordList, int *memoryError);
int check_decoded_words_in_dictionary(String *pDecoded, ArrayList *words, int *mallocError);

#endif //INNLEVERING2_CRACK_UTIL_H
