//
// Created by Hans Fredrik Brastad on 09/11/15.
//


#include "../headers/crack_util.h"


int check_matching_words(String *pDecoded, String *words){
    char *wordsToCheck = strtok(pDecoded->characters, " ");
    if(wordsToCheck == NULL) {
        return NULL;
    }

    while(wordsToCheck != NULL){
        printf("%s", wordsToCheck);

        wordsToCheck = strtok(NULL, " ");
    }

    return 1;
}
