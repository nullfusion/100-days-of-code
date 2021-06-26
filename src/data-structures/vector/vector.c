#include <stdlib.h>
#include <math.h>

#include "data-structures/vector/vector.h"
#include "utils/utils.h"

// Returns a new vector with capacity equal to 1
Vector*
new_vector(void)
{
    Vector* vec = malloc(sizeof *vec);

    if (vec == NULL)
        die(__func__, ERR_ALLOC_FAILED);

    vec->arr = malloc(sizeof *(vec->arr));

    if (vec->arr == NULL) {
        free_vector(vec);
        die(__func__, ERR_ALLOC_FAILED);
    }

    vec->capacity = 1;
    vec->size = 0;
    return vec;
}

// Appends the given item to the list
void
push_back(Vector* vec, VectorItem item)
{
    if (vec == NULL)
        die(__func__, ERR_NULL_VALUE);

    if (vec->size < vec->capacity) {
        vec->arr[vec->size] = item;
        vec->size++;
        return;
    }

    resize(vec, 2*vec->capacity);
    push_back(vec, item);
    return;
}

// Prepends the given item to the list
void
push_front(Vector* vec, VectorItem item)
{
    if (vec == NULL)
        die(__func__, ERR_NULL_VALUE);

    if (vec->size < vec->capacity) {
        for (int i = vec->size; i > 0; i--)
            vec->arr[i] = vec->arr[i-1];

        vec->arr[0] = item;
        vec->size++;
        return;
    }

    resize(vec, 2*vec->capacity);
    push_front(vec, item);
    return;
}

// Removes and returns the last item of the list
VectorItem
pop_back(Vector* vec)
{
    if (vec == NULL)
        die(__func__, ERR_NULL_VALUE);

    if (vec->size > 0) {
        VectorItem item = vec->arr[vec->size-1];
        vec->size--;

        if (vec->size == round(vec->capacity/4.0))
            resize(vec, vec->capacity/2);
        
        return item;
    }

    free_vector(vec);
    die(__func__, ERR_OUT_OF_BOUNDS);
}

// Removes and returns the first item of the list
VectorItem
pop_front(Vector* vec)
{
    if (vec == NULL)
        die(__func__, ERR_NULL_VALUE);

    if (vec->size > 0) {
        VectorItem item = vec->arr[0];

        for (int i = 0; i <= vec->size-2; i++)
            vec->arr[i] = vec->arr[i+1];

        vec->size--;

        if (vec->size == round(vec->capacity/4.0))
            resize(vec, vec->capacity/2);
        
        return item;
    }

    free_vector(vec);
    die(__func__, ERR_OUT_OF_BOUNDS);
}

// Finds and returns the index of first list item equal to the given item
// If none are found, returns -1
int
find_item(Vector* vec, VectorItem item)
{
    if (vec == NULL)
        die(__func__, ERR_NULL_VALUE);

    if (vec->size > 0) {
        for (int i = 0; i < vec->size; i++) {
            if (vec->arr[i] == item)
                return i;
        }
    }

    return -1;
}

// Removes any and every list item equal to the given item and rearranges the list
void
remove_item(Vector* vec, VectorItem item)
{
    if (vec == NULL)
        die(__func__, ERR_NULL_VALUE);

    if (vec->size > 0) {
        int count = 0;

        for (int i = 0; i < vec->size; i++) {
            if (count > 0)
                vec->arr[i-count] = vec->arr[i];

            if (vec->arr[i] == item)
                count++;
        }

        vec->size -= count;

        if (vec->size == round(vec->capacity/4.0))
            resize(vec, vec->capacity/2);
    }
}

// Inserts item at the given index and shifts index item and trailing items to the right
void
insert_item(Vector* vec, int index, VectorItem item)
{
    if (vec == NULL)
        die(__func__, ERR_NULL_VALUE);

    if (index < 0 || index > vec->size-1) {
        free_vector(vec);
        die(__func__, ERR_OUT_OF_BOUNDS);
    }

    if (vec->size < vec->capacity) {
        for (int i = vec->size; i > index; i--)
            vec->arr[i] = vec->arr[i-1];
        
        vec->arr[index] = item;
        vec->size++;
        return;
    }

    resize(vec, 2*vec->capacity);
    insert_item(vec, index, item);
    return;
}

// Returns the item at the given index
VectorItem
get(Vector* vec, int index)
{
    if (vec == NULL)
        die(__func__, ERR_NULL_VALUE);

    if (index < 0 || index > vec->size-1) {
        free_vector(vec);
        die(__func__, ERR_OUT_OF_BOUNDS);
    }

    return vec->arr[index];
}


// INTERNAL FUNCTION
// Resizes the array list to fit the given new_size
void
resize(Vector* vec, int new_size)
{
    vec->arr = realloc(vec->arr, new_size * sizeof *(vec->arr));

    if (vec->arr == NULL) {
        free_vector(vec);
        die(__func__, ERR_ALLOC_FAILED);
    }

    vec->capacity = new_size;
    return;
}

// INTERNAL FUNCTION
// Deallocates vector from memory
void
free_vector(Vector *vec)
{
    if (vec != NULL) {
        free(vec->arr);
        free(vec);
    }

    return;
}