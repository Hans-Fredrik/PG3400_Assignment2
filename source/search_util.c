//
// Created by Hans Fredrik Brastad on 09/11/15.
//

#include <string.h>
#include "../headers/search_util.h"
#include "../headers/array_list.h"
#include "../headers/string.h"


int binary_arraylist_search(ArrayList * arrayList, char *target){

//    printf("\nBinary search: %s\n", target);


    int minIndex = 0;
    int maxIndex = arrayList->usedLength-1;
    int midIndex = 0;

    while (minIndex <= maxIndex){
        midIndex = (minIndex+maxIndex)/2;

        int res = strcmp(arrayList->strings[midIndex].characters, target);

        if(res < 0) {
            minIndex = minIndex +1;
        }
        else if(res > 0)
        {
            maxIndex = midIndex -1;
        }
        else{
            printf("[%s] str1 is equal to [%s] str2", arrayList->strings[midIndex].characters, target);
            return  1;
        }

    }

    return 0;
}

