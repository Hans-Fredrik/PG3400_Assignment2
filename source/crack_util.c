//
// Created by Hans Fredrik Brastad on 09/11/15.
//

#include "../headers/crack_util.h"
#include "../headers/string.h"


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
            decode_string(&stringKey, encodedText, &decodedText, memoryError);


            int result = check_decoded_words_in_dictionary(&decodedText, wordList, memoryError);
            if(result > highestPercentage){
                highestPercentage = result;

                remove_string_content(crackedKey);
                add_word(crackedKey, keyname, strlen(keyname), memoryError);
                add_char(crackedKey, '\0', memoryError);
            }


            free_string_memory(&decodedText);
            free_string_memory(&stringKey);
        }


        if(highestPercentage == 100) return  1;

        keyname = strtok(NULL, "\n");
    }

    if(highestPercentage == 0) return 0;

    return  1;
}



int check_decoded_words_in_dictionary(String *pDecoded, ArrayList *words, int *mallocError){

    int found = 0;
    int numeberOfWords = 0;

    for(int i = 0; i < pDecoded->used-1; i++){

        String word = new_string(2, mallocError);
        while(char_lower(pDecoded->characters[i]) || char_upper(pDecoded->characters[i])){
            add_char(&word, tolower(pDecoded->characters[i]), mallocError);
            i++;
        }

        if(word.used > 0){
            add_char(&word, '\0', mallocError);
            numeberOfWords++;
            if(binary_arraylist_search(words, word.characters)){
                found++;
            }
        }

        free_string_memory(&word);
    }


    return (found*100)/numeberOfWords;
}