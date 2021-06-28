#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "data-structures/hashmap/hashmap.h"
#include "utils/utils.h"

// Allocates and returns a pointer to the hashmap
HashMapT*
new_hashmap(int capacity)
{
    if (capacity > 0) {
        HashMapT* map = malloc(sizeof *map);

        if (map == NULL)
            die(__func__, ERR_ALLOC_FAILED);

        // map->items = malloc(sizeof *(map->items) * map->capacity);
        map->items = malloc(sizeof(HashMapItemT*) * map->capacity);

        if (map->items == NULL) {
            free_hashmap(map);
            die(__func__, ERR_ALLOC_FAILED);
        }

        for (int i = 0; i < capacity; i++) {
            map->items[i] = NULL;
        }

        // for (int i = 0; i < capacity; i++) {
        //     map->items[i].key = NULL;
        //     map->items[i].value = NULL;
        // }

        map->capacity = capacity;
        map->size = 0;
        return map;
    }

    return NULL;
}

// Inserts a given key-value pair in hashmap
void
put_key(HashMapT* map, char* key, char* value)
{
    if (map == NULL || key == NULL || value == NULL)
        goto error;

    if (map->size == map->capacity)
        die(__func__, ERR_OUT_OF_BOUNDS);

    int start_index = gen_hash(key) % map->capacity;
    int collisions = 0;

    // while (1) {
    //     int i = (start_index + collisions) % map->capacity;

    //     if (map->items[i].key != NULL) {
    //         collisions++;
    //         continue;
    //     }

    //     map->items[i].key = malloc(sizeof *key);

    //     if (map->items[i].key == NULL)
    //         goto error;

    //     map->items[i].key = key;
    //     map->items[i].value = malloc(sizeof *value);

    //     if (map->items[i].value == NULL)
    //         goto error;

    //     map->items[i].value = value;
    //     return;
    // }

    while (1) {
        int i = (start_index + collisions) % map->capacity;

        if (map->items[i] != NULL) {
            collisions++;
            continue;
        }

        map->items[i]->key = malloc(sizeof *key);

        if (map->items[i]->key == NULL)
            goto error;

        map->items[i]->key = key;
        map->items[i]->value = malloc(sizeof *value);

        if (map->items[i]->value == NULL)
            goto error;

        map->items[i]->value = value;
        return;
    }

    error:
        free_hashmap(map);
        die(__func__, ERR_NULL_VALUE);
}

char*
get_key(HashMapT* map, char* key)
{
    if (map == NULL || key == NULL) {
        free_hashmap(map);
        die(__func__, ERR_NULL_VALUE);
    }

    int start_index = gen_hash(key) % map->capacity;
    int collisions = 0;

    while (1) {
        int i = (start_index + collisions) % map->capacity;

        // if (map->items[i].key == key)
        //     return map->items[i].value;

        if (map->items[i] != NULL)
            if (map->items[i]->key == key)
                return map->items[i]->value;

        collisions++;
    }
}

// Removes all keys and values from hashmap
void
clear(HashMapT* map)
{
    if (map == NULL)
        die(__func__, ERR_NULL_VALUE);

    for (int i = 0; i < map->capacity; i++) {
        if (map->items[i] != NULL) {
            free(map->items[i]->key);
            free(map->items[i]->value);
            map->items[i] = NULL;
        }
        // free(map->items[i].key);
        // free(map->items[i].value);
        // map->items[i].key = NULL;
        // map->items[i].value = NULL;
    }

    return;
}

// INTERNAL FUNCTION
// Generates a unique hash for every key provided
int
gen_hash(char* key)
{
    if (key == NULL)
        die(__func__, ERR_NULL_VALUE);

    int hash = 0;

    for (int i = 0; i < strlen(key); i++) {
        hash += key[i];
    }

    return hash;
}

// INTERNAL FUNCTION
// Deallocates hashmap from memory
void
free_hashmap(HashMapT* map)
{
    if (map != NULL) {
        free(map->items);
        free(map);
    }

    return;
}