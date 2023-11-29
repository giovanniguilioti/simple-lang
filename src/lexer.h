#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct lexer
{
    char c;
    unsigned int i;
    char* contents;
} Lexer;

Lexer* lexer_init(char* contents);

void lexer_advance(Lexer* lexer);

void lexer_skip_whitespace(Lexer* lexer);

Token* lexer_get_next_token(Lexer* lexer);

Token* lexer_collect_num(Lexer* lexer, int minus);

Token* lexer_advance_with_token(Lexer* lexer, Token* token);

char* lexer_get_current_char_as_string(Lexer* lexer);

Token* lexer_handle_minus(Lexer* lexer);

#endif