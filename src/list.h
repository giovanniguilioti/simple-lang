#ifndef LIST_H
#define LIST_H

#include "token.h"

struct token_node
{
    struct token token;
    struct token_node* next;
};

struct list
{
    struct token_node* head;
};

struct list* list_init();

int list_empty(struct token_node* head);

struct list* list_push(struct list* list, struct token* token);

struct token_node* list_at(struct list* list, int index);

#endif