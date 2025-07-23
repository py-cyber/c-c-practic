#ifndef INTRUSIVE_LIST_H
#define INTRUSIVE_LIST_H

typedef struct intrusive_node {
    struct intrusive_node* prev;
    struct intrusive_node* next;
} intrusive_node;

typedef struct {
    intrusive_node head;
} intrusive_list;

void init_list(intrusive_list* l);

void add_node(intrusive_node* after, intrusive_node* node);

void remove_node(intrusive_node* node);

int get_length(const intrusive_list* l);

#endif
