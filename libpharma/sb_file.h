//
//  sb_file.h
//  PharmApp
//
//  Created by Salim Braksa on 12/30/15.
//  Copyright © 2015 Braksa Salim. All rights reserved.
//

#ifndef sb_file_h
#define sb_file_h

#include <stdio.h>

/// Permet de créer un fichier si ce dernier n'existe pas
int file_exist(char* filepath);

/// Permet de créer un fichier
void create_file(char* filepath);

#endif /* sb_file_h */
