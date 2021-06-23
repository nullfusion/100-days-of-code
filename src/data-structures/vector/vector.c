#include <stdlib.h>
#include <utils.h>
#include <vector.h>
#include <math.h>

// Returns a new vector with capacity equal to 1
Vector*
new_vector(void)
{
    Vector* vec = xmalloc(sizeof *vec);
    vec->arr = xmalloc(sizeof *(vec->arr));
    vec->capacity = 1;
    vec->size = 0;
    return vec;
}

// Appends the given item to the list
void
push_back(Vector* vec, VectorItem item)
{
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
    if (vec->size > 0) {
        VectorItem item = vec->arr[vec->size-1];
        vec->size--;

        if (vec->size == round(vec->capacity/4.0))
            resize(vec, vec->capacity/2);
        
        return item;
    }

    free_vector(vec);
    die("vector not long enough to pop back");
}

// Removes and returns the first item of the list
VectorItem
pop_front(Vector* vec)
{
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
    die("vector not long enough to pop front");
}

// Finds and returns the index of first list item equal to the given item
// If none are found, returns -1
int
find_item(Vector* vec, VectorItem item)
{
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
    if (index < 0 || index > vec->size-1) {
        free_vector(vec);
        die("index out of bounds");
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
    if (index < 0 || index > vec->size-1) {
        free_vector(vec);
        die("index out of bounds");
    }

    return vec->arr[index];
}


// INTERNAL FUNCTION
// Resizes the array list to fit the given new_size
void
resize(Vector* vec, int new_size)
{
    vec->arr = xrealloc(vec->arr, new_size * sizeof *(vec->arr));
    vec->capacity = new_size;
    return;
}

// INTERNAL FUNCTION
// Deallocates vector from memory
void
free_vector(Vector *vec)
{
    free(vec->arr);
    free(vec);
    return;
}