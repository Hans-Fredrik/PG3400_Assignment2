//
// Created by Hans Fredrik Brastad on 31/10/15.
//

#include "program.h"
#include "source/array.h"


int main(int argc, char *argv[]){

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
    free_string_memory(&keyString);


    Map map = new_map(25);

    Item charItem = {.key = 'A', .value = new_array(2)};

    put(&map, charItem);

    free_map_memory(&map);

    Array array = new_array(2);

    free_array_memory(&array);
    return 0;
}