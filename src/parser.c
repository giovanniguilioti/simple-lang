#include "parser.h"
#include "list.h"
#include "ast.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

Parser* parser_init(List* list)
{
    Parser* parser = calloc(1, sizeof(Parser));
    parser->tokens = list;
    parser->count = 0;
    return parser;
}

char* next(Parser* parser)
{
    return list_at(parser->tokens, parser->count)->token.value;
}

char* consume(Parser* parser)
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
    printf("syntax error.");
    exit(1);
}

int expect(Parser* parser, char* token)
{
    if (strcmp(next(parser), token) == 0)
    {
        consume(parser);
    }
    else
        error();

    return 1;
}

struct ast_node* expr(Parser* parser)
{
    struct ast_node* left = term(parser);
    return expr_tail(parser, left);
}

struct ast_node* expr_tail(Parser* parser, struct ast_node* left)
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

struct ast_node* term(Parser* parser)
{
    struct ast_node* left = factor(parser);
    return term_tail(parser, left);
}

struct ast_node* term_tail(Parser* parser, struct ast_node* left)
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

struct ast_node* factor(Parser* parser)
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
    else
    {
        error();
    }
}
