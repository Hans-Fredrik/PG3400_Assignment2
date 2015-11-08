//
// Created by Hans Fredrik Brastad on 31/10/15.
//

#include "program.h"
#include "headers/map.h"
#include "headers/array.h"


int main(int argc, char *argv[]){

    // Tester ut de Ordentlige secretCoder funksjonene..

    int status = 99;
/*
    char *encodedText = encode("inputMessage.txt", "data/sweetChildGR.txt", "encodedText.txt", &status);

    free(encodedText);


    char *decodedText = decode("encodedText.txt", "data/sweetChildGR.txt", &status);

    free(decodedText);*/



    char *encodedText2 = encode("inputMessage.txt", "data/sweetChildGR.txt", "encodedText.txt", &status);

    printf("\nHere: %s \n", encodedText2);

    free(encodedText2);

    printf("\nMessage: %d", status);



    // ------- Testing slutt ---------------------------

    /* --- BRUKES TIL DEBUGGING, SPARES TIL RETT FØR INNLEVERING HANDY JA
    printf("Key: \n");
    String keyString = new_string(2);
    read_file("data/sweetChildGR.txt", &keyString, KEY);
    print_string(&keyString);


    printf("\nMessage: \n");
    String inputMessage = new_string(2);
    read_file("inputMessage.txt", &inputMessage, NORMAL);
    print_string(&inputMessage);



    printf("\nEncoded message: \n");
    String encodeSting = new_string(2);
    encode_string(&keyString, &inputMessage,&encodeSting, 2);
    print_string(&encodeSting);
    write_to_file("encodedText.txt", &encodeSting);


    printf("\nEncoded messsage from file: \n");
    String encodedFileText = new_string(2);
    read_file("encodedText.txt", &encodedFileText, NORMAL);
    print_string(&encodedFileText);


    printf("\nDecoded: \n");
    String decodedText = new_string(2);
    decode_string(&keyString, &encodedFileText, &decodedText);
    print_string(&decodedText);


    free_string_memory(&inputMessage);
    free_string_memory(&encodeSting);
    free_string_memory(&encodedFileText);
    free_string_memory(&decodedText);


    Map map = create_char_index_map(&keyString);


    for(int i = 0; i < map.used; i++){
        printf("\nKey: %c  | ", map.items[i].key);
        printf("Values: ");
        for(int x = 0; x < map.items[i].value.usedLength; x++){
            printf(" [%d] ", map.items[i].value.numbers[x]);
        }
    }

    free_map_memory(&map);
    free_string_memory(&keyString);

    */


    return 0;
}