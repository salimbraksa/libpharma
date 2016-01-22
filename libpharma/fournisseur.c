//
//  fournisseur.c
//  PharmApp
//
//  Created by Braksa - Boutaib on 12/17/15.
//  Copyright © 2015 NSApps. All rights reserved.
//

#include "fournisseur.h"

// Helpers Prototypes

void set_fournisseur_data(Fournisseur* fournisseur, char* nom, char* email, char* telephone);

// Implémentation des fonctions

Fournisseur* create_fournisseur(char* nom, char* email, char* telephone) {
    
    // Alloc new Fournisseur
    Fournisseur* fournisseur = (Fournisseur* )malloc(sizeof(Fournisseur));
    
    // Set it's properties
    set_fournisseur_data(fournisseur, nom, email, telephone);
    
    // Return
    return fournisseur;
    
}

void edit_fournisseur(Fournisseur* fournisseur, char* nom, char* email, char* telephone) {
    set_fournisseur_data(fournisseur, nom, email, telephone);
}

// Helpers

void set_fournisseur_data(Fournisseur* fournisseur, char* nom, char* email, char* telephone) {
    
    // Copie nom & email, telephone
    char* copied_nom = (char*)malloc(sizeof(char) * strlen(nom));
    char* copied_email = (char*)malloc(sizeof(char) * strlen(email));
    char* copied_telephone = (char*)malloc(sizeof(char) * strlen(telephone));
    strcpy(copied_nom, nom);
    strcpy(copied_email, email);
    strcpy(copied_telephone, telephone);
    
    strcpy(fournisseur -> nom, copied_nom);
    strcpy(fournisseur -> email, copied_email);
    strcpy(fournisseur -> telephone, copied_telephone);
    
}