//
//  sb_file.c
//  PharmApp
//
//  Created by Salim Braksa on 12/30/15.
//  Copyright © 2015 Braksa Salim. All rights reserved.
//

#include "sb_file.h"

int file_exist(char* filepath) {
    
    // Try to read file
    FILE* file = fopen(filepath, "r");
    
    // Close it
    fclose(file);
    
    // Return success
    return ( file == NULL) ? 0 : 1;
    
}

void create_file(char* filepath) {
    
    // Open file ( creating it )
    FILE* file = fopen(filepath, "ab");
    
    // Close
    fclose(file);
    
}