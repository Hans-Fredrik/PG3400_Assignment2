//
// Created by Hans Fredrik Brastad on 31/10/15.
//

#include "program.h"
#include "headers/map.h"
#include "headers/array.h"


int main(int argc, char *argv[]){

    // Tester ut de Ordentlige secretCoder funksjonene..

    int status = 99;

    char *encodedText = encode("inputMessage.txt", "data/sweetChildGR.txt", "encodedText.txt", &status);

    free(encodedText);


    char *decodedText = decode("encodedText.txt", "data/sweetChildGR.txt", &status);

    free(decodedText);


    crack("encodedText.txt","data/", &status);

    return 0;
}