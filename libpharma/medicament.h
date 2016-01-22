//
//  medicament.h
//  PharmApp
//
//  Created by Braksa - Boutaib on 12/21/15.
//  Copyright © 2015 NSApps. All rights reserved.
//

#ifndef Medicament_h
#define Medicament_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMUM_FOURNISSEURS 10

/// Définition de la structure Medicament
typedef struct {
    
    long int medicament_id;
    char nom[80];
    char description[201];
    int quantite;
    double prix;
    int seuil;
    
    int nombre_fournisseurs;
    long int default_fournisseur_id;
    int fournisseurs_ids[MAXIMUM_FOURNISSEURS];
    
} Medicament;

/// Permet de créer un nouveau Medicament
Medicament* create_medicament(char* nom,
                              char* description,
                              double prix,
                              int quantite,
                              int seuil,
                              int nombre_fournisseurs,
                              long int default_fournissur_id,
                              int fournisseurs_ids[MAXIMUM_FOURNISSEURS]);

/// Permet de modifier un Médicament
void modifier_medicament(Medicament* medicament,
                         char* nom,
                         char* description,
                         double prix,
                         int quantite,
                         int seuil,
                         int nombre_fournisseurs,
                         long int default_fournisseur_id,
                         int fournisseurs_ids[MAXIMUM_FOURNISSEURS]);

/// Permet de vérifier si un fournisseur donné est vraiment un fournisseur du médicament
int is_fournisseur_of_medicament(Medicament* medicament, long int fournisseur_id);

/// Permet de modifier le fournisseur par défault du médicament
void edit_medicament_fournisseur(Medicament* medicament, long int fournisseur_id);

#endif /* Medicament_h */
