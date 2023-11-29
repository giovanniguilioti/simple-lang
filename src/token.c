#include "token.h"
#include <stdlib.h>

Token* token_init(int type, char* value)
{
    Token* token = calloc(1, sizeof(struct token));
    token->type = type;
    token->value = value;

    return token;
}