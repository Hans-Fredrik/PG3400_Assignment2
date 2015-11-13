//
// Created by Hans Fredrik Brastad on 01/11/15.
//


#include "../headers/file_reader.h"

int read_file(const char *fileName, String *pstring, ReadFlag readFlag, int *memoryError){
    FILE* file = fopen (fileName, "r");

    if(file == NULL) return 0;

    char readChar;

    while((fscanf (file, "%c", &readChar)) != EOF){
        if(readFlag == KEY){
            if((readChar >= 'a' && 'z' >= readChar) || (readChar >= 'A' && readChar <= 'Z')){
                add_char(pstring, (char) tolower(readChar), memoryError);
            }
        }else if(readFlag == NORMAL){
            add_char(pstring, readChar, memoryError);
        }
    }

    fclose (file);
    return 1;
}


int read_directory(const char *dirName, String *pString, int *mallocError){
    DIR *dir;

    dir = opendir(dirName);

    if(dir == NULL){
        return 0;
    }

    while (1) {
        struct dirent * entry;

        entry = readdir (dir);
        if (! entry) {
            break;
        }

        add_word(pString, dirName, strlen(dirName), mallocError);
        add_word(pString, entry->d_name, strlen(entry->d_name), mallocError);
        add_char(pString, '\n', mallocError);
    }

    add_char(pString, '\0', mallocError);

    closedir(dir);
    return 1;
}


int read_dictionary(const char *fileName, ArrayList *pArrayList, int *mallocError){
    FILE* file = fopen (fileName, "r");

    if(file == NULL) return 0;

    char read[100];

    while(fgets(read, 100, file) != NULL){
        String word = new_string(2, mallocError);

        add_word(&word, read, strlen(read), mallocError);
        add_char(&word, '\0', mallocError);

        add_string(pArrayList, word, mallocError);
    }

    fclose (file);
    return 1;
}


int write_to_file(const char *fileName, String *pstring){
    if(fileName == NULL) return 0;

    FILE *encodedMessageFile = fopen(fileName, "w");

    if(encodedMessageFile == NULL) return 0;

    fwrite(pstring->characters, sizeof(char), pstring->used, encodedMessageFile);

    fclose(encodedMessageFile);

    return 1;
}

