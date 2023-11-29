#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

struct ast_node* ast_op(char c, struct ast_node* l, struct ast_node* r)
{
    struct ast_node* new = malloc(sizeof(struct ast_node));
    
    switch(c)
    {
        case '+':
            new->type = AST_ADD;
            break;
        case '-':
            new->type = AST_SUB;
            break;
        case '*':
            new->type = AST_MULT;
            break;
        case '/': 
            new->type = AST_DIV;
            break;
    }

    new->op = c;
    new->left = l;
    new->right = r;

    return new;
}

struct ast_node* ast_num(int v)
{
    struct ast_node* new = malloc(sizeof(struct ast_node));
    new->type = AST_NUMBER;
    new->value = v;

    new->right = NULL;
    new->left = NULL;

    return new;
}

void ast_post(struct ast_node* n)
{
    if (n != NULL)
    {
        ast_post(n->left);
        ast_post(n->right);
        switch(n->type)
        {
            case AST_NUMBER:
                printf("%d | ", n->value);
                break;
            default:
                printf("%c | ", n->op);
                break;
        }
        
    }
}