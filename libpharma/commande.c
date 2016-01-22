//
//  commande.c
//  PharmApp
//
//  Created by Braksa - Boutaib on 12/21/15.
//  Copyright © 2015 NSApps. All rights reserved.
//

#include "commande.h"

// Implémentation des fonctions

Commande* create_commande(time_t date_time, int nombre_medicaments, long int medicaments[MAX_MEDICAMENTS_IDS][2]) {
    
    // Alloc new Commande
    Commande* commande = (Commande*)malloc(sizeof(Commande));
    
    // Set properties
    commande -> commande_id = -1;
    commande -> date_time = date_time;
    commande -> nombre_medicaments = nombre_medicaments;
    for (int i = 0; i < nombre_medicaments; i++) {
        commande -> medicaments[i][0] = medicaments[i][0];
        commande -> medicaments[i][1] = medicaments[i][1];
    }
    
    // Return
    return commande;
    
}