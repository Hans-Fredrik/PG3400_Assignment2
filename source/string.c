//
// Created by Hans Fredrik Brastad on 31/10/15.
//


#include "../headers/string.h"

const int ARRAY_RESIZE_FACTOR = 2;

String new_string(int startSize){
    String string;
    string.characters = malloc(startSize * sizeof(char));
    string.used = 0;
    string.length = startSize;
    return string;
}


void add_char(String *pString, char element) {
    if (pString->used == pString->length) {
        resize_string(pString);
    }

    pString->characters[pString->used] = element;
    pString->used++;
}


void add_word(String *pString, const char *word, size_t length){
    for(int i = 0; i < length; i++){
        if(word[i] != '\n'){
            add_char(pString, word[i]);
        }
    }
}


void resize_string(String *pString){
    pString->length *= ARRAY_RESIZE_FACTOR;
    pString->characters = realloc(pString->characters, pString->length * sizeof(char));

    if(pString->characters == NULL){
        printf("\nProgram couldn't reallocate more memory, freeing memory and exiting!\n");
        free_string_memory(pString);
        exit(0);
    }
}


void free_string_memory(String *pString) {
    free(pString->characters);
    pString->characters = NULL;
    pString->length = 0;
    pString->used = 0;
}


void print_string(String *pString){
    for(int i = 0; i < pString->used; i++){
        printf("%c", pString->characters[i]);
    }
}
