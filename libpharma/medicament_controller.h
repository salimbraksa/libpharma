//
//  medicament_controller.h
//  PharmApp
//
//  Created by Braksa - Boutaib on 12/25/15.
//  Copyright © 2015 NSApps. All rights reserved.
//

#ifndef medicament_controller_h
#define medicament_controller_h

#include <stdio.h>
#include "medicament.h"
#include "linked_list.h"
#include "fournisseur_controller.h"
#include "constants.h"
#include "sb_string.h"
#include "commande.h"

/// Permet de save le medicament dans un fichier
void save_medicament(char* filename, Medicament* medicament);

/// Permet d'ajouter un médicament à une commandew
/// Si cette commande a suffisament d'espace pour contenir
/// Le médicament, sinon on crée une nouvelle commande
/// Pour contenir le médicament et l'a retourne
Commande* medicament_add_to_commande(Medicament* medicament, int quantity, Commande* commande);

/// Permet de retourner le dernier medicament qui peut être NULL
Medicament* get_last_medicament(char* filename);

/// Permet de retourner un medicament à partir son id
Medicament* get_medicament_from_id(char* filename, long int medicament_id);

/// Permet de retourner un medicament à partir son nom
LinkedList* get_medicament_from_name(char* filename, char* name);

/// Permet de retourner les fournisseurs d'un médicament
LinkedList* get_fournisseurs_from_medicament(char* filename, long int medicament_id);

/// Permet de marquer le médicament qu'il doit être commander automatiquement
void should_commande_medicament(Medicament* medicament);

#endif /* medicament_controller_h */
