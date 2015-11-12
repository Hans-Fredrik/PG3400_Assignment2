//
// Created by Hans Fredrik Brastad on 12/11/15.
//

#include "../headers/encode_decode_util.h"

int read_and_parse_key_file(const char *keyFile, String *keyString, int *status){
    int memoryError = 0;

    int readKeyFileResult = read_file(keyFile, keyString, KEY, &memoryError);

    if(!readKeyFileResult || memoryError){
        if(memoryError){
            OUTPUT_ERROR("\nCould not allocate enough memory");
            *status = 1;
        }else{
            OUTPUT_FILE_ERROR("\nEncode function error: could not open keyfile", keyFile);
            *status = 2;
        }
        return 0;
    }

    return 1;
}


int read_the_message_to_encode(const char *inputMessageFile, String *inputString, int *status){
    int memoryError = 0;

    int readInputMessageResult = read_file(inputMessageFile, inputString, NORMAL, &memoryError);

    if(!readInputMessageResult || memoryError){
        if(memoryError){
            OUTPUT_ERROR("\nCould not allocate enough memory");
            *status = 1;
        }else{
            OUTPUT_FILE_ERROR("\nEncode function error: could not open inputMessageFile", inputMessageFile);
            *status = 3;
        }

        return 0;
    }

    return 1;
}


int encode_the_message_with_key(String *keyString, String *inputString, String *encodedString, const char *keyFile, int *status, int d){
    int memoryError = 0;

    int encodeMessageWithKeyResult = encode_string(keyString, inputString,encodedString, d, &memoryError);

    if(!encodeMessageWithKeyResult || memoryError){
        if(memoryError){
            OUTPUT_ERROR("\nCould not allocate enough memory");
            *status = 1;
        }else{
            OUTPUT_FILE_ERROR("\nEncode function error: Could not encode with the keyfile. Missing characters[a-z is must] in", keyFile);
            *status = 4;
        }

        return 0;
    }

    return 1;
}


int write_encoded_message_to_file(const char *outputFile, String *encodedString, int *status){

    int writeEncodedMessageResult =  write_to_file(outputFile, encodedString);

    if(!writeEncodedMessageResult){
        OUTPUT_FILE_ERROR("\nEncode function: output filename need to be atleast 1 char long, could not save to file ", outputFile);
        *status = 5;
        return  0;
    }

    return 1;
}


int read_encoded_message_to_decode(const char *inputCodeFile, String *encodedFileText, int *status){

    int memoryError = 0;

    int readFileEncodedResult = read_file(inputCodeFile, encodedFileText, NORMAL, &memoryError);


    if(!readFileEncodedResult || memoryError){

        if(memoryError){
            OUTPUT_ERROR("\nCould not allocate enough memory");
            *status = 1;
        }else{
            OUTPUT_FILE_ERROR("\nDecode function error: could not open encoded message file ", inputCodeFile);
            *status = 2;
        }
        return 0;
    }

    return 1;
}