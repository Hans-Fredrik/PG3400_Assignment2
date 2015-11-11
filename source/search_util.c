//
// Created by Hans Fredrik Brastad on 09/11/15.
//

#include <string.h>
#include "../headers/search_util.h"


int binary_arraylist_search(ArrayList * arrayList, char *target){

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
            return  1;
        }

    }

    return 0;
}

