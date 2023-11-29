#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include "list.h"

typedef struct
{
    List* tokens;
    int count;
}Parser;

Parser* parser_init(List* list);

char* next(Parser* rec);

char* consume(Parser* rec);

void error();

int expect(Parser* rec, char* token);

struct ast_node* expr(Parser* parser);

struct ast_node* expr_rest(Parser* parser);

struct ast_node* term(Parser* parser);

struct ast_node* term_rest(Parser* parser);

struct ast_node* factor(Parser* parser);

#endif