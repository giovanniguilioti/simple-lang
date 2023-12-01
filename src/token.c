#include "token.h"
#include <stdlib.h>

struct token* token_init(int type, char* value)
{
    struct token* token = calloc(1, sizeof(struct token));
    token->type = type;
    token->value = value;

    return token;
}