//
// Created by Hans Fredrik Brastad on 31/10/15.
//

#include "secretCoder.h"
#include <string.h>
#include "headers/string.h"
#include "headers/file_reader.h"
#include "headers/string_util.h"
#include "headers/crack_util.h"
#include "headers/encode_decode_util.h"


static const int DEFAULT_SIZE = 2;


static void on_error_free_helper(String *pString, String *pString1, String *pString2){
    free_string_memory(pString);
    free_string_memory(pString1);
    free_string_memory(pString2);
}


char *encode(const char *inputMessageFile, const char *keyFile, const char *outputFile, int *status, int d){
    if(inputMessageFile == NULL || keyFile == NULL || outputFile == NULL) return NULL;

    *status = 0;
    if(d < 0) d = 0;
    int memoryError = 0;

    String keyString = new_string(DEFAULT_SIZE, &memoryError);
    String inputString = new_string(DEFAULT_SIZE, &memoryError);
    String encodedString = new_string(DEFAULT_SIZE, &memoryError);

    if(memoryError){
        on_error_free_helper(&keyString, &inputString, &encodedString);
        OUTPUT_ERROR("\nCould not allocate enough memory");
        *status = 1;
        return  NULL;
    }

    if(!read_and_parse_key_file(keyFile, &keyString, status)){
        on_error_free_helper(&keyString, &inputString, &encodedString);
        return NULL;
    }

    if(!read_the_message_to_encode(inputMessageFile, &inputString, status)){
        on_error_free_helper(&keyString, &inputString, &encodedString);
        return NULL;
    }

    if(!encode_the_message_with_key(&keyString, &inputString, &encodedString, keyFile, status, d)){
        on_error_free_helper(&keyString, &inputString, &encodedString);
        return NULL;
    }

    if(!write_encoded_message_to_file(outputFile, &encodedString, status)){
        on_error_free_helper(&keyString, &inputString, &encodedString);
        return  NULL;
    }

    free_string_memory(&keyString);
    free_string_memory(&inputString);

    return encodedString.characters;
}


char *decode(const char *inputCodeFile, const char *keyFile, int *status){
    if(inputCodeFile == NULL || keyFile == NULL) return NULL;

    *status = 0;
    int memoryError = 0;

    String keyString = new_string(DEFAULT_SIZE, &memoryError);
    String encodedFileText = new_string(DEFAULT_SIZE, &memoryError);
    String decodedText = new_string(DEFAULT_SIZE, &memoryError);

    if(memoryError){
        on_error_free_helper(&keyString, &encodedFileText, &decodedText);
        OUTPUT_ERROR("\nCould not allocate enough memory");
        *status = 1;
        return  NULL;
    }

    if(!read_and_parse_key_file(keyFile, &keyString, status)){
        on_error_free_helper(&keyString, &encodedFileText, &decodedText);
        return NULL;
    }

    if(!read_encoded_message_to_decode(inputCodeFile, &encodedFileText, status)){
        on_error_free_helper(&keyString, &encodedFileText, &decodedText);
        return NULL;
    }


    if(!decode_string(&keyString, &encodedFileText, &decodedText, &memoryError)){
        on_error_free_helper(&keyString, &encodedFileText, &decodedText);
        return NULL;
    }


    free_string_memory(&keyString);
    free_string_memory(&encodedFileText);
    return decodedText.characters;
}


char *crack(const char *inputCodeFile, const char *keyFolder, int *status){
    if(inputCodeFile == NULL || keyFolder == NULL) return NULL;

    int memoryError = 0;

    ArrayList wordList = new_array_list(DEFAULT_SIZE, &memoryError);
    read_dictionary("words", &wordList, &memoryError);


    String encodedText = new_string(DEFAULT_SIZE, &memoryError);
    if(!read_file(inputCodeFile, &encodedText, NORMAL ,&memoryError)){
        *status = 1;
        return NULL;
    }

    String keyfiles = new_string(DEFAULT_SIZE, &memoryError);
    if(!read_directory(keyFolder, &keyfiles, &memoryError)){
        *status = 2;
        return NULL;
    }

    char *keyname = strtok(keyfiles.characters, "\n");
    if(keyname == NULL) {
        return NULL;
    }

    String crackedKey = new_string(DEFAULT_SIZE, &memoryError);

    if(!brute_force_right_key(&crackedKey, keyname, &encodedText, &wordList, &memoryError) || memoryError){

    }

    String keyString = new_string(DEFAULT_SIZE, &memoryError);
    read_file(crackedKey.characters, &keyString, KEY, &memoryError);

    String decodedText = new_string(DEFAULT_SIZE, &memoryError);
    decode_string(&keyString, &encodedText, &decodedText, &memoryError);

    printf("Key: ");
    OUTPUT_COMPLETE(crackedKey.characters);

    free_string_memory(&keyfiles);
    free_string_memory(&encodedText);
    free_string_memory(&crackedKey);
    free_string_memory(&keyString);
    free_array_list_memory(&wordList);


    return  decodedText.characters;
}



