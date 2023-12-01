#include "parser.h"
#include "list.h"
#include "ast.h"
#include "token.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct parser* parser_init(struct list* list)
{
    struct parser* parser = calloc(1, sizeof(struct parser));
    parser->tokens = list;
    parser->count = 0;
    return parser;
}

struct token current(struct parser* parser)
{
    return list_at(parser->tokens, parser->count)->token;
}

char* next(struct parser* parser)
{
    return list_at(parser->tokens, parser->count)->token.value;
}

char* consume(struct parser* parser)
{
    if(strcmp(list_at(parser->tokens, parser->count)->token.value, "$") == 0)
    {
        exit(1);
    }

    char* temp = list_at(parser->tokens, parser->count)->token.value;
    parser->count++;
    return temp;
}

void error()
{
    printf("syntax error.:");
    exit(1);
}

int expect(struct parser* parser, char* token)
{
    if (strcmp(next(parser), token) == 0)
    {
        consume(parser);
    }
    else
        error();

    return 1;
}

struct ast_node* stmts(struct parser* parser)
{
    if (current(parser).type == TOKEN_ID || current(parser).type == TOKEN_NUM)
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
    if (current(parser).type == TOKEN_ID)
        return assignment(parser);
}

struct ast_node* assignment(struct parser* parser)
{
    char* id = consume(parser);
    if(strcmp(next(parser), "=") == 0)
    {
        char* token = consume(parser);
        struct ast_node* assignment_node = ast_op(token[0], ast_id(id), expr(parser));
        return assignment_node;
    }
}

struct ast_node* expr(struct parser* parser)
{
    struct ast_node* left = term(parser);
    return expr_tail(parser, left);
}

struct ast_node* expr_tail(struct parser* parser, struct ast_node* left)
{
    if(strcmp(next(parser), "+") == 0 || strcmp(next(parser), "-") == 0 )
    {
        char* token = consume(parser);
        struct ast_node* right = term(parser);
        struct ast_node* new = ast_op(token[0], left, right);
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
    if(strcmp(next(parser), "*") == 0 || strcmp(next(parser), "/") == 0 )
    {
        char* token = consume(parser);
        struct ast_node* right = factor(parser);
        struct ast_node* new = ast_op(token[0], left, right);
        return term_tail(parser, new);
    }
    return left;
}

struct ast_node* factor(struct parser* parser)
{
    struct ast_node* t;
    if(atoi(next(parser)))
    {
        t = ast_num(atoi(next(parser)));
        consume(parser);
        return t;
    }
    else if(strcmp(next(parser), "(") == 0)
    {
        consume(parser);
        t = expr(parser);
        expect(parser, ")");
        return t;
    }
    else if(current(parser).type == TOKEN_ID)
    {
        char* id = consume(parser);
        t = ast_id(id);
        return t;
    }
    else
    {
        error();
    }
}
