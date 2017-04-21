//
// Created by Hans Fredrik Brastad on 12/11/15.
//

#ifndef INNLEVERING2_ENCODE_DECODE_UTIL_H
#define INNLEVERING2_ENCODE_DECODE_UTIL_H


#include "../headers/string_util.h"
#include "../headers/file_reader.h"
#include "string.h"


int read_and_parse_key_file(const char *keyFile, String *keyString, int *status);


int read_the_message_to_encode(const char *inputMessageFile, String *inputString, int *status);


int encode_the_message_with_key(String *keyString, String *inputString, String *encodedString, const char *keyFile, int *status, int d);


int write_encoded_message_to_file(const char *outputFile, String *encodedString, int *status);


int read_encoded_message_to_decode(const char *inputCodeFile, String *encodedFileText, int *status);


int read_dictionary_to_array_list(const char *dictionaryFile, ArrayList *wordList, int *status);


int read_key_names_from_directory(const char *keyFolder, String *keyfiles, int *status);


int brute_force_for_the_right_key(String *crackedKey, char *keyname, String *encodedText, ArrayList *wordList, int *status);


#endif //INNLEVERING2_ENCODE_DECODE_UTIL_H
