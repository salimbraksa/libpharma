//
//  vente.c
//  PharmApp
//
//  Created by Braksa - Boutaib on 12/25/15.
//  Copyright © 2015 NSApps. All rights reserved.
//

#include "vente.h"

// Implémentation des fonctions

Vente* create_vente(time_t date_time, int nombre_medicaments, int medicaments[VENTE_MAX_MEDICAMENTS_IDS][2]) {
    
    // Alloc new Commande
    Vente* vente = (Vente*)malloc(sizeof(Vente));
    
    // Set properties
    vente -> vente_id = -1;
    vente -> date_time = date_time;
    vente -> nombre_medicaments = nombre_medicaments;
    for (int i = 0; i < nombre_medicaments; i++) {
        vente -> medicaments[i][0] = medicaments[i][0];
        vente -> medicaments[i][1] = medicaments[i][1];
    }
    
    // Return
    return vente;
    
}