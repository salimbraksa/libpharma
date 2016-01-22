//
//  client.h
//  PharmApp
//
//  Created by Braksa - Boutaib on 12/17/15.
//  Copyright © 2015 NSApps. All rights reserved.
//

#ifndef client_h
#define client_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Définition de la structure Client
typedef struct {

    long int client_id;
    char nom[80];
    char telephone[11];
    char cin[9];

} Client;

/// Permet de créer un nouveau client
Client* creer_client(char* nom,
                     char* telephone,
                     char* cin);

/// Permet de modifier les informations d'un client
void modifier_client(Client* client,
                     char* nom,
                     char* telephone,
                     char* cin);

#endif /* client_h */
