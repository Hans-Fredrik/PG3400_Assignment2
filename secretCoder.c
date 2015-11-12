//
// Created by Hans Fredrik Brastad on 31/10/15.
//

#include "secretCoder.h"
#include <string.h>
#include "headers/string.h"
#include "headers/file_reader.h"
#include "headers/string_util.h"
#include "headers/crack_util.h"


static const int DEFAULT_SIZE = 2;


char *encode(const char *inputMessageFile, const char *keyFile, const char *outputFile, int *status){
    if(inputMessageFile == NULL || keyFile == NULL || outputFile == NULL) return NULL;

    String keyString = new_string(DEFAULT_SIZE);
    if(!read_file(keyFile, &keyString, KEY)){
        printf("\nEncode function error: could not open keyfile.\n");
        free_string_memory(&keyString);
        *status = 1;
        return NULL;
    }

    print_string(&keyString);


    printf("\nMessage: \n");
    String inputString = new_string(DEFAULT_SIZE);
    if(!read_file(inputMessageFile, &inputString, NORMAL)){
        printf("\nEncode function error: could not open inputMessageFile.\n");
        free_string_memory(&inputString);
        free_string_memory(&keyString);
        *status = 2;
        return NULL;
    }

    print_string(&inputString);



    printf("\nEncoded message: \n");
    String encodedString = new_string(DEFAULT_SIZE);
    if(!encode_string(&keyString, &inputString,&encodedString, 1)){
        printf("\nEncode function error: Could not encode with the keyfile. Missing characters...\n");
        free_string_memory(&encodedString);
        free_string_memory(&keyString);
        free_string_memory(&inputString);

        *status = 3;
        return NULL;
    }

    print_string(&encodedString);

    free_string_memory(&keyString);
    free_string_memory(&inputString);

    if(!write_to_file(outputFile, &encodedString)){
        printf("\nEncode function: could not save to file[%s] output filename need atleast 1 to be char.\n", outputFile);
    }
    
    return encodedString.characters;
}


char *decode(const char *inputCodeFile, const char *keyFile, int *status){
    if(inputCodeFile == NULL || keyFile == NULL) return NULL;

    String keyString = new_string(DEFAULT_SIZE);
    read_file(keyFile, &keyString, KEY);
    print_string(&keyString);


    printf("\nEncoded messsage from file: \n");
    String encodedFileText = new_string(DEFAULT_SIZE);
    read_file("encodedText.txt", &encodedFileText, NORMAL);
    print_string(&encodedFileText);


    printf("\nDecoded: \n");
    String decodedText = new_string(DEFAULT_SIZE);
    decode_string(&keyString, &encodedFileText, &decodedText);
    print_string(&decodedText);

    free_string_memory(&keyString);
    free_string_memory(&encodedFileText);


    return decodedText.characters;
}


char *crack(const char *inputCodeFile, const char *keyFolder, int *status){
    ArrayList wordList = new_array_list(2);
    read_dictionary("words", &wordList);


    String encodedText = new_string(2);
    if(!read_file(inputCodeFile, &encodedText, NORMAL)){
        *status = 1;
        return NULL;
    }

    String keyfiles = new_string(2);
    if(!read_directory(keyFolder, &keyfiles)){
        *status = 2;
        return NULL;
    }

    char *keyname = strtok(keyfiles.characters, "\n");
    if(keyname == NULL) {
        return NULL;
    }

    String crackedKey = new_string(2);

    if(!brute_force_right_key(&crackedKey, keyname, &encodedText, &wordList)){

    }

    String decodedText = new_string(2);
    decode_string(&crackedKey, &encodedText, &decodedText);

    printf("Key: ");
    COMPLETE_OUTPUT(crackedKey.characters);

    free_string_memory(&keyfiles);
    free_string_memory(&encodedText);
    free_string_memory(&crackedKey);
    free_array_list_memory(&wordList);


    return  decodedText.characters;
}



