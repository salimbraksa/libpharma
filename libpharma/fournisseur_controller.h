//
//  fournisseur_controller.h
//  PharmApp
//
//  Created by Braksa - Boutaib on 12/25/15.
//  Copyright © 2015 NSApps. All rights reserved.
//

#ifndef fournisseur_controller_h
#define fournisseur_controller_h

#include <stdio.h>
#include "linked_list.h"
#include "fournisseur.h"
#include "sb_string.h"
#include "sb_file.h"

/// Permet de save la fournisseur dans un fichier
void save_fournisseur(char* filename, Fournisseur* fournisseur);

/// Permet de retourner le dernier id d'une fournisseur qui peut être NULL
Fournisseur* get_last_fournisseur(char* filename);

/// Permet de retourner un fournisseur par son id
Fournisseur* get_fournisseur_from_id(char* filename, long int fournisseur_id);

/// Permet de charger tout les fournisseurs à partir d'un fichier
LinkedList* get_fournisseurs(char* filename);

/// Permet de supprimer un fournisseur
void remove_fournisseur(char* filename, long int fournisseur_id);

#endif /* fournisseur_controller_h */
