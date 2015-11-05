//
// Created by Hans Fredrik Brastad on 01/11/15.
//


#include "../headers/file_utility.h"

int read_file(char *fileName, String *pstring, ReadFlag readFlag){
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


int write_to_file(char *fileName, String *pstring){
    FILE *encodedMessageFile = fopen(fileName, "w");

    if(encodedMessageFile == NULL) return 0;

    fwrite(pstring->characters, sizeof(char), pstring->used, encodedMessageFile);

    fclose(encodedMessageFile);

    return 1;
}

