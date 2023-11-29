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
    term(parser);
    expr_rest(parser);
}

struct ast_node* expr_rest(Parser* parser)
{
    if(strcmp(next(parser), "+") == 0 || strcmp(next(parser), "-") == 0 )
    {
        consume(parser);
        term(parser);
    }
}

struct ast_node* term(Parser* parser)
{
    factor(parser);
    term_rest(parser);
}

struct ast_node* term_rest(Parser* parser)
{
    if(strcmp(next(parser), "*") == 0 || strcmp(next(parser), "/") == 0 )
    {
        consume(parser);
        factor(parser);
    }
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
    }
    else
    {
        error();
    }
}

/*void term(Parser* parser)
{
    struct ast_node* n1 = factor(parser);
    struct ast_node* n2 = term_tail(parser);
}

struct ast_node* term_tail(Parser* parser)
{
    if(strcmp(next(parser), "+") == 0 || strcmp(next(parser), "-") == 0 )
    {
        consume(parser);
        term(parser);
    }
}

void factor(Parser* parser)
{
    primary(parser);
    factor_tail(parser);
}

void factor_tail(Parser* parser)
{
    if(strcmp(next(parser), "*") == 0 || strcmp(next(parser), "/") == 0 )
    {
        consume(parser);
        factor(parser);
    }
}

void primary(Parser* parser)
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
        t = term(parser);
        expect(parser, ")");
        return t;
    }
    else
    {
        error();
    }
}
*/