//
// Created by Hans Fredrik Brastad on 31/10/15.
//

#ifndef INNLEVERING2_SECRETCODER_H
#define INNLEVERING2_SECRETCODER_H



/*
 * 1. Memory error
 * 2. Keyfile errror
 * 3. Inputfilemessage error
 * 4. Could not satisfy d condition
 * 5. Keyfile does not have a-z
 * 6. Could write to outputFile, name can't be blank
 */
char *encode(const char *inputMessageFile, const char *keyFile, const char *outputFile, int *status, int d);


/*
 * 1 -> means memory issue (Most likely not going to happen but can)
 * 2 -> Could nopen open and read keyfile
 * 3 -> Could not open and read encoded message file
 */

char *decode(const char *inputCodeFile, const char *keyFile, int *status);


/*
 * 1. Memory error
 * 2. Could not open keyfile
 * 3. COuld not read inputCodeFile
 * 4. COuld not open dictionaryFile
 * 5. Could not open and read from file directory
 * 6. Brute force function could not get any matches..
 */
char *crack(const char *inputCodeFile, const char *keyFolder, const char *dictionaryFile, int *status);



#endif //INNLEVERING2_SECRETCODER_H
