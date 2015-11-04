//
// Created by Hans Fredrik Brastad on 31/10/15.
//

#include <string.h>
#include "program.h"
#include "headers/arraylist.h"


int main(int argc, char *argv[]){

    //Viser en mer lett lest måte å gjøre det på
    String keyString = new_string(2);
    read_file("data/sweetChildGR.txt", &keyString, KEY);
    print_string(&keyString);


    String inputMessage = new_string(2);
    read_file("inputMessage.txt", &inputMessage, NORMAL);
    print_string(&inputMessage);



    // ENCODE part..
    String encodeSting = new_string(2);
    encode_string(&keyString, &inputMessage,&encodeSting, 2);
    print_string(&encodeSting);
    write_to_file("encodedText.txt", &encodeSting);


    // Read encoded.txt
    printf("\n\n\n ");
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
    return 0;
}