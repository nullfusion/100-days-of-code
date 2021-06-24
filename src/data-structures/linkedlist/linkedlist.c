#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <linkedlist.h>
#include <utils.h>


// Allocates a new Node in memory with the given values and returns its pointer
Node*
new_node(NodeItem item, Node* next, Node* prev)
{
    Node* n = xmalloc(sizeof *n);
    n->item = item;
    n->next = next;
    n->prev = prev;
    return n;
}

// Allocates a new LinkedList in memory and returns its pointer
LinkedList*
new_linkedlist(void)
{
    LinkedList* ll = xmalloc(sizeof *ll);
    ll->head = NULL;
    ll->tail = NULL;
    ll->size = 0;
    return ll;
}

// Returns true if given list is empty
bool
is_empty(LinkedList* ll)
{
    return ll->head == NULL && ll->tail == NULL && ll->size == 0;
}

// Appends the given item to the list
void
push_back(LinkedList* ll, NodeItem item)
{
    if (is_empty(ll)) {
        ll->head = new_node(item, NULL, NULL);
        ll->tail = ll->head;
        ll->size++;
        return;
    }

    ll->tail->next = new_node(item, NULL, ll->tail);
    ll->tail = ll->tail->next;
    ll->size++;
    return;
}

// Prepends the given item to the list
void
push_front(LinkedList* ll, NodeItem item)
{
    if (is_empty(ll)) {
        push_back(ll, item);
        return;
    }

    ll->head = new_node(item, ll->head, NULL);
    ll->head->next->prev = ll->head;
    ll->size++;
    return;
}

// Removes and returns the last item of the list
NodeItem
pop_back(LinkedList* ll)
{
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
    die("list not long enough to pop back");
}

// Removes and returns the first item of the list
NodeItem
pop_front(LinkedList* ll)
{
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
    die("list not long enough to pop front");
}

// // TODO
// // Reverses the list
// void
// reverse(LinkedList* ll)
// {}

// // TODO
// // Returns the nth item from the end of the list
// NodeItem
// nth_item_from_end(LinkedList* ll, int n)
// {}

// // TODO
// // Inserts given item at index
// void
// insert(LinkedList* ll, int index, NodeItem item)
// {}

// // TODO
// // Removes the first item in the list equal to the given item
// void
// remove_item(LinkedList* ll, NodeItem item)
// {}

// // TODO
// // Removes and returns the item at the given index
// NodeItem
// remove_index(LinkedList* ll, int index)
// {}

// INTERNAL FUNCTION
// Deallocates linkedlist from memory
void
free_linkedlist(LinkedList* ll)
{
    for (Node* n = ll->head; n != NULL; n = n->next)
        free(n);

    free(ll);
    return;
}