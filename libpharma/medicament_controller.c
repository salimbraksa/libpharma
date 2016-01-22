//
//  medicament_controller.c
//  PharmApp
//
//  Created by Braksa - Boutaib on 12/25/15.
//  Copyright © 2015 NSApps. All rights reserved.
//

#include "medicament_controller.h"
#include "sb_file.h"

void save_medicament(char* filename, Medicament* medicament) {
    
    // Avant tout, tester si medicament n'est pas NULL
    if (!medicament) return;
    
    // Créer le fichier s'il n'existe pas
    if (!file_exist(filename)) {
        create_file(filename);
    }
    
    // Cherche si le médicament existe
    // Si oui, il suffit de modifier le médicament
    // Existant, Sinon il crée un nouveau médicament
    // Dans la base de donnée
    FILE* file = fopen(filename, "r+b");
    
    // Sortir si le fichier ne peux pas s'ouvrir
    if (!file) return;
    
    // Itérer
    do {
        
        Medicament* current_medicament = (Medicament*)malloc(sizeof(Medicament));
        if (!fread(current_medicament, sizeof(Medicament), 1, file)) break;
        
        // Si le médicament est trouvé
        if (current_medicament -> medicament_id == medicament -> medicament_id) {
            
            // Modifier le médicament
            long int currPost = ftell(file);
            fseek(file, currPost - sizeof(Medicament), SEEK_SET);
            fwrite(medicament, sizeof(Medicament), 1, file);
         
            // Sortir de la fonction
            fclose(file);
            return;
        }
        
    } while (1);
    
    // Set nouveau id
    long int new_id = get_last_medicament(filename) -> medicament_id + 1;
    medicament -> medicament_id = new_id;
    
    // Sauvegarder la commande
    fwrite(medicament, sizeof(Medicament), 1, file);
    
    // Fermer le fichier
    fclose(file);
    
}

Medicament* get_last_medicament(char* filename) {
    
    // Ouvrir le fichier
    FILE* flot = fopen(filename, "rb");
    
    // Tester si flot ne sont pas NULL
    if (!flot) return NULL;
    
    // Pointer sur le dernier medicament dans le fichier
    fseek(flot, -sizeof(Medicament), SEEK_END);
    
    // Lire la derniere commande
    Medicament* medicament = (Medicament*)malloc(sizeof(Medicament));
    fread(medicament, sizeof(Medicament), 1, flot);
    
    return medicament;
    
}

Medicament* get_medicament_from_id(char* filename, long int medicament_id) {
    
    // Ouvrir le fichier
    FILE* flot = fopen(filename, "rb");
    
    // Tester si flot n'est pas NULL
    if (!flot) return NULL;
    
    do {
        Medicament* medicament = (Medicament*)malloc(sizeof(Medicament));
        if (!fread(medicament, sizeof(Medicament), 1, flot)) break;
        if (medicament -> medicament_id == medicament_id) return medicament;
    } while (1);
    
    return NULL;
    
}

LinkedList* get_medicament_from_name(char* filename, char* name) {
    
    // Ouvrir le fichier
    FILE* flot = fopen(filename, "rb");
    
    // Tester si flot n'est pas NULL
    if (!flot) return NULL;
    
    // Declarer une liste chainées de medicaments
    LinkedList* medicaments = NULL;
    
    // Lower the name
    char* lower_name = lower_string(name);
    
    do {
        Medicament* medicament = (Medicament*)malloc(sizeof(Medicament));
        if (!fread(medicament, sizeof(Medicament), 1, flot)) break;
        if (strcmp(lower_string(medicament->nom), lower_name) == 0) linked_list_append(&medicaments, medicament);
    } while (1);
    
    return medicaments;
    
}

LinkedList* get_fournisseurs_from_medicament(char* filename, long int medicament_id) {
    
    // Ouvrir le fichier
    FILE* flot = fopen(filename, "rb");
    
    // Tester si flot n'est pas NULL
    if (!flot) return NULL;
    
    // Déclarer une liste chainée de fournisseurs
    LinkedList* fournisseurs = NULL;
    
    do {
        
        // Itérer sur chaque médicament
        Medicament* medicament = (Medicament*)malloc(sizeof(Medicament));
        if (!fread(medicament, sizeof(Medicament), 1, flot)) break;
        
        // Si le médicament qu'on cherche est trouvé
        if (medicament -> medicament_id == medicament_id) {
            for (int i = 0; i < medicament -> nombre_fournisseurs; i++) {
                
                // Chercher le fournisseur par son id
                int fournisseur_id = (medicament -> fournisseurs_ids)[i];
                Fournisseur* fournisseur = (Fournisseur*)malloc(sizeof(Fournisseur));
                fournisseur = get_fournisseur_from_id(FOURNISSEURS_FILENAME, fournisseur_id);
                
                // Ajouter le fournisseur à la liste si ce dernier existe
                if (fournisseur) linked_list_append(&fournisseurs, fournisseur);
                
            }
            
        }
        
    } while (1);
    
    return fournisseurs;
    
}

Commande* medicament_add_to_commande(Medicament* medicament, int quantity, Commande* commande) {
    
    // Ne rien faire si l'un des deux arguments est NULL ( medicament ou commande )
    if (!medicament || !commande) return NULL;
    
    // La commande à utiliser
    // Initialement, on utilise la commande
    // Qui provient du l'argument de la fonction
    Commande* use_commande = commande;
    
    // Vérifier si la commande ne peut pas contenir le médicament
    if (commande -> nombre_medicaments >= MAX_MEDICAMENTS_IDS) {
        long int ids[0][2] = {};
        use_commande = create_commande(time(NULL), 0, ids);
    }
    
    // Incrémenter le nombre de médicaments
    use_commande->nombre_medicaments++;
    
    // Ajouter l'id du médicament et initializer sa quantité par 1
    use_commande -> medicaments[use_commande->nombre_medicaments-1][0] = medicament -> medicament_id;
    use_commande -> medicaments[use_commande->nombre_medicaments-1][1] = quantity;
    
    // Si la on utiliser une nouvelle commande, on doit la retourner
    if (use_commande -> commande_id != commande -> commande_id) return use_commande;
    return NULL;
}

void should_commande_medicament(Medicament* medicament) {
    
    // Ouvrir le fichier
    FILE* file = fopen("needed_medics", "ab");
    
    // Tester
    if (!file) return;
    
    // Ecrire l'id du medicament
    fwrite(&(medicament->medicament_id), sizeof(long int), 1, file);
    
    // Fermer
    fclose(file);
    
}