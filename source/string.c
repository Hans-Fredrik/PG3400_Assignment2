//
// Created by Hans Fredrik Brastad on 31/10/15.
//


#include "../headers/string.h"

const int ARRAY_RESIZE_FACTOR = 2;

String new_string(int startSize, int *mallocError){
    String string;
    string.characters = malloc(startSize * sizeof(char));

    if(string.characters == NULL) *mallocError = 1;

    string.used = 0;
    string.length = startSize;
    return string;
}


void add_char(String *pString, char element, int *mallocError) {
    if (pString->used == pString->length) {
        if(!*mallocError)
        resize_string(pString, mallocError);
    }

    if(!*mallocError){
        pString->characters[pString->used] = element;
        pString->used++;
    }
}


void add_word(String *pString, const char *word, size_t length, int *mallocError){
    for(int i = 0; i < length; i++){
        if(word[i] != '\n'){
            if(*mallocError) break;
            add_char(pString, word[i], mallocError);
        }
    }
}


void resize_string(String *pString, int *mallocError){
    pString->length *= ARRAY_RESIZE_FACTOR;
    pString->characters = realloc(pString->characters, pString->length * sizeof(char));


    if(pString->characters == NULL){
        // This implementation need to throw the error up, because of the exception handler. So no freeing at this level.
        *mallocError = 1;
    }
}


void free_string_memory(String *pString) {
    free(pString->characters);
    pString->characters = NULL;
    pString->length = 0;
    pString->used = 0;
}


