//
// Created by Hans Fredrik Brastad on 01/11/15.
//

#include <ctype.h>
#include <stdio.h>
#include "string.h"

#ifndef INNLEVERING2_FILE_READER_H
#define INNLEVERING2_FILE_READER_H

#include <dirent.h>
#include <string.h>
#include "array_list.h"


typedef enum {
    NORMAL,
    KEY
} ReadFlag;

int read_file(const char *fileName, String *pstring, ReadFlag readFlag, int *memoryError);

int read_directory(const char *dirName, String *pString, int *mallocError);

int write_to_file(const char *fileName, String *pstring);

int read_dictionary(const char *fileName, ArrayList *pArrayList, int *mallocError);

#endif //INNLEVERING2_FILE_READER_H