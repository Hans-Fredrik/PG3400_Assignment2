//
// Created by Hans Fredrik Brastad on 01/11/15.
//

#include "dynamic_char_array.h"

#ifndef INNLEVERING2_FILE_UTILITY_H
#define INNLEVERING2_FILE_UTILITY_H

#endif //INNLEVERING2_FILE_UTILITY_H
typedef enum {NORMAL, KEY, DECODE} ReadFlag;

int read_file(char *fileName, String *pstring, ReadFlag readFlag);

int write_to_file(char *fileName, String *pstring);