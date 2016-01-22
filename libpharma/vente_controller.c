//
//  vente_controller.c
//  PharmApp
//
//  Created by Salim Braksa on 12/31/15.
//  Copyright © 2015 Braksa Salim. All rights reserved.
//

#include "vente_controller.h"

void save_vente(char* filename, Vente* vente) {
    
    // Ouvrir le fichier
    FILE* file = fopen(filename, "ab");
    
    // Tester si le fichier est ouvert
    if (!file) return;
    
    // Donner un nouveau id à la vente
    Vente* last_vente = get_last_vente(filename);
    long int last_id = ( last_vente == NULL ? 1 : last_vente->vente_id + 1);
    vente -> vente_id = last_id;
    
    // Avant de sauvegarder la vente, vérifier que la quantité
    // Choisi de vente d'un médicament est inférieur à la quantité du
    // Médicament dans le stock, ainsi que de vérifier que le médicament
    // Existe déja.
    for (int i = 0; i < vente -> nombre_medicaments; i++) {
        
        // Charger le médicament
        long int medic_id = vente -> medicaments[i][0];
        Medicament* medicament = get_medicament_from_id(MEDICAMENTS_FILENAME, medic_id);
        
        // Si ce médicament n'existe pas, fermer le fichier et sortir de la fonction
        // ( aka. ne vendre rien )
        if (!medicament) { fclose(file); return; }
        
        // Sinon, assurer de choisir le minimum entre la quantité disponible en stock
        // Et la quantité choisi à vendre
        vente -> medicaments[i][1] = min(vente -> medicaments[i][1], medicament -> quantite);
        
        // Diminuer la quantité de ce médicament dans le stock
        medicament -> quantite -= vente -> medicaments[i][1];
        
        // Si la quantité du médicament est inférieur à son seuil
        // Marquer le médicament d'être commander automatiquement lors
        // De la prochaine ouverture du programme
        if (medicament -> quantite < medicament -> seuil) {
            should_commande_medicament(medicament);
        }
        
        // Enregistrer ce changement
        save_medicament(MEDICAMENTS_FILENAME, medicament);
        
        // Libérer le médicament
        free(medicament);
        
    }
    
    // Sauvegarder la vente
    fwrite(vente, sizeof(Vente), 1, file);
    
    // Fermer le fichier
    fclose(file);
    
}

LinkedList* get_ventes(char* filename) {
    
    // Ouvrir le fichier
    FILE* flot = fopen(filename, "rb");
    
    // Tester si flot n'est pas NULL
    if (!flot) return NULL;
    
    // Declarer une liste chainées de ventes
    LinkedList* ventes = NULL;
    
    // Lire les données du fichier
    do {
        Vente* vente = (Vente*)malloc(sizeof(Vente));
        if (!fread(vente, sizeof(Vente), 1, flot)) break;
        linked_list_append(&ventes, vente);
    } while (1);
    
    // Fermer le fichier
    fclose(flot);
    
    // Return
    return ventes;
    
    
}

LinkedList* get_ventes_from_date(char* filename, char* date, DateComponents ignore_date_components) {
    
    // Ouvrir le fichier
    FILE* flot = fopen(filename, "rb");
    
    // Tester si flot n'est pas NULL
    if (!flot) return NULL;
    
    // Liste chainée de ventes
    LinkedList* ventes = NULL;
    
    do {
        
        Vente* vente = (Vente*)malloc(sizeof(Vente));
        if(!fread(vente, sizeof(Vente), 1, flot)) break;
        if (vente -> vente_id == 0) break;
        
        // Ajouter que les ventes dont la date égale à
        // La date donnée par l'utilisateur
        struct tm vente_time = *localtime(&(vente -> date_time));
        struct tm user_time;
        strptime(date, "%Y-%m-%d", &user_time);
        
        if ( (( user_time.tm_year == vente_time.tm_year || (Year & ignore_date_components) ) &&
            ( user_time.tm_mon == vente_time.tm_mon || (Month & ignore_date_components) ) &&
            user_time.tm_mday == vente_time.tm_mday) || (Day & ignore_date_components) ) {
            linked_list_append(&ventes, vente);
        }
        
    } while (1);
    
    // Return
    return ventes;
    
}

Vente* get_last_vente(char* filename) {
    
    // Ouvrir le fichier
    FILE* flot = fopen(filename, "rb");
    
    // Tester si flot ne sont pas NULL
    if (!flot) return NULL;
    
    // Pointer sur la derniere vente dans le fichier
    fseek(flot, -sizeof(Vente), SEEK_END);
    
    // Lire la derniere vente
    Vente* vente = (Vente*)malloc(sizeof(Vente));
    fread(vente, sizeof(Vente), 1, flot);
    
    return vente;
    
}