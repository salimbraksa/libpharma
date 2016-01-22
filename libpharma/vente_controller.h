//
//  vente_controller.h
//  PharmApp
//
//  Created by Salim Braksa on 12/31/15.
//  Copyright © 2015 Braksa Salim. All rights reserved.
//

#ifndef vente_controller_h
#define vente_controller_h

#include <stdio.h>
#include "vente.h"
#include "medicament_controller.h"
#include "linked_list.h"
#include "sb_number.h"
#include "sb_date.h"

/// Permet de sauvegarder une vente
void save_vente(char* filename, Vente* vente);

/// Permet de retourner une liste chainée de toute les ventes
LinkedList* get_ventes(char* filename);

/// Permet de retourner une liste chainée de ventes d'une date donnée
LinkedList* get_ventes_from_date(char* filename, char* date,  DateComponents ignore_date_components);

/// Permet de retourner la derniere vente
Vente* get_last_vente(char* filename);

#endif /* vente_controller_h */
