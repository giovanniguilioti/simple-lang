#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

Lexer* lexer_init(char* contents)
{
    Lexer* lexer = calloc(1, sizeof(struct lexer));
    lexer->contents = contents;
    lexer->i = 0;
    lexer->c = contents[lexer->i];

    return lexer;
}

void lexer_advance(Lexer* lexer)
{
    if(lexer->c != '\0' && lexer->i < strlen(lexer->contents))
    {
        lexer->i += 1;
        lexer->c = lexer->contents[lexer->i];
    }
}

void lexer_skip_whitespace(Lexer* lexer)
{
    while(lexer->c == ' ' || lexer->c == 10)
    {
        lexer_advance(lexer);
    }
}

Token* lexer_get_next_token(Lexer* lexer)
{
    while(lexer->c != '\0' && lexer->i < strlen(lexer->contents))
    {
        if(lexer->c == ' ' || lexer->c == 10)
            lexer_skip_whitespace(lexer);

        if(isdigit(lexer->c))
            return lexer_collect_num(lexer, 0);

        switch(lexer->c)
        {
            case '+':
                return lexer_advance_with_token(lexer, token_init(TOKEN_ADD, lexer_get_current_char_as_string(lexer))); break;
            case '-':
                return lexer_handle_minus(lexer);
                break;
            case '*':
                return lexer_advance_with_token(lexer, token_init(TOKEN_MULT, lexer_get_current_char_as_string(lexer))); break;
            case '/':
                return lexer_advance_with_token(lexer, token_init(TOKEN_DIV, lexer_get_current_char_as_string(lexer))); break;
            case '(':
                return lexer_advance_with_token(lexer, token_init(TOKEN_LPAREN, lexer_get_current_char_as_string(lexer))); break;
            case ')':
                return lexer_advance_with_token(lexer, token_init(TOKEN_RPAREN, lexer_get_current_char_as_string(lexer))); break;
            case '$':
                return lexer_advance_with_token(lexer, token_init(TOKEN_END, lexer_get_current_char_as_string(lexer))); break;
        }

    }

    return (void*)0;
}

Token* lexer_advance_with_token(Lexer* lexer, Token* token)
{
    lexer_advance(lexer);

    return token;
}

char* lexer_get_current_char_as_string(Lexer* lexer)
{
    char* str = calloc(2, sizeof(char));
    str[0] = lexer->c;
    str[1] = '\0';

    return str;
}

Token* lexer_collect_num(Lexer* lexer, int minus)
{
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    if(minus)
    {
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        lexer_advance(lexer);
    }
    
    while (isdigit(lexer->c))
    {
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        lexer_advance(lexer);
    }

    return token_init(TOKEN_NUM, value);
}

Token* lexer_handle_minus(Lexer* lexer)
{
    if(isdigit(lexer->contents[lexer->i+1]))
        return lexer_collect_num(lexer, 1);

    return lexer_advance_with_token(lexer, token_init(TOKEN_SUB, lexer_get_current_char_as_string(lexer)));
}