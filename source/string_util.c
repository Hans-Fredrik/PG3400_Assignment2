//
// Created by Hans Fredrik Brastad on 06/11/15.
//

#include "../headers/string_util.h"
#include "../headers/string.h"


void remove_string_content(String *pString){
    for(int i = 0; i < pString->used-1; i++){
        pString->characters[i] = ' ';
        pString->used = 0;
    }
}


void add_int_as_indiviudal_chars(String *encodedOutput, int number, int *memoryError){

    if(number == 0) {
        add_char(encodedOutput, '0', memoryError);
    }else{
        const int length = (int)log10(number)+1;

        char buffer[length];

        sprintf(buffer, "%d", number);

        for(int i = 0; i < length ; i++){
            add_char(encodedOutput, buffer[i], memoryError);
        }
    }
}


Map create_char_index_map(String *key, int *malloc_error){
    Map map = new_map(2 ,malloc_error);

    for(char i = 'a'; i <= 'z'; i++){
        const Item charItem = {.key = i, .value = new_array(2, malloc_error), .isUsed = 0};
        put(&map, charItem, malloc_error);
    }

    for(int i = 0; i < key->used; i++){
        add_int_on_key(&map, key->characters[i], i, malloc_error);
    }

    return map;
}


int get_char_position_in_map(Map *pMap, char target, int d){
    int keyIndex =  get_index_for_key(pMap, target);

    int usedLength = pMap->items[keyIndex].value.usedLength;
    int currentIndex = pMap->items[keyIndex].value.currentIndex;


    if(pMap->items[keyIndex].isUsed){
        verify_adjacent_code(&pMap->items[keyIndex], d);
    }else{
        pMap->items[keyIndex].isUsed = 1;
    }


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
        // Only 1 element at char, no need to try keep adjacent
        return pMap->items[keyIndex].value.numbers[0];
    }

}


int encode_string(String *key, String *message, String *encodedOutput, int d , int *memoryError){

    Map indexMap = create_char_index_map(key, memoryError);

    if(!check_map_for_a_z(&indexMap) || *memoryError){
        free_map_memory(&indexMap);
        return 0;
    }


    for(int i = 0; i < message->used; i++){

        if(char_lower(message->characters[i]) || char_upper(message->characters[i])){
            add_char(encodedOutput, '[', memoryError);

            if(char_upper(message->characters[i])){
                add_char(encodedOutput, '-', memoryError);
            }

            int pos = get_char_position_in_map(&indexMap, tolower(message->characters[i]), d);


            add_int_as_indiviudal_chars(encodedOutput, pos, memoryError);

            add_char(encodedOutput, ']' ,memoryError);
        }else{
            add_char(encodedOutput, message->characters[i], memoryError);
        }

        if(*memoryError) break;
    }

    add_char(encodedOutput, '\0', memoryError);
    free_map_memory(&indexMap);

    if(*memoryError) return 0;

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


int decode_string(String *key, String *message, String *decodeOutput, int *memoryError){

    for(int i = 0; i < message->used; i++){
        if(message->characters[i] == '['){
            String numberBasedOnChar = new_string(2, memoryError);
            if(*memoryError) {
                free_string_memory(&numberBasedOnChar);
                return 0;
            }

            i++;
            while(i < message->used && message->characters[i] != ']'){
                add_char(&numberBasedOnChar, message->characters[i], memoryError);
                i++;

                if(*memoryError){
                    free_string_memory(&numberBasedOnChar);
                    return 0;
                }
            }

            add_char(&numberBasedOnChar, '\0', memoryError);

            int number;
            sscanf(numberBasedOnChar.characters, "%d", &number);


            if(number < 0){
                add_char(decodeOutput, (char)toupper(get_char_at_position(key, abs(number))), memoryError);

            }else{
                add_char(decodeOutput, get_char_at_position(key, number), memoryError);
            }

            free_string_memory(&numberBasedOnChar);
            if(*memoryError) return 0;
        }else{
            add_char(decodeOutput, message->characters[i], memoryError);
        }

        if(*memoryError) return 0;
    }

    return 1;
}


int check_map_for_a_z(Map *map){

    for(int i = 0; i < map->used; i++){
        if(map->items[i].value.usedLength == 0) return 0;
    }

    return  1;
}


int verify_adjacent_code(Item *item, int d){
    if(d == 0) return 1;

    if(item->value.usedLength == 1){
        printf("\nEncode function (Warning): "
                       "Only 1 index[%d] on key [%c] in keystring not possible to satifsy d = %d\n " ,item->value.numbers[0],item->key, d);

        return 0;
    }

    int lowestNumber = item->value.numbers[0];
    int numbersOfIndexesFullFillD = 0;

    for(int l = 0; l < item->value.usedLength; l++){
        if(lowestNumber > item->value.numbers[l]) {
            lowestNumber = item->value.numbers[l];
        }
    }

    for(int x = 0; x < item->value.usedLength; x++){
        if((item->value.numbers[x] - lowestNumber) >= d){
            numbersOfIndexesFullFillD++;
        }
    }

    if(numbersOfIndexesFullFillD < 2){
        printf("\nEncode function (Warning): Did not satisfy [%d] units between indexes on char [%c] in key. Number of indexes: %d\n"
                ,d, item->key, item->value.usedLength);
    }

    return 1;
}