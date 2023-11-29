#ifndef LIST_H
#define LIST_H

#include "token.h"

struct token_node
{
    Token token;
    struct token_node* next;
};

typedef struct
{
    struct token_node* head;
}List;

List* list_init();

int list_empty(struct token_node* head);

List* list_push(List* list, Token* token);

struct token_node* list_at(List* list, int index);

#endif