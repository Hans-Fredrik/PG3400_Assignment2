//
// Created by Hans Fredrik Brastad on 31/10/15.
//

#include "secretCoder.h"
#include <string.h>
#include "headers/string.h"
#include "headers/file_reader.h"
#include "headers/string_util.h"
#include "headers/exception_handler.h"


static const int DEFAULT_SIZE = 2;


static void on_error_free_helper(String *pString, String *pString1, String *pString2){
    free_string_memory(pString);
    free_string_memory(pString1);
    free_string_memory(pString2);
}

/*
 * 1. Memory error
 * 2. Keyfile errror
 * 3. Inputfilemessage error
 * 4. Could not satisfy d condition
 * 5. Keyfile does not have a-z
 * 6. Could write to outputFile, name can't be blank
 */
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

/*
 * 1 -> means memory issue (Most likely not going to happen but can)
 * 2 -> Could nopen open and read keyfile
 * 3 -> Could not open and read encoded message file
 * 1 -> memory error again.
 */

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

    if(decodedText.used == 0){
        free_string_memory(&decodedText);
        return  NULL;
    }

    return decodedText.characters;
}

static void on_error_decode_helper(String *pS1, String *pS2, String *pS3, ArrayList *pArrayList){
    free_string_memory(pS1);
    free_string_memory(pS2);
    free_string_memory(pS3);
    free_array_list_memory(pArrayList);

}

/*
 * 1. Memory error
 * 2. Could not open keyfile
 * 3. COuld not read inputCodeFile
 * 4. COuld not open dictionaryFile
 * 5. Could not open and read from file directory
 * 6. Brute force function could not get any matches..
 */
char *crack(const char *inputCodeFile, const char *keyFolder, const char *dictionaryFile, int *status){
    if(inputCodeFile == NULL || keyFolder == NULL || dictionaryFile == NULL) return NULL;

    *status = 0;
    int memoryError = 0;

    ArrayList wordList = new_array_list(DEFAULT_SIZE, &memoryError);
    String encodedText = new_string(DEFAULT_SIZE, &memoryError);
    String keyfiles = new_string(DEFAULT_SIZE, &memoryError);
    String crackedKey = new_string(DEFAULT_SIZE, &memoryError);

    if(memoryError){
        OUTPUT_ERROR("\nCould not allocate enough memory");
        on_error_decode_helper(&encodedText, &keyfiles, &crackedKey, &wordList);
        *status = 1;
        return NULL;
    }


    if(!read_dictionary_to_array_list(dictionaryFile, &wordList, status)){
        on_error_decode_helper(&encodedText, &keyfiles, &crackedKey, &wordList);
        return NULL;
    }


    if(!read_encoded_message_to_decode(inputCodeFile, &encodedText, status)){
        on_error_decode_helper(&encodedText, &keyfiles, &crackedKey, &wordList);
        return NULL;
    }


    if(!read_key_names_from_directory(keyFolder, &keyfiles, &memoryError)){
        on_error_decode_helper(&encodedText, &keyfiles, &crackedKey, &wordList);
        return NULL;
    }


    char *keyname = strtok(keyfiles.characters, "\n");
    if(keyname == NULL) {
        OUTPUT_ERROR("\nCrack function [Keyname splitting]: Could not get first keyfile from string.");
        on_error_decode_helper(&encodedText, &keyfiles, &crackedKey, &wordList);
        return NULL;
    }


    if(!brute_force_for_the_right_key(&crackedKey, keyname, &encodedText, &wordList, status)){
        on_error_decode_helper(&encodedText, &keyfiles, &crackedKey, &wordList);
        return NULL;
    }



    String keyString = new_string(DEFAULT_SIZE, &memoryError);
    if(!read_and_parse_key_file(crackedKey.characters, &keyString, status)){
        on_error_decode_helper(&encodedText, &keyfiles, &crackedKey, &wordList);
        free_string_memory(&keyString);
        return NULL;
    }



    String decodedText = new_string(DEFAULT_SIZE, &memoryError);
    if(!decode_string(&keyString, &encodedText, &decodedText, &memoryError)){
        on_error_decode_helper(&encodedText, &keyfiles, &crackedKey, &wordList);
        free_string_memory(&keyString);
        free_string_memory(&decodedText);
        return NULL;
    }


    OUTPUT_COMPLETE("Key:",crackedKey.characters);

    free_string_memory(&keyfiles);
    free_string_memory(&crackedKey);
    free_array_list_memory(&wordList);
    free_string_memory(&encodedText);
    free_string_memory(&keyString);


    return  decodedText.characters;
}



