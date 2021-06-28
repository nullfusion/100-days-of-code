
typedef struct HashMapItem HashMapItemT;
typedef struct HashMap HashMapT;

struct HashMapItem {
    char* key;
    char* value;
};

struct HashMap {
    HashMapItemT** items;
    int capacity;
    int size;
};

HashMapT* new_hashmap(int capacity);

char* get_key(HashMapT* map, char* key);

void put_key(HashMapT* map, char* key, char* value);
void remove_key(HashMapT* map, char* key);
void clear(HashMapT* map);

// INTERNAL FUNCTIONS
void free_hashmap(HashMapT* map);
int gen_hash(char* key);