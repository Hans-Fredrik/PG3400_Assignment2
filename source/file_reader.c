//
// Created by Hans Fredrik Brastad on 01/11/15.
//


#include "../headers/file_reader.h"
#include "../headers/string.h"

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

        if(*memoryError){
            fclose(file);
            return 0;
        }
    }

    fclose (file);
    return 1;
}


int read_directory(const char *dirName, String *pString, int *memoryError){
    DIR *dir;

    dir = opendir(dirName);

    if(dir == NULL){
        return 0;
    }

    while (!*memoryError) {
        struct dirent * entry;

        entry = readdir (dir);
        if (! entry) {
            break;
        }

        add_word(pString, dirName, strlen(dirName), memoryError);
        add_word(pString, entry->d_name, strlen(entry->d_name), memoryError);
        add_char(pString, '\n', memoryError);
    }
    add_char(pString, '\0', memoryError);


    if(*memoryError){
        closedir(dir);
        return 0;
    }

    closedir(dir);
    return 1;
}


int read_dictionary(const char *fileName, ArrayList *pArrayList, int *memoryError){
    FILE* file = fopen (fileName, "r");

    if(file == NULL) return 0;

    char read[100];

    while(fgets(read, 100, file) != NULL){
        String word = new_string(2, memoryError);

        add_word(&word, read, strlen(read), memoryError);
        add_char(&word, '\0', memoryError);
        add_string(pArrayList, word, memoryError);

        if(*memoryError){
            fclose (file);
            return 0;
        }
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

