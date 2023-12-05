#ifndef LIST_H
#define LIST_H

#include "token.h"

struct token_node
{
    struct token token;
    struct token_node* next;
};

struct token_list
{
    struct token_node* head;
};

struct token_list* list_init();

int list_empty(struct token_node* head);

struct token_list* list_push(struct token_list* list, struct token* token);

struct token* list_at(struct token_list* list, int index);

#endif