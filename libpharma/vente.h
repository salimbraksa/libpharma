//
//  vente.h
//  PharmApp
//
//  Created by Braksa - Boutaib on 12/25/15.
//  Copyright © 2015 NSApps. All rights reserved.
//

#ifndef vente_h
#define vente_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VENTE_MAX_MEDICAMENTS_IDS 10

/// Définition de la structure Vente
typedef struct {
    
    long int vente_id;
    time_t date_time;
    
    int nombre_medicaments;
    int medicaments[VENTE_MAX_MEDICAMENTS_IDS][2];
    
} Vente;

/// Permet de créer une nouvelle Vente
Vente* create_vente(time_t date_time,
                    int nombre_medicamants,
                    int medicaments[VENTE_MAX_MEDICAMENTS_IDS][2]);

#endif /* vente_h */
