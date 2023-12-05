#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>

enum token_type
{
    TOKEN_ID,
    TOKEN_NUM,
    TOKEN_SEMICOLON,
    TOKEN_RPAREN,
    TOKEN_LPAREN,
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_MULT,
    TOKEN_DIV,
    TOKEN_ASSIGN,
    TOKEN_VARDECL,
    TOKEN_END
}; 

struct token
{
    enum token_type type;

    char* value;
};

struct token* token_init(int type, char* s);

#endif