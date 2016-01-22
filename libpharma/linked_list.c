//
//  linked_list.c
//  PharmApp
//
//  Created by Salim Braksa on 12/30/15.
//  Copyright © 2015 Braksa Salim. All rights reserved.
//

#include "linked_list.h"

LinkedList* linked_list_new(void* element) {
    
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list -> data = element;
    list -> next = NULL;
    return list;
    
}

void linked_list_append(LinkedList** list, void* element) {
    
    // Do nothing if element is NULL
    if (!element) return;
    
    // If *list is NULL, then just create a new one
    if (!(*list)) {
        *list = linked_list_new(element);
        return;
    }
    
    // Current node, and previous node
    LinkedList* current_node = *list;
    LinkedList* previous_node = NULL;
    
    // Iterate through list
    while (current_node) {
        previous_node = current_node;
        current_node = current_node -> next;
    }
    
    // Create new node
    current_node = linked_list_new(element);
    previous_node->next = current_node;
    
}

int list_len(LinkedList* list) {
    
    int counter = 0;
    LinkedList* iterator = list;
    while (iterator) {
        if (iterator -> data) counter++;
        iterator = iterator -> next;
    }
    return  counter;
    
}

void* element_from_index(LinkedList* list, int index) {
    
    LinkedList* iterator = list;
    int count = 0;
    while (iterator) {
        if (count == index) break;
        iterator = iterator -> next;
    }
    
    if (iterator) return iterator -> data;
    return NULL;
    
}