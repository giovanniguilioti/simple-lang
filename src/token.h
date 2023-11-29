#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>

typedef enum
{
    TOKEN_NUM,
    TOKEN_RPAREN,
    TOKEN_LPAREN,
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_MULT,
    TOKEN_DIV,
    TOKEN_END
}TokenType; 

typedef struct token
{
    TokenType type;

    char* value;
}Token;

Token* token_init(int type, char* s);

#endif