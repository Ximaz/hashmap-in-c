/*
** EPITECH PROJECT, 2024
** Hashmap in C
** File description:
** hashmap_delete.c
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

static void hashmap_delete_entry(hashmap_t *hashmap, hashmap_entry_t **head)
{
    hashmap_entry_t *new_entry = (*head)->prev ? (*head)->prev : (*head)->next;

    if (NULL != (*head)->key->release)
        (*head)->key->release((*head)->key->key);
    free((*head)->key);
    if (NULL != hashmap->destroy)
        hashmap->destroy((*head)->value);
    if (NULL != (*head)->prev)
        (*head)->prev->next = (*head)->next;
    if (NULL != (*head)->next)
        (*head)->next->prev = (*head)->prev;
    free((*head));
    (*head) = new_entry;
}

void hashmap_delete(hashmap_t *hashmap, const char *key)
{
    hash_t hash = hashmap_hash(key);
    hashmap_entry_t **head = &(hashmap->buckets[hash].head);

    while (NULL != (*head)) {
        if (0 != strcmp(key, (*head)->key->key)) {
            (*head) = (*head)->next;
            continue;
        }
        hashmap_delete_entry(hashmap, head);
        return;
    }
}
