//
// Created by Hans Fredrik Brastad on 13/11/15.
//

#include <stdlib.h>
#include <stdio.h>
#include "secretCoder.h"

int main(int argc, char *argv[]){

    int status = 99;

    char *encodedText = encode("inputMessage.txt", "../keys/sweetChildGR.txt", "encodedText.txt", &status, 2);

    printf("EncodedMessage: %s\n", encodedText);

    free(encodedText);


    char *decodedText = decode("encodedText.txt", "../keys/sweetChildGR.txt", &status);

    printf("\nDecoedMessage: %s\n", decodedText);

    free(decodedText);



    char * decodedText2 = crack("encodedText.txt", "keys/", "../words", &status);

    printf("\nCracked DecoedMessage: %s\n", decodedText2);


    free(decodedText2);

    return 0;
}

