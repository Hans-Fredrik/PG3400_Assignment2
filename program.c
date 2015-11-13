//
// Created by Hans Fredrik Brastad on 31/10/15.
//


#include "program.h"
#include "headers/string.h"


int main(int argc, char *argv[]){

    // Test case
    int status = -1;


    char *encodedText = encode("inputMessage.txt", "data/sweetChildGR.txt", "encodedText.txt", &status, 250);


    printf("\nEncodedtext: \n %s", encodedText);

    free(encodedText);


    status = -1;

    char *decodedText = decode("encodedText.txt", "data/sweetChildGR.txt", &status);

    printf("\nDecodedtext: \n %s", decodedText);

    free(decodedText);



    char * decodedText2 = crack("encodedText.txt", "data/", "words", &status);
    printf("\nCracked decoedText2: \n%s", decodedText2);
    free(decodedText2);


    return 0;
}