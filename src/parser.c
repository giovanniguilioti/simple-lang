#include "parser.h"
#include "ast.h"
#include "token.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct parser* parser_init(struct token_list* list)
{
    struct parser* parser = calloc(1, sizeof(struct parser));
    parser->tokens = list;
    parser->count = 0;
    parser->lookahead = list_at(list, parser->count);
    return parser;
}

static void parser_move(struct parser* parser)
{
    (parser->count)++;
    parser->lookahead = list_at(parser->tokens, parser->count);

    if(parser->lookahead->type == TOKEN_END)
        return;
}

void match(struct parser* parser, char* token)
{
    if(strcmp(parser->lookahead->value, token) == 0)
        parser_move(parser);
    else
        error(parser);
}

void error(struct parser* parser)
{
    printf("syntax error\ntoken not expected: %s", parser->lookahead->value);
    exit(1);
}

struct ast_node* stmts(struct parser* parser)
{
    if (parser->lookahead->type == TOKEN_ID || parser->lookahead->type == TOKEN_NUM)
    {
        struct ast_node* stmt_node = stmt(parser);
        struct ast_node* stmts_tail_node = stmts(parser);

        if (stmts_tail_node != NULL) 
        {
            struct ast_node* stmts_node = ast_empty(AST_EMPTY);
            stmts_node->left = stmt_node;
            stmts_node->right = stmts_tail_node;
            return stmts_node;
        }

        return stmt_node;
    }

    return NULL;
}

struct ast_node* stmt(struct parser* parser)
{
    if (parser->lookahead->type == TOKEN_ID)
        return assignment(parser);
    else
        error(parser);
}

struct ast_node* assignment(struct parser* parser)
{
    char* id = parser->lookahead->value;
    match(parser, parser->lookahead->value);
    if(parser->lookahead->type == TOKEN_ASSIGN)
    {
        match(parser, parser->lookahead->value);
        struct ast_node* assignment_node = ast_op('=', ast_id(id), expr(parser));
        return assignment_node;
    }
    else
        error(parser);
}

struct ast_node* expr(struct parser* parser)
{
    struct ast_node* left = term(parser);
    return expr_tail(parser, left);
}

struct ast_node* expr_tail(struct parser* parser, struct ast_node* left)
{
    if(parser->lookahead->type == TOKEN_ADD)
    {
        match(parser, "+");
        struct ast_node* right = term(parser);
        struct ast_node* new = ast_op('+', left, right);
        return expr_tail(parser, new);
    }
    else if(parser->lookahead->type == TOKEN_SUB)
    {
        match(parser, "-");
        struct ast_node* right = term(parser);
        struct ast_node* new = ast_op('-', left, right);
        return expr_tail(parser, new);
    }

    return left;
}

struct ast_node* term(struct parser* parser)
{
    struct ast_node* left = factor(parser);
    return term_tail(parser, left);
}

struct ast_node* term_tail(struct parser* parser, struct ast_node* left)
{
    if(parser->lookahead->type == TOKEN_MULT)
    {
        match(parser, "*");
        struct ast_node* right = factor(parser);
        struct ast_node* new = ast_op('*', left, right);
        return term_tail(parser, new);
    }
    else if(parser->lookahead->type == TOKEN_DIV)
    {
        match(parser, "/");
        struct ast_node* right = factor(parser);
        struct ast_node* new = ast_op('/', left, right);
        return term_tail(parser, new);
    }

    return left;
}

struct ast_node* factor(struct parser* parser)
{
    struct ast_node* t;
    if(parser->lookahead->type == TOKEN_NUM)
    {
        t = ast_num(atoi(parser->lookahead->value));
        match(parser, parser->lookahead->value);
        return t;
    }
    else if(parser->lookahead->type == TOKEN_LPAREN)
    {
        match(parser, parser->lookahead->value);
        t = expr(parser);
        match(parser, ")");
        return t;
    }
    else if(parser->lookahead->type == TOKEN_ID)
    {
        char* id = parser->lookahead->value;
        match(parser, parser->lookahead->value);
        t = ast_id(id);
        return t;
    }
    else
    {
        error(parser);
    }
}
