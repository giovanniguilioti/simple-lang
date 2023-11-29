#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "token.h"
#include "lexer.h"
#include "list.h"
#include "parser.h"

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
    expr(parser);
}
