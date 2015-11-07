//
// Created by Hans Fredrik Brastad on 01/11/15.
//

#include <ctype.h>
#include <stdio.h>
#include "string.h"

#ifndef INNLEVERING2_FILE_UTILITY_H
#define INNLEVERING2_FILE_UTILITY_H

typedef enum {
    NORMAL,
    KEY
} ReadFlag;

int read_file(const char *fileName, String *pstring, ReadFlag readFlag);

int write_to_file(const char *fileName, String *pstring);

#endif //INNLEVERING2_FILE_UTILITY_H