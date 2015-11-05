//
// Created by Hans Fredrik Brastad on 31/10/15.
//


#include <string.h>
#include <math.h>
#include "../headers/string.h"

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


static void resize_string(String *pString){
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


void add_int_as_indiviudal_chars(String *encodedOutput, int number){

    if(number == 0) {
        add_char(encodedOutput, '0');
    }else{
        const int length = (int)log10(number)+1;

        char buffer[length];

        sprintf(buffer, "%d", number);

        for(int i = 0; i < length ; i++){
            add_char(encodedOutput, buffer[i]);
        }
    }
}



void encode_string(String *key, String *message, String *encodedOutput, int d){
    for(int i = 0; i < message->used; i++){

        if(check_char_lower(message->characters[i]) || check_char_upper(message->characters[i])){
            add_char(encodedOutput, '[');

            if(check_char_upper(message->characters[i])){
                add_char(encodedOutput, '-');
            }

            int pos = get_char_position(key, tolower(message->characters[i]));

            add_int_as_indiviudal_chars(encodedOutput, pos);

            add_char(encodedOutput, ']');
        }else{
            add_char(encodedOutput, message->characters[i]);
        }
    }
}

int check_char_lower(char chr){
    if(chr >= 'a' && 'z' >= chr) return 1;
    return 0;
}

int check_char_upper(char chr){
    if(chr >= 'A' && chr <= 'Z') return 1;
    return 0;
}



int get_char_position(String *pString, char target){
    for(int i = 0; i < pString->used; i++){
        if(pString->characters[i] == target){
            return  i;
        }
    }

    return -404;
}

char get_char_at_position(String *pString, int pos){
    for(int i = 0; i < pString->used; i++){
        if(i == pos){
            return pString->characters[i];
        }
    }
    return '0';
}


void decode_string(String *key, String *message, String *decodeOutput){

    for(int i = 0; i < message->used; i++){
        int streakCounter = 0;

        if(message->characters[i] == '['){
            int number;
            String numberBasedOnChar = new_string(2);

            i++;
            while(i < message->used && message->characters[i] != ']'){
                add_char(&numberBasedOnChar, message->characters[i]);
                streakCounter++;
                i++;
            }

            add_char(&numberBasedOnChar, '\0');
            sscanf(numberBasedOnChar.characters, "%d", &number);

            char charToAdd;

            if(number < 0){
                charToAdd = (char)toupper(get_char_at_position(key, abs(number)));

            }else{
                charToAdd = get_char_at_position(key, number);
            }


            add_char(decodeOutput, charToAdd);
            free_string_memory(&numberBasedOnChar);
        }else{
            add_char(decodeOutput, message->characters[i]);
        }

    }

}