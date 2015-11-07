//
// Created by Hans Fredrik Brastad on 31/10/15.
//

#include "secretCoder.h"
#include "headers/file_utility.h"
#include "headers/string.h"

char *encode(const char *inputMessageFile, const char *keyFile, int *status){
    String keyString = new_string(2);

    read_file(keyFile, &keyString, KEY);

    print_string(&keyString);


    printf("\nMessage: \n");
    String inputMessage = new_string(2);
    read_file(inputMessageFile, &inputMessage, NORMAL);
    print_string(&inputMessage);



    printf("\nEncoded message: \n");
    String encodeSting = new_string(2);
    encode_string(&keyString, &inputMessage,&encodeSting, 2);
    print_string(&encodeSting);
    write_to_file("encodedText.txt", &encodeSting);

    free_string_memory(&keyString);
    free_string_memory(&inputMessage);

    return encodeSting.characters;
}


char *decode(const char *inputCodeFile, const char *keyFile, int *status){

    String keyString = new_string(2);
    read_file(keyFile, &keyString, KEY);
    print_string(&keyString);


    printf("\nEncoded messsage from file: \n");
    String encodedFileText = new_string(2);
    read_file("encodedText.txt", &encodedFileText, NORMAL);
    print_string(&encodedFileText);


    printf("\nDecoded: \n");
    String decodedText = new_string(2);
    decode_string(&keyString, &encodedFileText, &decodedText);
    print_string(&decodedText);

    free_string_memory(&keyString);
    free_string_memory(&encodedFileText);


    return decodedText.characters;
}
