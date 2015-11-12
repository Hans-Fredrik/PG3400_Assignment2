//
// Created by Hans Fredrik Brastad on 31/10/15.
//


#include "program.h"



int main(int argc, char *argv[]){

    // Tester ut de Ordentlige secretCoder funksjonene..

    int status = -1;

    char *encodedText = encode("inputMessage.txt", "data/sweetChildGR.txt", "encodedText.txt", &status, 2);

    printf("\nEncodedtext: \n %s", encodedText);

    free(encodedText);

    printf("\n\nSTATUS IS : %d" , status);

    /*
    char *decodedText = decode("encodedText.txt", "data/sweetChildGR.txt", &status);

    free(decodedText);


    char * decodedText2 = crack("encodedText.txt", "data/" , &status);
    free(decodedText2);*/


    return 0;
}