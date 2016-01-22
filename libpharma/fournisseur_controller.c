//
//  fournisseur_controller.c
//  PharmApp
//
//  Created by Braksa - Boutaib on 12/25/15.
//  Copyright © 2015 NSApps. All rights reserved.
//

#include "fournisseur_controller.h"

void save_fournisseur(char* filename, Fournisseur* fournisseur) {
    
    // Avant tout, tester si fournisseur n'est pas NULL
    if (!fournisseur) return;
    
    // Créer le fichier s'il n'existe pas
    if (!file_exist(filename)) create_file(filename);
    
    // Cherche si le médicament existe
    // Si oui, il suffit de modifier le médicament
    // Existant, Sinon on crée un nouveau médicament
    // Dans la base de donnée
    FILE* file = fopen(filename, "r+b");
    
    // Sortir si le fichier ne peux pas s'ouvrir
    if (!file) return;
    
    // Itérer
    do {
        
        Fournisseur* current_fournisseur = (Fournisseur*)malloc(sizeof(Fournisseur));
        if (!fread(current_fournisseur, sizeof(Fournisseur), 1, file)) break;
        
        // Si le médicament est trouvé
        if (current_fournisseur -> fournisseur_id == fournisseur -> fournisseur_id) {
            
            // Modifier le médicament
            long int currPost = ftell(file);
            fseek(file, currPost - sizeof(Fournisseur), SEEK_SET);
            fwrite(fournisseur, sizeof(Fournisseur), 1, file);
            
            // Sortir de la fonction
            fclose(file);
            return;
        }
        
    } while (1);
    
    // Set nouveau id
    long int new_id = get_last_fournisseur(filename) -> fournisseur_id + 1;
    fournisseur -> fournisseur_id = new_id;
    
    // Sauvegarder la commande
    fwrite(fournisseur, sizeof(Fournisseur), 1, file);
    
    // Fermer le fichier
    fclose(file);
    
}

Fournisseur* get_last_fournisseur(char* filename) {
    
    // Ouvrir le fichier
    FILE* flot = fopen(filename, "rb");
    
    // Tester si flot ne sont pas NULL
    if (!flot) return NULL;
    
    // Pointer sur le dernier fournisseur dans le fichier
    fseek(flot, -sizeof(Fournisseur), SEEK_END);
    
    // Lire la derniere fournisseur
    Fournisseur* fournisseur = (Fournisseur*)malloc(sizeof(Fournisseur));
    fread(fournisseur, sizeof(Fournisseur), 1, flot);
    
    return fournisseur;
    
}

LinkedList* get_fournisseurs(char* filename) {
    
    // Ouvrir le fichier
    FILE* flot = fopen(filename, "rb");
    
    // Tester si flot n'est pas NULL
    if (!flot) return NULL;
    
    // Declarer une liste chainées de fournisseurs
    LinkedList* fournisseurs = NULL;
    
    // Lire les données du fichier
    do {
        Fournisseur* fournisseur = (Fournisseur*)malloc(sizeof(Fournisseur));
        if (!fread(fournisseur, sizeof(Fournisseur), 1, flot)) break;
        linked_list_append(&fournisseurs, fournisseur);
    } while (1);
    
    // Fermer le fichier
    fclose(flot);
    
    // Return
    return fournisseurs;
    
}

Fournisseur* get_fournisseur_from_id(char* filename, long int fournisseur_id) {
    
    // Ouvrir le fichier
    FILE* flot = fopen(filename, "rb");
    
    // Tester si flot n'est pas NULL
    if (!flot) return NULL;
    
    do {
        Fournisseur* fournisseur = (Fournisseur*)malloc(sizeof(Fournisseur));
        if (!fread(fournisseur, sizeof(Fournisseur), 1, flot)) break;
        if (fournisseur -> fournisseur_id == fournisseur_id) return fournisseur;
    } while (1);
    
    // Close the file
    fclose(flot);
    
    return NULL;
    
}

void remove_fournisseur(char* filename, long int fournisseur_id) {
    
    // Declare files
    FILE* origin_file = fopen(filename, "rb");
    FILE* copied_file = fopen("tmp", "wb");
    
    // If the system couldn't open one of the files
    if (!origin_file || !copied_file) return;
    
    do {
        Fournisseur* fournisseur = (Fournisseur*)malloc(sizeof(Fournisseur));
        if (!fread(fournisseur, sizeof(Fournisseur), 1, origin_file)) break;
        if (fournisseur -> fournisseur_id != fournisseur_id) fwrite(fournisseur, sizeof(Fournisseur), 1, copied_file);
    } while (1);
    
    // Close files
    fclose(origin_file);
    fclose(copied_file);
    
    // Remove origin file
    remove(filename);
    rename("tmp", filename);
    
}