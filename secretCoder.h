//
// Created by Hans Fredrik Brastad on 31/10/15.
//

#ifndef INNLEVERING2_SECRETCODER_H
#define INNLEVERING2_SECRETCODER_H

/*
 * Note! The client should handle the status message and(or) at least check for NULL when using this library.
 * Example give in example usage is just simplified.
 */


/*
 * Parameters:
 * - inputMessageFile (not NULL) file name for message to encode
 * - keyFile (not NULL) file name for key
 * - outputFile (not NULL) file name for the encoded output (If not exists file will be created)
 * - status will contain int from 0-6
 * - d numbers of units for adjacent codes
 * _______________________________________________________________________________________________________
 * Status:
 * 0. No errors
 * 1. memory error
 * 2. keyfile errror
 * 3. inputMessageFile error
 * 4. Could not satisfy d condition (It must be atleast a 80% worstcase match for encoding to be done)
 * 5. Keyfile does not have a-z
 * 6. outputfile is blank
 * _______________________________________________________________________________________________________
 * Return:
 * Function return the encoded message as char *, the function may return NULL.
 * _______________________________________________________________________________________________________
 * Example usage:
 * char *encodedText = encode("inputMessage.txt", "keys/sweetChildGR.txt", "encodedText.txt", &status, 2);
 * free(encodedText);
 */
char *encode(const char *inputMessageFile, const char *keyFile, const char *outputFile, int *status, int d);


/*
 * Parameters:
 * - inputCodeFile (not NULL) name of encoded file
 * - keyFile (not NULL) name of keyfile to use
 * - status will contain int from 0-3
 * _______________________________________________________________________
 * Status:
 * 0. No errors
 * 1. memory error (not enough memory)
 * 2. Could not open and read keyfile
 * 3. Could not open and read encoded message file
 * _______________________________________________________________________
 * Return:
 * Function return decoded message as char *, may return NULL.
 * _______________________________________________________________________
 * Example usage:
 * char *decodedText = decode("encodedText.txt", "keys/sweetChildGR.txt", &status);
 * free(decodedText);
 */
char *decode(const char *inputCodeFile, const char *keyFile, int *status);


/*
 * Parameters:
 * - inputCodeFile (not NULL) name of encoded file
 * - keyFolder (NOT NULL) name of directory where your keys are
 * - dictionaryFile name of the dictionaryfile
 * - status will contain int from 0-6
 * _____________________________________________________________________________________________________
 * Status:
 * 1. Memory error
 * 2. Could not open keyfile
 * 3. Could not read inputCodeFile
 * 4. Could not open dictionaryFile
 * 5. Could not open and read from file directory
 * 6. Brute force function could not get any matches..
 * _____________________________________________________________________________________________________
 * Return:
 * Function return the crackedMessage as char * and output the key. May return NULL.
 * _____________________________________________________________________________________________________
 * Example usage:
 * char * decodedText2 = crack("encodedText.txt", "keys/", "../words", &status);
 * free(decodedText2);
 */
char *crack(const char *inputCodeFile, const char *keyFolder, const char *dictionaryFile, int *status);



#endif //INNLEVERING2_SECRETCODER_H
