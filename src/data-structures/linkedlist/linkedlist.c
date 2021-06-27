#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "data-structures/linkedlist/linkedlist.h"
#include "utils/utils.h"


// Allocates a new Node in memory with the given values and returns its pointer
Node*
new_node(NodeItem item, Node* next, Node* prev)
{
    Node* n = malloc(sizeof *n);

    if (n == NULL)
        return NULL;

    n->item = item;
    n->next = next;
    n->prev = prev;
    return n;
}

// Allocates a new LinkedList in memory and returns its pointer
LinkedList*
new_linkedlist(void)
{
    LinkedList* ll = malloc(sizeof *ll);

    if (ll == NULL)
        die(__func__, ERR_ALLOC_FAILED);

    ll->head = NULL;
    ll->tail = NULL;
    ll->size = 0;
    return ll;
}

// Returns true if given list is empty
bool
is_empty(LinkedList* ll)
{
    if (ll == NULL)
        die(__func__, ERR_NULL_VALUE);

    return ll->head == NULL && ll->tail == NULL && ll->size == 0;
}

// Appends the given item to the list
void
push_back(LinkedList* ll, NodeItem item)
{
    if (ll == NULL)
        die(__func__, ERR_NULL_VALUE);

    if (is_empty(ll)) {
        ll->head = new_node(item, NULL, NULL);

        if (ll->head == NULL) {
            free_linkedlist(ll);
            die(__func__, ERR_ALLOC_FAILED);
        }

        ll->tail = ll->head;
        ll->size++;
        return;
    }

    ll->tail->next = new_node(item, NULL, ll->tail);

    if (ll->tail->next == NULL) {
        free_linkedlist(ll);
        die(__func__, ERR_ALLOC_FAILED);
    }

    ll->tail = ll->tail->next;
    ll->size++;
    return;
}

// Prepends the given item to the list
void
push_front(LinkedList* ll, NodeItem item)
{
    if (ll == NULL)
        die(__func__, ERR_NULL_VALUE);

    if (is_empty(ll)) {
        push_back(ll, item);
        return;
    }

    ll->head = new_node(item, ll->head, NULL);

    if (ll->head == NULL) {
        free_linkedlist(ll);
        die(__func__, ERR_ALLOC_FAILED);
    }

    ll->head->next->prev = ll->head;
    ll->size++;
    return;
}

// Removes and returns the last item of the list
NodeItem
pop_back(LinkedList* ll)
{
    if (ll == NULL)
        die(__func__, ERR_NULL_VALUE);

    if (!is_empty(ll)) {
        if (ll->size == 1) {
            NodeItem item = ll->head->item;
            free(ll->head);

            ll->head = NULL;
            ll->tail = NULL;
            ll->size = 0;

            return item;
        }

        NodeItem item = ll->tail->item;
        Node* new_tail = ll->tail->prev;

        ll->tail->prev->next = NULL;
        ll->size--;

        free(ll->tail);
        ll->tail = new_tail;

        return item;
    }

    free_linkedlist(ll);
    die(__func__, ERR_OUT_OF_BOUNDS);
}

// Removes and returns the first item of the list
NodeItem
pop_front(LinkedList* ll)
{
    if (ll == NULL)
        die(__func__, ERR_NULL_VALUE);

    if (!is_empty(ll)) {
        if (ll->size == 1) {
            NodeItem item = pop_back(ll);
            return item;
        }

        NodeItem item = ll->head->item;
        Node* new_head = ll->head->next;

        ll->head->next->prev = NULL;
        ll->size--;

        free(ll->head);
        ll->head = new_head;

        return item;
    }

    free_linkedlist(ll);
    die(__func__, ERR_OUT_OF_BOUNDS);
}

// Reverses the list
void
reverse_list(LinkedList* ll)
{
    if (ll == NULL)
        die(__func__, ERR_NULL_VALUE);

    if (ll->size > 1) {
        Node* next;

        for (Node* node = ll->head; node != NULL; node = next) {
            next = node->next;
            node->next = node->prev;
            node->prev = next;
        }

        Node* head = ll->head;
        ll->head = ll->tail;
        ll->tail = head;
    }

    return;
}

// Inserts given item at index
void
insert_item(LinkedList* ll, int index, NodeItem item)
{
    if (index == 0) {
        push_front(ll, item);
        return;
    }

    if (ll == NULL)
        die(__func__, ERR_NULL_VALUE);

    if (!is_within_range(ll, index)) {
        free_linkedlist(ll);
        die(__func__, ERR_OUT_OF_BOUNDS);
    }

    Node* node = get_node_at(ll, index);
    Node* new = new_node(item, node, node->prev);

    if (new == NULL) {
        free_linkedlist(ll);
        die(__func__, ERR_ALLOC_FAILED);
    }

    node->prev->next = new;
    node->prev = node->prev->next;
    ll->size++;
    return;
}

// Removes and returns the item at the given index
NodeItem
remove_index(LinkedList* ll, int index)
{
    if (ll == NULL)
        die(__func__, ERR_NULL_VALUE);

    if (!is_within_range(ll, index)) {
        free_linkedlist(ll);
        die(__func__, ERR_OUT_OF_BOUNDS);
    }

    if (index == 0)
        return pop_front(ll);

    if (index == ll->size-1)
        return pop_back(ll);

    Node* node = get_node_at(ll, index);
    NodeItem item = node->item;

    node->prev->next = node->next;
    node->next->prev = node->prev;
    ll->size--;

    free(node);
    return item;
}

// TODO
// Removes the first item in the list equal to the given item
void
remove_item(LinkedList* ll, NodeItem item)
{
    if (ll == NULL)
        die(__func__, ERR_NULL_VALUE);
    
    if (ll->size > 0) {
        int i = 0;
        Node* node = ll->head;

        while (node != NULL) {
            if (node->item == item) {
                if (i == 0) {
                    pop_front(ll);
                    return;
                }

                if (i == ll->size-1) {
                    pop_back(ll);
                    return;
                }

                node->prev->next = node->next;
                node->next->prev = node->prev;
                ll->size--;

                free(node);
                return;
            }

            i++;
            node = node->next;
        }
    }

    return;
}


// INTERNAL FUNCTION
// Returns the node at the given index
Node*
get_node_at(LinkedList* ll, int index)
{
    if (!is_within_range(ll, index)) {
        free_linkedlist(ll);
        die(__func__, ERR_OUT_OF_BOUNDS);
    }

    if (index == 0)
        return ll->head;
    
    if (index == ll->size-1)
        return ll->tail;

    Node* node = ll->head->next;

    for (int i = 1; i < index; i++)
        node = node->next;

    return node;
}

// INTERNAL FUNCTION
// Returns true if given index is within bounds
bool
is_within_range(LinkedList* ll, int index)
{
    return (index >= 0 && index < ll->size);
}

// INTERNAL FUNCTION
// Deallocates linkedlist from memory
void
free_linkedlist(LinkedList* ll)
{
    if (ll != NULL) {
        for (Node* n = ll->head; n != NULL;) {
            Node* tmp = n->next;
            free(n);
            n = tmp;
        }

        free(ll);
    }

    return;
}