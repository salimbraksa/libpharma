//
//  commande_controller.h
//  PharmApp
//
//  Created by Braksa - Boutaib on 12/22/15.
//  Copyright © 2015 NSApps. All rights reserved.
//

#ifndef commande_controller_h
#define commande_controller_h

#include <stdio.h>
#include "medicament_controller.h"
#include "linked_list.h"
#include "medicament.h"
#include "commande.h"
#include "sb_number.h"
#include "sb_date.h"

/// Permet d'ajouter un médicament à une commande
void commande_ajouter_medicament(Commande* commande, Medicament* medicament);

/// Permet de save la commande dans un fichier
void save_commande(char* filename, Commande* commande);

/// Permet de retourner le dernier id d'une commande qui peut être NULL
Commande* get_last_commande(char* filename);

/// Permet de retourner une liste de commandes d'une date donnée
LinkedList* get_commandes_from_date(char* filename, char* date, DateComponents ignore_date_components);

/// Permet de commander automatiquement les médicaments qui ont
/// Une quantité inférieur à leur seuil
void automatically_commande_medicaments();

/// Permet de charger tout les commandes à partir d'un fichier
LinkedList* get_commandes(char* filename);

#endif /* commande_controller_h */
