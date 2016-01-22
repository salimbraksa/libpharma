//
//  commande_controller.c
//  PharmApp
//
//  Created by Braksa - Boutaib on 12/22/15.
//  Copyright © 2015 NSApps. All rights reserved.
//

#include "commande_controller.h"
#include "sb_file.h"

void save_commande(char* filename, Commande* commande){
    
    // Ouvrir le fichier
    FILE* file = fopen(filename, "ab");
    
    // Tester si le fichier est ouvert
    if (!file) return;
    
    // Donner un nouveau id à la commande
    Commande* last_commande = get_last_commande(filename);
    long int last_id = ( last_commande == NULL ? 1 : last_commande->commande_id + 1);
    commande -> commande_id = last_id;
    
    // Avant de sauvegarder la commande, vérifier que la quantité
    // Choisi de commande d'un médicament est inférieur à la quantité du
    // Médicament dans le stock, ainsi que de vérifier que le médicament
    // Existe déja.
    for (int i = 0; i < commande -> nombre_medicaments; i++) {
        
        // Charger le médicament
        long int medic_id = commande -> medicaments[i][0];
        Medicament* medicament = get_medicament_from_id(MEDICAMENTS_FILENAME, medic_id);
        
        // Si ce médicament n'existe pas, fermer le fichier et sortir de la fonction
        // ( aka. ne vendre rien )
        if (!medicament) { fclose(file); return; }
        
        // Augmenter la quantité de ce médicament dans le stock
        medicament -> quantite += commande -> medicaments[i][1];
        
        // Enregistrer ce changement
        save_medicament(MEDICAMENTS_FILENAME, medicament);
        
        // Libérer le médicament
        free(medicament);
        
    }
        
    // Sauvegarder la commande
    fwrite(commande, sizeof(Commande), 1, file);
    
    // Fermer le fichier
    fclose(file);

}

Commande* get_last_commande(char* filename) {
    
    // Ouvrir le fichier
    FILE* flot = fopen(filename, "rb");
    
    // Tester si flot ne sont pas NULL
    if (!flot) return NULL;
    
    // Pointer sur la derniere commande dans le fichier
    fseek(flot, -sizeof(Commande), SEEK_END);
    
    // Lire la derniere commande
    Commande* commande = (Commande*)malloc(sizeof(Commande));
    fread(commande, sizeof(Commande), 1, flot);
    
    return commande;
    
}

LinkedList* get_commandes_from_date(char* filename, char* date, DateComponents ignore_date_components) {
    
    // Ouvrir le fichier
    FILE* flot = fopen(filename, "rb");
    
    // Tester si flot n'est pas NULL
    if (!flot) return NULL;
    
    // Liste chainée de commandes
    LinkedList* commandes = NULL;
    
    do {
        
        Commande* commande = (Commande*)malloc(sizeof(Commande));
        if(!fread(commande, sizeof(Commande), 1, flot)) break;
        
        // Ajouter que les commandes dont la date égale à
        // La date donnée par l'utilisateur
        struct tm commande_time = *localtime(&(commande -> date_time));
        struct tm user_time;
        strptime(date, "%Y-%m-%d", &user_time);
        
        if ( ( user_time.tm_year == commande_time.tm_year || (Year & ignore_date_components) ) &&
              ( user_time.tm_mon == commande_time.tm_mon || (Month & ignore_date_components) ) &&
              (user_time.tm_mday == commande_time.tm_mday || (Day & ignore_date_components)) ){
            linked_list_append(&commandes, commande);
        } else {
            free(commande);
        }
        
    } while (1);

    // Return
    return commandes;

}

LinkedList* get_commandes(char* filename) {
    
    // Ouvrir le fichier
    FILE* flot = fopen(filename, "rb");
    
    // Tester si flot n'est pas NULL
    if (!flot) return NULL;
    
    // Declarer un tableau de commandes
    LinkedList* commandes = NULL;
    
    // Lire les données du fichier
    do {
        Commande* commande = (Commande*)malloc(sizeof(Commande));
        if (!fread(commande, sizeof(Commande), 1, flot)) break;
        linked_list_append(&commandes, commande);
    } while (1);
    
    // Fermer le fichier
    fclose(flot);
    
    // Return
    return commandes;
    
}

void automatically_commande_medicaments() {
    
    // Ouvrir le fichier
    FILE* file = fopen("needed_medics", "rb");
    
    // Tester
    if (!file) return;
    
    // Initializer une premiere commande
    long int medics[0][2] = {};
    Commande* commande = create_commande(time(NULL), 0, medics);
    
    // Itérer
    do {
        
        // Charger l'id du médicament
        long int medic_id;
        if (!fread(&medic_id, sizeof(long int), 1, file)) break;
        
        // Charger le médicament
        Medicament* medicament = get_medicament_from_id(MEDICAMENTS_FILENAME, medic_id);
        
        // Ajouter le médicament à la commande
        Commande* next_commande = medicament_add_to_commande(medicament, medicament -> seuil, commande);
        
        // Si ...
        if (next_commande) {
            
            // Sauvegarder la commande précedente
            save_commande(COMMANDES_FILENAME, commande);
            
            // Libérer la commande précedente
            free(commande);
            
            // Utiliser la commande suivante
            commande = next_commande;
            
        }
        
        // Libérer
        free(medicament);
        
    } while (1);
    
    // Sauvegarder la commande
    save_commande(COMMANDES_FILENAME, commande);
    
    // Fermer le fichier
    fclose(file);
    
    // Vider le fichier
    file = fopen("needed_medics", "wb");
    fclose(file);
    
}