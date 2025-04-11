#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data);
void insert_end(Node** head, int data);
void print_list(Node* head);
void free_list(Node* head);
void insert_front(Node** head, int data);
void delete_node(Node** head, int data);
Node* find_node(Node* head, int data);
void insert_at(Node** head, int index, int data);


#endif
