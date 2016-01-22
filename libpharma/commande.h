//
//  commande.h
//  PharmApp
//
//  Created by Braksa - Boutaib on 12/21/15.
//  Copyright © 2015 NSApps. All rights reserved.
//

#ifndef commande_h
#define commande_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_MEDICAMENTS_IDS 50

/// Définition de la structure Commande
typedef struct {
    
    long int commande_id;
    time_t date_time;
    
    int nombre_medicaments;
    long int medicaments[MAX_MEDICAMENTS_IDS][2];
    
} Commande;

/// Permet de créer une nouvelle Commande
Commande* create_commande(time_t date_time,
                          int nombre_medicamants,
                          long int medicaments[MAX_MEDICAMENTS_IDS][2]);

#endif /* commande_h */
