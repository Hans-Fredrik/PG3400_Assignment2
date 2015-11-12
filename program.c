//
// Created by Hans Fredrik Brastad on 31/10/15.
//


#include "program.h"



int main(int argc, char *argv[]){

    // Tester ut de Ordentlige secretCoder funksjonene..

    int status = -1;


    /*
    char *encodedText = encode("inputMessage.txt", "data/sweetChildGR.txt", "encodedText.txt", &status, 2);

    printf("\nEncodedtext: \n %s", encodedText);

    free(encodedText); */


    char *decodedText = decode("encodedText.txt", "data/sweetChildGR.txt", &status);

    printf("\nDecodedtext: \n %s", decodedText);

    free(decodedText);


/*
    char * decodedText2 = crack("encodedText.txt", "data/" , &status);
    printf("\nCracked decoedText2: \n%s", decodedText2);
    free(decodedText2);
*/

    return 0;
}