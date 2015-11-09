//
// Created by Hans Fredrik Brastad on 01/11/15.
//

#include <ctype.h>
#include <stdio.h>
#include "string.h"

#ifndef INNLEVERING2_FILE_UTILITY_H
#define INNLEVERING2_FILE_UTILITY_H

#include <dirent.h>
#include <string.h>

typedef enum {
    NORMAL,
    KEY
} ReadFlag;

int read_file(const char *fileName, String *pstring, ReadFlag readFlag);

int read_directory(const char *dirName, String *pString);

int write_to_file(const char *fileName, String *pstring);

int read_dictionary(const char *fileName, String *pstring);

#endif //INNLEVERING2_FILE_UTILITY_H