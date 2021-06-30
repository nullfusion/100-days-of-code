#include <stdlib.h>
#include <stdbool.h>

#include "data-structures/hashmap/hashmap.h"
#include "utils/utils.h"

// Allocates and returns a pointer to the hashmap
HashMapT*
new_hashmap(void)
{
    int init_cap = 10;
    HashMapT* map = malloc(sizeof *map);

    if (map == NULL)
        goto alloc_failed;

    map->items = malloc(sizeof *(map->items) * init_cap);

    if (map->items == NULL)
        goto alloc_failed;

    for (int i = 0; i < init_cap; i++) {
        map->items[i].key = NULL;
        map->items[i].value = NULL;
    }

    map->capacity = init_cap;
    map->size = 0;
    return map;

    alloc_failed:
        free_hashmap(map);
        die(__func__, ERR_ALLOC_FAILED);
}

// Returns the value of the given key
// Returns NULL if key is not found
char*
get(HashMapT* map, char* key, bool remove)
{
    if (map == NULL || key == NULL) {
        free_hashmap(map);
        die(__func__, ERR_NULL_VALUE);
    }

    int index = gen_hash(key) % map->capacity;
    int collisions = 0;

    while (1) {
        int i = (index + collisions) % map->capacity;

        if (collisions > map->capacity)
            break;

        if (map->items[i].key != key) {
            collisions++;
            continue;
        }

        if (remove == true) {
            char* value = map->items[i].value;
            map->items[i].key = NULL;
            map->items[i].value = NULL;
            map->size--;
            return value;
        }

        return map->items[i].value;
    }

    return NULL;
}

// Inserts the given key-value pair in hashmap
// TODO: Fix inserting same key in multiple places
void
put(HashMapT* map, char* key, char* value)
{
    if (map == NULL || key == NULL || value == NULL) {
        free_hashmap(map);
        die(__func__, ERR_NULL_VALUE);
    }

    // TODO: Use warn instead of die
    if (map->size == map->capacity) {
        free_hashmap(map);
        die(__func__, ERR_OUT_OF_BOUNDS);
    }

    int index = gen_hash(key) % map->capacity;
    int collisions = 0;

    for (;;) {
        int i = (index + collisions) % map->capacity;

        if (map->items[i].key != NULL) {
            collisions++;
            continue;
        }

        map->items[i].key = key;
        map->items[i].value = value;
        map->size++;
        return;
    }
}

// Removes all key-value pairs from hashmap
void
clear(HashMapT* map)
{
    if (map == NULL)
        die(__func__, ERR_NULL_VALUE);

    for (int i = 0; i < map->capacity; i++) {
        map->items[i].key = NULL;
        map->items[i].value = NULL;
    }

    return;
}

// INTERNAL FUNCTION
// Returns a unique hash for each key
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
    if (map == NULL)
        die(__func__, ERR_NULL_VALUE);

    free(map->items);
    free(map);
    return;
}