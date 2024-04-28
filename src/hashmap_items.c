/*
** EPITECH PROJECT, 2024
** Hashmap in C
** File description=
** hashmap_items.c
*/

#include <stddef.h>
#include <stdlib.h>
#include "hashmap.h"

static size_t hashmap_count_items(const hashmap_t *hashmap)
{
    size_t i = 0;
    size_t count = 0;
    hashmap_entry_t *entry = NULL;

    for (; i < HASHMAP_SIZE; ++i) {
        entry = hashmap->buckets[i].head;
        while (NULL != entry) {
            ++count;
            entry = entry->next;
        }
    }
    return count;
}

static void hashmap_fill_keys(const hashmap_t *hashmap, hashmap_keys_t *keys)
{
    size_t i = 0;
    size_t j = 0;
    hashmap_entry_t *entry = NULL;

    for (; i < HASHMAP_SIZE; ++i) {
        entry = hashmap->buckets[i].head;
        while (NULL != entry) {
            keys->keys[j] = entry->key;
            entry = entry->next;
            ++j;
        }
    }
}

static void hashmap_fill_values(const hashmap_t *hashmap,
    hashmap_values_t *values)
{
    size_t i = 0;
    size_t j = 0;
    hashmap_entry_t *entry = NULL;

    for (; i < HASHMAP_SIZE; ++i) {
        entry = hashmap->buckets[i].head;
        while (NULL != entry) {
            values->values[j] = entry->value;
            entry = entry->next;
            ++j;
        }
    }
}

static void hashmap_fill_items(const hashmap_t *hashmap,
    hashmap_items_t *items)
{
    size_t i = 0;
    size_t j = 0;
    hashmap_entry_t *entry = NULL;

    for (; i < HASHMAP_SIZE; ++i) {
        entry = hashmap->buckets[i].head;
        while (NULL != entry) {
            items->items[j].key = entry->key;
            items->items[j].value = entry->value;
            entry = entry->next;
            ++j;
        }
    }
}

hashmap_keys_t *hashmap_keys(const hashmap_t *hashmap)
{
    hashmap_keys_t *keys = calloc(1, sizeof(hashmap_keys_t));

    if (NULL != keys) {
        keys->count = hashmap_count_items(hashmap);
        keys->keys = calloc(keys->count, sizeof(char *));
        if (NULL == keys->keys) {
            free(keys);
            return NULL;
        }
        hashmap_fill_keys(hashmap, keys);
    }
    return keys;
}

hashmap_values_t *hashmap_values(const hashmap_t *hashmap)
{
    hashmap_values_t *values = calloc(1, sizeof(hashmap_values_t));

    if (NULL != values) {
        values->count = hashmap_count_items(hashmap);
        values->values = calloc(values->count, sizeof(char *));
        if (NULL == values->values) {
            free(values);
            return NULL;
        }
        hashmap_fill_values(hashmap, values);
    }
    return values;
}

hashmap_items_t *hashmap_items(const hashmap_t *hashmap)
{
    hashmap_items_t *items = calloc(1, sizeof(hashmap_items_t));

    if (NULL != items) {
        items->count = hashmap_count_items(hashmap);
        items->items = calloc(items->count, sizeof(hashmap_item_t));
        if (NULL == items->items) {
            free(items);
            return NULL;
        }
        hashmap_fill_items(hashmap, items);
    }
    return items;
}

void hashmap_keys_destroy(hashmap_keys_t *keys)
{
    free(keys->keys);
    free(keys);
}

void hashmap_values_destroy(hashmap_values_t *values)
{
    free(values->values);
    free(values);
}

void hashmap_items_destroy(hashmap_items_t *items)
{
    free(items->items);
    free(items);
}
