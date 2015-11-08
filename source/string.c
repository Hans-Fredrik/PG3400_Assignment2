//
// Created by Hans Fredrik Brastad on 31/10/15.
//

#include "../headers/string.h"
#include "../headers/map.h"
#include "../headers/array.h"

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


Map create_char_index_map(String *key){
    Map map = new_map(2);

    for(char i = 'a'; i <= 'z'; i++){
        const Item charItem = {.key = i, .value = new_array(2)};
        put(&map, charItem);
    }

    for(int i = 0; i < key->used; i++){
        add_int_on_key(&map, key->characters[i], i);
    }

    return map;
}

int get_char_position_in_map(Map *pMap, char target, int d){
    int keyIndex =  get_index_for_key(pMap, target);

    int usedLength = pMap->items[keyIndex].value.usedLength;
    int currentIndex = pMap->items[keyIndex].value.currentIndex;

    if (currentIndex >= usedLength){
        pMap->items[keyIndex].value.currentIndex = 0;
        currentIndex = 0;
    };

    if(usedLength > 1 && currentIndex < usedLength){

        if(currentIndex == 0){
            pMap->items[keyIndex].value.currentIndex++;
            return pMap->items[keyIndex].value.numbers[0];
        }

        for(int i = currentIndex; i < usedLength-1; i++){

            if((pMap->items[keyIndex].value.numbers[i] - pMap->items[keyIndex].value.numbers[currentIndex-1]) >= d){
                currentIndex = i;
                break;
            }
        }


        pMap->items[keyIndex].value.currentIndex = currentIndex+1;
        return pMap->items[keyIndex].value.numbers[currentIndex];

    }else{
        // Only 1 element aka no Adjacent code.
        return pMap->items[keyIndex].value.numbers[0];
    }

}


int encode_string(String *key, String *message, String *encodedOutput, int d){
    Map indexMap = create_char_index_map(key);

    if(!check_map_for_a_z(&indexMap)){
        free_map_memory(&indexMap);
        return 0;
    }

    for(int i = 0; i < message->used; i++){

        if(char_lower(message->characters[i]) || char_upper(message->characters[i])){
            add_char(encodedOutput, '[');

            if(char_upper(message->characters[i])){
                add_char(encodedOutput, '-');
            }

            int pos = get_char_position_in_map(&indexMap, tolower(message->characters[i]), d);

            add_int_as_indiviudal_chars(encodedOutput, pos);

            add_char(encodedOutput, ']');
        }else{
            add_char(encodedOutput, message->characters[i]);
        }
    }

    add_char(encodedOutput, '\0');
    free_map_memory(&indexMap);
    return 1;
}

int char_lower(char chr){
    if(chr >= 'a' && 'z' >= chr) return 1;
    return 0;
}


int char_upper(char chr){
    if(chr >= 'A' && chr <= 'Z') return 1;
    return 0;
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

        if(message->characters[i] == '['){
            String numberBasedOnChar = new_string(2);

            i++;
            while(i < message->used && message->characters[i] != ']'){
                add_char(&numberBasedOnChar, message->characters[i]);
                i++;
            }

            add_char(&numberBasedOnChar, '\0');

            int number;
            sscanf(numberBasedOnChar.characters, "%d", &number);


            if(number < 0){
                add_char(decodeOutput, (char)toupper(get_char_at_position(key, abs(number))));

            }else{
                add_char(decodeOutput, get_char_at_position(key, number));
            }

            free_string_memory(&numberBasedOnChar);
        }else{
            add_char(decodeOutput, message->characters[i]);
        }
    }
}

int check_map_for_a_z(Map *map){

    for(int i = 0; i < map->used; i++){
        if(map->items[i].value.usedLength == 0) return 0;
    }

    return  1;
}