#ifndef XDOC_DS_VECTOR_H
#define XDOC_DS_VECTOR_H

typedef int VectorItem;
typedef struct Vector Vector;

struct Vector {
    VectorItem* arr;
    int capacity;
    int size;
};

Vector* new_vector(void);
void push_back(Vector* vec, VectorItem item);
void push_front(Vector* vec, VectorItem item);
VectorItem pop_back(Vector* vec);
VectorItem pop_front(Vector* vec);
VectorItem get(Vector* vec, int index);
int find_item(Vector* vec, VectorItem item);
void remove_item(Vector* vec, VectorItem item);
void insert_item(Vector* vec, int index, VectorItem item);

// INTERNAL FUNCTIONS
void resize(Vector* vec, int new_size);
void free_vector(Vector* vec);

#endif