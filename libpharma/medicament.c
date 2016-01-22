//
//  medicament.c
//  PharmApp
//
//  Created by Braksa - Boutaib on 12/21/15.
//  Copyright © 2015 NSApps. All rights reserved.
//

#include "Medicament.h"

void set_medicament_data(Medicament* medicament,
                         char* nom,
                         char* description,
                         double prix,
                         int quantite,
                         int seuil,
                         int nombre_fournisseurs,
                         long int default_fournisseur_id,
                         int fournisseurs_ids[MAXIMUM_FOURNISSEURS]);

// Implémentation des fonctions

Medicament* create_medicament(char* nom, char* description, double prix, int quantite, int seuil, int nombre_fournisseurs, long int default_founrnisseur_id, int fournisseurs_ids[MAXIMUM_FOURNISSEURS]) {
    
    // Alloc new Medicament
    Medicament* medicament = (Medicament *)malloc(sizeof(Medicament));
    
    // Set properties
    medicament -> medicament_id = -1;
    set_medicament_data(medicament, nom, description, prix, quantite, seuil, nombre_fournisseurs, default_founrnisseur_id, fournisseurs_ids);
    
    // Return
    return medicament;
    
}

void modifier_medicament(Medicament* medicament, char* nom, char* description, double prix, int quantite, int seuil, int nombre_fournisseurs, long int default_fournisseur_id, int fournisseurs_ids[MAXIMUM_FOURNISSEURS]) {
    
    // Set medicament data
    set_medicament_data(medicament, nom, description, prix, quantite, seuil, nombre_fournisseurs, default_fournisseur_id, fournisseurs_ids);
    
}

int is_fournisseur_of_medicament(Medicament* medicament, long int fournisseur_id) {
    
    for (int i = 0; i < medicament->nombre_fournisseurs; i++) {
        if ((medicament->fournisseurs_ids)[i] == fournisseur_id) return 1;
    }
    return 0;
    
}

void edit_medicament_fournisseur(Medicament* medicament, long int fournisseur_id) {
    
    // Si ce fournisseur ne figure pas dans la liste des fournisseur de ce medicament
    if (!is_fournisseur_of_medicament(medicament, fournisseur_id)) return;
    
    // Sinon
    medicament -> default_fournisseur_id = fournisseur_id;
    
}

// Helpers

void set_medicament_data(Medicament* medicament, char* nom, char* description, double prix, int quantite, int seuil, int nombre_fournisseurs, long int default_fournisseur_id, int fournisseurs_ids[MAXIMUM_FOURNISSEURS]) {
    
    // Copie nom & description
    char* copied_nom = (char*)malloc(sizeof(char) * strlen(nom));
    char* copied_description = (char*)malloc(sizeof(char) * strlen(description));
    strcpy(copied_nom, nom);
    strcpy(copied_description, description);
    
    // Set
    strcpy(medicament->nom, copied_nom);
    strcpy(medicament->description, copied_description);
    medicament -> prix = prix;
    medicament -> seuil = seuil;
    medicament -> quantite = quantite;
    medicament -> nombre_fournisseurs = nombre_fournisseurs;
    medicament -> default_fournisseur_id = default_fournisseur_id;
    for (int i = 0; i < nombre_fournisseurs; i++) {
        (medicament -> fournisseurs_ids)[i] = fournisseurs_ids[i];
    }
    
}