//
//  client_controller.c
//  PharmApp
//
//  Created by Braksa - Boutaib on 12/24/15.
//  Copyright © 2015 NSApps. All rights reserved.
//

#include "client_controller.h"
#include "sb_file.h"

void save_client(char* filename, Client* client) {
    
    // Avant tout, tester si client n'est pas NULL
    if (!client) return;
    
    // Créer le fichier s'il n'existe pas
    if (!file_exist(filename)) {
        create_file(filename);
    }
    
    // Cherche si le médicament existe
    // Si oui, il suffit de modifier le médicament
    // Existant, Sinon il crée un nouveau médicament
    // Dans la base de donnée
    FILE* file = fopen(filename, "r+b");
    
    // Sortir si le fichier ne peux pas s'ouvrir
    if (!file) return;
    
    // Itérer
    do {
        
        Client* current_client = (Client*)malloc(sizeof(Client));
        if (!fread(current_client, sizeof(Client), 1, file)) break;
        
        // Si le médicament est trouvé
        if (current_client -> client_id == client -> client_id) {
            
            // Modifier le médicament
            long int currPost = ftell(file);
            fseek(file, currPost - sizeof(Client), SEEK_SET);
            fwrite(client, sizeof(Client), 1, file);
            
            // Sortir de la fonction
            fclose(file);
            return;
        }
        
    } while (1);
    
    // Set nouveau id
    long int new_id = get_last_client(filename) -> client_id + 1;
    client -> client_id = new_id;
    
    // Sauvegarder la commande
    fwrite(client, sizeof(Client), 1, file);
    
    // Fermer le fichier
    fclose(file);
    
}

Client* get_last_client(char* filename) {
    
    // Ouvrir le fichier
    FILE* flot = fopen(filename, "rb");
    
    // Tester si flot ne sont pas NULL
    if (!flot) return NULL;
    
    // Pointer sur la derniere commande dans le fichier
    fseek(flot, -sizeof(Client), SEEK_END);
    
    // Lire la derniere commande
    Client* client = (Client*)malloc(sizeof(Client));
    fread(client, sizeof(Client), 1, flot);
    
    return client;
    
}

LinkedList* get_clients(char* filename) {
    
    // Ouvrir le fichier
    FILE* flot = fopen(filename, "rb");
    
    // Tester si flot n'est pas NULL
    if (!flot) return NULL;
    
    // Declarer une liste chainées de clients
    LinkedList* clients = NULL;
    
    // Lire les données du fichier
    do {
        Client* client = (Client*)malloc(sizeof(Client));
        if (!fread(client, sizeof(Client), 1, flot)) break;
        linked_list_append(&clients, client);
    } while (1);
    
    // Fermer le fichier
    fclose(flot);
    
    // Return
    return clients;
    
}

Client* get_client_from_id(char* filename, long int client_id) {
    
    // Ouvrir le fichier
    FILE* flot = fopen(filename, "rb");
    
    // Tester si flot n'est pas NULL
    if (!flot) return NULL;
    
    do {
        Client* client = (Client*)malloc(sizeof(Client));
        if (!fread(client, sizeof(Client), 1, flot)) break;
        if (client -> client_id == client_id) return client;
    } while (1);
    
    return NULL;
    
}

LinkedList* get_client_from_name(char* filename, char* name) {
    
    // Ouvrir le fichier
    FILE* flot = fopen(filename, "rb");
    
    // Tester si flot n'est pas NULL
    if (!flot) return NULL;
    
    // Declarer une liste chainées de clients
    LinkedList* clients = NULL;
    
    // Lower the name
    char* lower_name = lower_string(name);
    
    do {
        Client* client = (Client*)malloc(sizeof(Client));
        if (!fread(client, sizeof(Client), 1, flot)) break;
        if (strcmp(lower_string(client->nom), lower_name) == 0) linked_list_append(&clients, client);
    } while (1);
    
    return clients;
    
}