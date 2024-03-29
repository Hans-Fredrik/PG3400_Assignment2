//
// Created by Hans Fredrik Brastad on 09/11/15.
//

#include "../headers/crack_util.h"
#include "../headers/string.h"
#include "../headers/exception_handler.h"


int brute_force_right_key(String *crackedKey, char *keyname, String *encodedText, ArrayList *wordList, int *memoryError){
    int highestPercentage = 0;

    while (keyname != NULL){

        if(strlen(keyname) > 7){

            String stringKey = new_string(2, memoryError);

            if(!read_file(keyname, &stringKey, KEY, memoryError)){
                free_string_memory(&stringKey);
                return 0;
            }

            String decodedText = new_string(2, memoryError);

            if(!decode_string(&stringKey, encodedText, &decodedText, memoryError)){
                free_string_memory(&decodedText);
                free_string_memory(&stringKey);
                return 0;
            }

            int result = check_decoded_words_in_dictionary(&decodedText, wordList, memoryError);

            if(result > highestPercentage){
                highestPercentage = result;
                remove_string_content(crackedKey);
                add_word(crackedKey, keyname, strlen(keyname), memoryError);
                add_char(crackedKey, '\0', memoryError);
            }


            free_string_memory(&decodedText);
            free_string_memory(&stringKey);

            if(*memoryError){
                return 0;
            }
        }


        if(highestPercentage == 100) return  1;

        keyname = strtok(NULL, "\n");
    }

    if(highestPercentage == 0) return 0;

    return  1;
}



int check_decoded_words_in_dictionary(String *pDecoded, ArrayList *words, int *memoryError){

    int found = 0;
    int numeberOfWords = 0;

    for(int i = 0; i < pDecoded->used-1; i++){

        String word = new_string(2, memoryError);
        while(char_lower(pDecoded->characters[i]) || char_upper(pDecoded->characters[i])){
            add_char(&word, tolower(pDecoded->characters[i]), memoryError);
            i++;
        }
        if(*memoryError) break;

        if(word.used > 0){
            add_char(&word, '\0', memoryError);
            numeberOfWords++;
            if(binary_arraylist_search(words, word.characters)){
                found++;
            }
        }

        free_string_memory(&word);

        if(*memoryError) break;
    }


    return (found*100)/numeberOfWords;
}

