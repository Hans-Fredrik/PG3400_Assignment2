//
// Created by Hans Fredrik Brastad on 01/11/15.
//


#include <dirent.h>
#include <string.h>
#include "../headers/file_utility.h"

int read_file(const char *fileName, String *pstring, ReadFlag readFlag){
    FILE* file = fopen (fileName, "r");

    if(file == NULL) return 0;

    char readChar;

    while((fscanf (file, "%c", &readChar)) != EOF){
        if(readFlag == KEY){
            if((readChar >= 'a' && 'z' >= readChar) || (readChar >= 'A' && readChar <= 'Z')){
                add_char(pstring, (char) tolower(readChar));
            }
        }else if(readFlag == NORMAL){
            add_char(pstring, readChar);
        }
    }

    fclose (file);
    return 1;
}

int read_directory(const char *dirName, String *pString){
    DIR *dir;

    dir = opendir(dirName);

    if(dir == NULL){
        printf("Could not open the directory");
        return 0;
    }

    while (1) {
        struct dirent * entry;

        entry = readdir (dir);
        if (! entry) {
            break;
        }

        add_word(pString, dirName, strlen(dirName));
        add_word(pString, entry->d_name, strlen(entry->d_name));
        add_char(pString, '\n');
    }

    add_char(pString, '\0');

    closedir(dir);
    return 1;
}


int read_dictionary(const char *fileName, String *pstring){
    FILE* file = fopen (fileName, "r");

    if(file == NULL) return 0;

    char read[100];
    while(fgets(read, 100, file)){
        add_word(pstring, read, strlen(read));
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

