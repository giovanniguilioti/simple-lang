#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include "list.h"

struct parser
{
    struct list* tokens;
    int count;
};

struct parser* parser_init(struct list* list);

char* next(struct parser* rec);

char* consume(struct parser* rec);

int expect(struct parser* rec, char* token);

void error();

struct ast_node* stmts(struct parser* parser);

struct ast_node* stmt(struct parser* parser);

struct ast_node* assignment(struct parser* parser);

struct ast_node* expr(struct parser* parser);

struct ast_node* expr_tail(struct parser* parser, struct ast_node* left);

struct ast_node* term(struct parser* parser);

struct ast_node* term_tail(struct parser* parser, struct ast_node* left);

struct ast_node* factor(struct parser* parser);

#endif