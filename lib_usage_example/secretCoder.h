//
// Created by Hans Fredrik Brastad on 31/10/15.
//

#ifndef INNLEVERING2_SECRETCODER_H
#define INNLEVERING2_SECRETCODER_H



char *encode(const char *inputMessageFile, const char *keyFile, const char *outputFile, int *status, int d);

char *decode(const char *inputCodeFile, const char *keyFile, int *status);

char *crack(const char *inputCodeFile, const char *keyFolder, const char *dictionaryFile, int *status);



#endif //INNLEVERING2_SECRETCODER_H
