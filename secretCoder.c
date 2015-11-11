//
// Created by Hans Fredrik Brastad on 31/10/15.
//

#include "secretCoder.h"
#include <string.h>
#include "headers/string.h"
#include "headers/file_reader.h"
#include "headers/array_list.h"
#include "headers/search_util.h"


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



int check_word(String *pDecoded, ArrayList *words){

    for(int i = 0; i < pDecoded->used-1; i++){

        String word = new_string(2);
        while(char_lower(pDecoded->characters[i]) || char_upper(pDecoded->characters[i])){
            add_char(&word, tolower(pDecoded->characters[i]));
            i++;
        }

        if(word.used > 0){
            add_char(&word, '\0');
            binary_arraylist_search(words, word.characters);
        }

        free_string_memory(&word);
    }

    return 1;
}

char *crack(const char *inputCodeFile, const char * keyfolder, int *status){
    ArrayList wordList = new_array_list(2);
    read_dictionary("words", &wordList);

//    for(int i = 0; i < wordList.usedLength; i++){
//        printf("%s", wordList.strings[i].characters);
//    }


    String encodedText = new_string(2);
    if(!read_file(inputCodeFile, &encodedText, NORMAL)){
        *status = 1;
        return NULL;
    }


    String keyfiles = new_string(2);
    if(!read_directory(keyfolder, &keyfiles)){
        *status = 2;
        return NULL;
    }

    char *keyname = strtok(keyfiles.characters, "\n");
    if(keyname == NULL) {
        return NULL;
    }


    // -------------
    String stringKEy2 = new_string(2);


    if(!read_file("data/sweetChildGR.txt", &stringKEy2, KEY)){
        printf("Could not read keyname...");
    }



    String decodedText2 = new_string(2);
    decode_string(&stringKEy2, &encodedText, &decodedText2);

    check_word(&decodedText2, &wordList);
    printf("%s", decodedText2.characters);

    free_string_memory(&stringKEy2);
    free_string_memory(&decodedText2);
    //------------------


    // Add a String that holds the keyname here, and keep change it if the key is more likely right.

    // 4. Try decode the inputFile with everykey.

    while (keyname != NULL){

        if(strlen(keyname) > 7){

            String stringKey = new_string(2);

            if(!read_file(keyname, &stringKey, KEY)){
                printf("Could not read keyname...");
            }

//            printf("\n%s", keyname);
            String decodedText = new_string(2);
            decode_string(&stringKey, &encodedText, &decodedText);

            check_word(&decodedText, &wordList);


//            printf("\n%s ", decodedText.characters);


            free_string_memory(&decodedText);
            free_string_memory(&stringKey);
        }
        keyname = strtok(NULL, "\n");
    }

    free_string_memory(&keyfiles);
    free_string_memory(&encodedText);
    free_array_list_memory(&wordList);

    return  NULL;
}


