//
// Created by Hans Fredrik Brastad on 31/10/15.
//


#include "unit_test.h"
#include "headers/string.h"


int main(int argc, char *argv[]){
    // Satus used for all tests
    int status = 0;


    // Testing encode function
    printf("\nTesting if input message param is NULL is handled:  ");
    char *expectNullWhen1ParamIsNull = encode(NULL, "keys/sweetChildGR.txt", "encodedText.txt", &status, 2);
    printf("\nexpectNullWhen1ParamIsNull is: %s expcted null\n", expectNullWhen1ParamIsNull);


    printf("\nTesting if keyfile param is NULL is handled:  ");
    char *expectNullWhen2ParamIsNull = encode("encodedText.txt", NULL, "encodedText.txt", &status, 2);
    printf("\nexpectNullWhen2ParamIsNull is: %s expcted null\n", expectNullWhen2ParamIsNull);


    printf("\nTesting if outputfile param is NULL is handled:  ");
    char *expectNullWhen3ParamIsNull = encode("encodedText.txt", "keys/sweetChildGR.txt", NULL, &status, 2);
    printf("\nexpectNullWhen3ParamIsNull is: %s expcted null\n", expectNullWhen3ParamIsNull);


    printf("\nTesting if all params is NULL is handled:  ");
    char *expectNullWhenAllParamIsNull = encode(NULL, NULL, NULL, &status, 2);
    printf("\nexpectNullWhenAllParamIsNull is: %s expcted null\n", expectNullWhenAllParamIsNull);



    // Testing encode function
    printf("\nTesting if blank input message file is handled:  ");
    char *expectInputMessageFileError = encode("", "keys/sweetChildGR.txt", "encodedText.txt", &status, 2);
    printf("\nThe expectInputMessageFileError is: %s expected null and status is: %d expected 3\n", expectInputMessageFileError, status);


    printf("\nTesting if blank input keyfile is handled:  ");
    char *expectKeyFileError = encode("encodedText.txt", "", "encodedText.txt", &status, 2);
    printf("\nThe expectKeyFileError is: %s expected null and status is: %d expected 2\n", expectKeyFileError, status);


    printf("\nTesting if blank input keyfile is handled:  ");
    char *expectCouldNotWriteToFIleError = encode("encodedText.txt", "keys/sweetChildGR.txt", "", &status, 2);
    printf("\nThe expectCouldNotWriteToFIleError is: %s expected null and status is: %d expected 6\n", expectCouldNotWriteToFIleError, status);


    printf("\nTesting if very high D condition handled:  ");
    char *expectNotSatisfyingDCon = encode("encodedText.txt", "keys/sweetChildGR.txt", "encodedText.txt", &status, 2000);
    printf("\nThe expectNotSatisfyingDCon is: %s expected null and status is: %d expected 4\n", expectNotSatisfyingDCon, status);


    // Testing encode function
    printf("\nTesting that program can handle badkey:  ");
    char *expectNotCompleteKeyFile = encode("encodedText.txt", "badkey", "encodedText.txt", &status, 2);
    printf("\nThe expectNotCompleteKeyFile is: %s expected null and status is: %d expected 5\n", expectNotCompleteKeyFile, status);
    free(expectNotCompleteKeyFile);



    // Testing decode function
    printf("\nTesting that encode can handle null params:  ");
    char *expectNullWhenParamIsNull = decode(NULL, "", NULL);
    printf("\nThe expectNullWhenParamIsNull is: %s expected null\n", expectNullWhenParamIsNull);


    printf("\nTesting that encode can handle badkey:  ");
    char *expectKeyFileErrorDecode = decode("encodedText.txt", "", &status);
    printf("\nThe expectKeyFileErrorDecode is: %s expected null and status is: %d expected 2\n", expectKeyFileErrorDecode, status);

    printf("\nTesting that encode can handle missing input file:  ");
    char *expectInputFileErrorDecode = decode("", "keys/sweetChildGR.txt", &status);
    printf("\nThe expectInputFileErrorDecode is: %s expected null and status is: %d expected 3\n", expectInputFileErrorDecode, status);




    // Testing crack funciton for most cases
    printf("\nTesting that crack function can handle null params:  ");
    char * expectNullFromCrack = crack(NULL, NULL, NULL, &status);
    printf("\nThe expectNullFromCrack is: %s expected null\n", expectNullFromCrack);


    printf("\nTesting that crack can handle missing input file:  ");
    char *expectInputFileErrorCrack= crack("", "keys/", "words", &status);
    printf("\nThe expectInputFileErrorCrack is: %s expected null and status is: %d expected 3\n", expectInputFileErrorCrack, status);


    printf("\nTesting that crack can handle missing wrong directory:  ");
    char *expectDirectoryErrorCrack= crack("encodedText.txt", "sdfszfdaf", "words", &status);
    printf("\nThe expectDirectoryErrorCrack is: %s expected null and status is: %d expected 5\n", expectDirectoryErrorCrack, status);



    // Showing expect behaviour
    char *encodedText = encode("inputMessage.txt", "keys/sweetChildGR.txt", "encodedText.txt", &status, 2);

    printf("EncodedMessage: %s\n", encodedText);

    free(encodedText);


    char *decodedText = decode("encodedText.txt", "keys/sweetChildGR.txt", &status);

    printf("\nDecoedMessage: %s\n", decodedText);

    free(decodedText);



    char * decodedText2 = crack("encodedText.txt", "keys/", "words", &status);

    printf("\nCracked DecoedMessage: %s\n", decodedText2);

    free(decodedText2);

    return 0;
}