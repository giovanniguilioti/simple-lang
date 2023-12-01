#ifndef LEXER_H
#define LEXER_H

#include "token.h"

struct lexer
{
    char c;
    unsigned int i;
    char* contents;
};

struct lexer* lexer_init(char* contents);

void lexer_advance(struct lexer* lexer);

void lexer_skip_whitespace(struct lexer* lexer);

struct token* lexer_get_next_token(struct lexer* lexer);

struct token* lexer_collect_num(struct lexer* lexer, int minus);

struct token* lexer_advance_with_token(struct lexer* lexer, struct token* token);

char* lexer_get_current_char_as_string(struct lexer* lexer);

struct token* lexer_handle_minus(struct lexer* lexer);

struct token* lexer_collect_identifier(struct lexer* lexer);

#endif