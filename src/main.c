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

    Lexer* lexer = lexer_init("-9 * (5 - 2)$");
    Token* token = (void*)0;

    List* list = list_init();

    while((token = lexer_get_next_token(lexer)) != (void*)0)
    {
        list_push(list, token);
        printf("TOKEN[%d, %s]\n", token->type, token->value);
    }

    Parser* parser = parser_init(list);
    struct ast_node* ast = expr(parser);
    ast_print(ast, 0);
}
