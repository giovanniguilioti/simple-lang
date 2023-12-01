#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "token.h"
#include "lexer.h"
#include "list.h"
#include "parser.h"
#include "ast.h"

int main()
{

    struct lexer* lexer = lexer_init("x = 10\ny = 20\nz = x + (y - 5)$");
    struct token* token = (void*)0;

    struct list* list = list_init();

    while((token = lexer_get_next_token(lexer)) != (void*)0)
    {
        list_push(list, token);
        //printf("[%d, %s]\n", token->type, token->value);
    }

    struct parser* parser = parser_init(list);
    struct ast_node* ast = stmts(parser);
    ast_print(ast, 0);
    //printf("%d", ast->type);
}
