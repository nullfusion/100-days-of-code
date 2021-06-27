#ifndef XDOC_LINKEDLIST_H
#define XDOC_LINKEDLIST_H

#include <stdbool.h>

typedef int NodeItem;
typedef struct LinkedList LinkedList;
typedef struct Node Node;

struct Node {
    NodeItem item;
    Node* next;
    Node* prev;
};

struct LinkedList {
    Node* head;
    Node* tail;
    int size;
};

Node* new_node(NodeItem item, Node* next, Node* prev);
LinkedList* new_linkedlist(void);

bool is_empty(LinkedList* ll);

void push_back(LinkedList* ll, NodeItem item);
void push_front(LinkedList* ll, NodeItem item);
void reverse_list(LinkedList* ll);
void insert_item(LinkedList* ll, int index, NodeItem item);
void remove_item(LinkedList* ll, NodeItem item);

NodeItem pop_back(LinkedList* ll);
NodeItem pop_front(LinkedList* ll);
NodeItem remove_index(LinkedList* ll, int index);

// INTERNAL FUCNTIONS
void free_linkedlist(LinkedList* ll);
bool is_within_range(LinkedList* ll, int index);
Node* get_node_at(LinkedList* ll, int index);

#endif