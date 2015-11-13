//
// Created by Hans Fredrik Brastad on 12/11/15.
//

#include "../headers/exception_handler.h"
#include "../headers/crack_util.h"

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

    if(encodeMessageWithKeyResult != 1 || memoryError){
        if(memoryError){
            OUTPUT_ERROR("\nCould not allocate enough memory");
            *status = 1;
        }else if(encodeMessageWithKeyResult == 3){
            OUTPUT_D_ERROR("\nAborting encoding, could not satifsy d", d);
            *status = 4;
        }
        else {
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
        *status = 6;
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
            *status = 3;
        }
        return 0;
    }

    return 1;
}

int read_dictionary_to_array_list(const char *dictionaryFile, ArrayList *wordList, int *status){
    int memoryError = 0;

    int readDictionaryStatus = read_dictionary(dictionaryFile, wordList, &memoryError);
    if(!readDictionaryStatus || memoryError){
        if(memoryError){
            OUTPUT_ERROR("\nCould not allocate enough memory");
            *status = 1;
        }else{
            OUTPUT_FILE_ERROR("\nCrack function error: could not open and read file", dictionaryFile);
            *status = 7;
        }

        return 0;
    }

    return 1;
}


int read_key_names_from_directory(const char *keyFolder, String *keyfiles, int *status){
    int memoryError = 0;

    int readKeysInDirectoryResult = read_directory(keyFolder, keyfiles, &memoryError);

    if(!readKeysInDirectoryResult || memoryError){
        if(memoryError){
            OUTPUT_ERROR("\nCould not allocate enough memory");
            *status = 1;
        }else{
            OUTPUT_FILE_ERROR("\nCrack function error: could not open and read file(directory)", keyFolder);
            *status = 8;
        }

        return 0;
    }

    return 1;
}


int brute_force_for_the_right_key(String *crackedKey, char *keyname, String *encodedText, ArrayList *wordList, int *status){
    int memoryError = 0;

    int bruteForceRightKeyResult = brute_force_right_key(crackedKey, keyname, encodedText, wordList, &memoryError);

    if(!bruteForceRightKeyResult || memoryError){
        if(memoryError){
            OUTPUT_ERROR("\nCould not allocate enough memory");
            *status = 1;
        }else{
            OUTPUT_FILE_ERROR("\nBrute force function error: Could not get any matches!", keyname);
            *status = 9;
        }

        return 0;
    }

    return 1;
}
