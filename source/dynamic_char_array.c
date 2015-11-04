//
// Created by Hans Fredrik Brastad on 31/10/15.
//


#include "../headers/dynamic_char_array.h"

String new_string(int startSize){
    String string;
    string.charArray = malloc(startSize * sizeof(char));
    string.used = 0;
    string.length = startSize;
    return string;
}

void add_char(String *pString, char element) {
    if (pString->used == pString->length) {
        resize_string(pString);
    }

    pString->charArray[pString->used] = element;
    pString->used++;
}


static void resize_string(String *pString){
    pString->length *= ARRAY_RESIZE_FACTOR;
    pString->charArray = realloc(pString->charArray, pString->length * sizeof(char));

    if(pString->charArray == NULL){
        printf("\nProgram couldn't reallocate more memory, freeing memory and exiting!\n");
        free_string_memory(pString);
        exit(0);
    }
}


void free_string_memory(String *pString) {
    free(pString->charArray);
    pString->charArray = NULL;
    pString->length = 0;
    pString->used = 0;
}


void print_string(String *pString){
    for(int i = 0; i < pString->used; i++){
        printf("%c", pString->charArray[i]);
    }
}


void add_int_as_indiviudal_chars(String *encodedOutput, int number){
    String buffer = new_string(2);

    if(number == 0) add_char(&buffer, '0');

    while (number){
        char cToAdd = '0' + number % 10;
        number /= 10;
        add_char(&buffer, cToAdd);
    }

    for(int i = buffer.used-1; i >= 0; i--){
        add_char(encodedOutput, buffer.charArray[i]);
    }

    free_string_memory(&buffer);
}


void encode_string(String *key, String *message, String *encodedOutput, int d){
    for(int i = 0; i < message->used; i++){

        if((message->charArray[i] >= 'a' && 'z' >= message->charArray[i]) || (message->charArray[i] >= 'A' && message->charArray[i] <= 'Z')){
            add_char(encodedOutput, '[');

            if((message->charArray[i] >= 'A' && message->charArray[i] <= 'Z')){
                add_char(encodedOutput, '-');
            }

            int pos = get_char_position(key, tolower(message->charArray[i]));

            add_int_as_indiviudal_chars(encodedOutput, pos);

            add_char(encodedOutput, ']');
        }else{
            add_char(encodedOutput, message->charArray[i]);
        }
    }
}



int get_char_position(String *pString, char target){

    for(int i = 0; i < pString->used; i++){
        if(pString->charArray[i] == target){
            return  i;
        }
    }

    return -404;
}

char get_char_at_position(String *pString, int pos){
    for(int i = 0; i < pString->used; i++){
        if(i == pos){
            return pString->charArray[i];
        }
    }
    return '0';
}


void decode_string(String *key, String *message, String *decodeOutput){

    for(int i = 0; i < message->used; i++){
        int streakCounter = 0;

        if(message->charArray[i] == '['){
            int number;
            String numberBasedOnChar = new_string(2);

            i++;
            while(i < message->used && message->charArray[i] != ']'){
                add_char(&numberBasedOnChar, message->charArray[i]);
                streakCounter++;
                i++;
            }

            add_char(&numberBasedOnChar, '\0');
            sscanf(numberBasedOnChar.charArray, "%d", &number);

            char charToAdd;

            if(number < 0){

                charToAdd = toupper(get_char_at_position(key, abs(number)));

            }else{
                charToAdd = get_char_at_position(key, number);
            }


            add_char(decodeOutput, charToAdd);
            free_string_memory(&numberBasedOnChar);
        }else{
            add_char(decodeOutput, message->charArray[i]);
        }

    }

}