//
// Created by Hans Fredrik Brastad on 06/11/15.
//

#ifndef INNLEVERING2_STRING_UTIL_H
#define INNLEVERING2_STRING_UTIL_H

#define KNRM  "\x1B[0m"     //??
#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE  "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CYAN  "\x1B[36m"
#define WHITE  "\x1B[37m"
#define RESET "\033[0m"

#define ERROR(X) printf("%s %s %s", RED, X, RESET)
#define GREEN_TXT(X) printf("%s %s %s", GREEN, X, RESET)



#endif //INNLEVERING2_STRING_UTIL_H
