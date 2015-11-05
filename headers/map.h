//
// Created by Hans Fredrik Brastad on 04/11/15.
//

#ifndef INNLEVERING2_MAP_H
#define INNLEVERING2_MAP_H

typedef struct{
    char    key;
    int     *values;
}Item;

typedef struct{
    Item items[25];
}Map;



#endif //INNLEVERING2_MAP_H
