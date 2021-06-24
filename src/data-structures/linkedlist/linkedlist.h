#ifndef XDOC_LINKEDLIST_H
#define XDOC_LINKEDLIST_H

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
NodeItem pop_back(LinkedList* ll);
NodeItem pop_front(LinkedList* ll);
NodeItem* items(LinkedList* ll);
NodeItem* items_from_end(LinkedList* ll);

// INTERNAL FUCNTIONS
void free_linkedlist(LinkedList* ll);

#endif