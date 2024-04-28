/*
** EPITECH PROJECT, 2024
** Hashmap in C
** File description:
** hashmap_set.c
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

static hashmap_key_t *make_key(char *key, void (*release)(char *key))
{
    hashmap_key_t *hkey = calloc(1, sizeof(hashmap_key_t));

    if (NULL != hkey) {
        hkey->key = key;
        hkey->release = release;
    }
    return hkey;
}

static int hashmap_insert(hashmap_t *hashmap, hashmap_key_t *key, void *value)
{
    hashmap_entry_t *entry = hashmap_entry_new(key, value);

    if (NULL == entry)
        return -1;
    hashmap_entry_set(hashmap, entry);
    return 0;
}

int hashmap_set(hashmap_t *hashmap, char *key, void (*release)(char *key),
    void *value)
{
    hashmap_key_t *hkey = NULL;
    hashmap_entry_t *entry = (hashmap_entry_t *)
        hashmap_entry_get(hashmap, key);

    if (NULL != entry) {
        if (NULL != hashmap->destroy)
            hashmap->destroy(entry->value);
        entry->value = value;
        return 0;
    }
    hkey = make_key(key, release);
    if (NULL == hkey)
        return -1;
    if (-1 == hashmap_insert(hashmap, hkey, value)) {
        free(hkey);
        return -1;
    }
    return 0;
}
