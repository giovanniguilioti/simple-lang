#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include "token_list.h"

struct parser
{
    struct token_list* tokens;
    struct token* lookahead;
    int count;
};

struct parser* parser_init(struct token_list* list);

void match(struct parser* parser, char* token);

void error(struct parser* parser);

struct ast_node* stmts(struct parser* parser);

struct ast_node* stmt(struct parser* parser);

struct ast_node* assignment(struct parser* parser);

struct ast_node* expr(struct parser* parser);

struct ast_node* expr_tail(struct parser* parser, struct ast_node* left);

struct ast_node* term(struct parser* parser);

struct ast_node* term_tail(struct parser* parser, struct ast_node* left);

struct ast_node* factor(struct parser* parser);

#endif