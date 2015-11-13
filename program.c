//
// Created by Hans Fredrik Brastad on 31/10/15.
//


#include "program.h"
#include "headers/string.h"


int main(int argc, char *argv[]){

    int status = -1;

    char *encodedText = encode("inputMessage.txt", "data/sweetChildGR.txt", "encodedText.txt", &status, 2);

    printf("\nEncodedtext: \n %s", encodedText);

    free(encodedText);


    char *decodedText = decode("encodedText.txt", "badkey", &status);

    printf("\nDecodedtext: \n %s", decodedText);

    free(decodedText);

    /*
    char * decodedText2 = crack("encodedText.txt", "data/", "words", &status);
    printf("\nCracked decoedText2: \n%s", decodedText2);
    free(decodedText2);
*/
    return 0;
}