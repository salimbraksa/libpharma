//
//  fournisseur.h
//  PharmApp
//
//  Created by Braksa - Boutaib on 12/17/15.
//  Copyright © 2015 NSApps. All rights reserved.
//

#ifndef fournisseur_h
#define fournisseur_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Définition de la structure Fournisser
typedef struct {
    
    long int fournisseur_id;
    char nom[80];
    char email[100];
    char telephone[11];
    
} Fournisseur;

/// Permet de créer un nouveau Fournisseur
Fournisseur* create_fournisseur(char* nom,
                               char* email,
                               char* telephone);

/// Permet de modifier les informations d'un fournisseur
void edit_fournisseur(Fournisseur* fournisseur,
                          char* nom,
                          char* email,
                          char* telephone);

#endif /* fournisseur_h */
