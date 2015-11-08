//
// Created by Hans Fredrik Brastad on 31/10/15.
//

#include "secretCoder.h"
#include "headers/file_utility.h"

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
    String inputMessage = new_string(DEFAULT_SIZE);

    if(!read_file(inputMessageFile, &inputMessage, NORMAL)){
        printf("\nEncode function error: could not open inputMessageFile.\n");
        free_string_memory(&inputMessage);
        free_string_memory(&keyString);
        *status = 2;
        return NULL;
    }

    print_string(&inputMessage);



    printf("\nEncoded message: \n");
    String encodedString = new_string(DEFAULT_SIZE);

    if(!encode_string(&keyString, &inputMessage,&encodedString, 2)){
        printf("\nEncode function error: Could not encode with the keyfile. Missing characters...\n");
        free_string_memory(&encodedString);
        free_string_memory(&keyString);
        free_string_memory(&inputMessage);

        *status = 3;
        return NULL;
    }

    print_string(&encodedString);

    free_string_memory(&keyString);
    free_string_memory(&inputMessage);

    if(!write_to_file(outputFile, &encodedString)){
        printf("\nEncode function: could not save to file[%s] need atleast 1 char.\n", outputFile);
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
