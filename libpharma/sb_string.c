//
//  sb_string.c
//  PharmApp
//
//  Created by Braksa - Boutaib on 12/25/15.
//  Copyright © 2015 NSApps. All rights reserved.
//

#include "sb_string.h"

char* lower_string(char* string) {
    
    char* str = (char*)malloc(sizeof(char) * strlen(string));
    strcpy(str, string);
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
    return str;
    
}
