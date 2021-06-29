#ifndef XDOC_HASHMAP_H
#define XDOC_HASHMAP_H

#include <stdbool.h>

typedef struct HashMap HashMapT;
typedef struct HashMapItem HashMapItemT;

struct HashMap {
    HashMapItemT* items;
    int capacity;
    int size;
};

struct HashMapItem {
    char* key;
    char* value;
};

HashMapT* new_hashmap(void);

char* get(HashMapT* map, char* key, bool remove);

void put(HashMapT* map, char* key, char* value);
void clear(HashMapT* map);

// INTERNAL FUNCTIONS
int gen_hash(char* key);
void free_hashmap(HashMapT* map);

#endif