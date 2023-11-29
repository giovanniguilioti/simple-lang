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

void ast_post_order(struct ast_node* n)
{
    if (n != NULL)
    {
        ast_post_order(n->left);
        ast_post_order(n->right);
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

void ast_print(struct ast_node* node, int space)
{
    if (node == NULL) {
        return;
    }

    space += 10;

    ast_print(node->right, space);

    for (int i = 10; i < space; i++) {
        printf("  ");
    }

    switch (node->type)
    {
        case AST_NUMBER:
            printf("%d\n", node->value);
            break;
        case AST_ADD:
            printf("+\n");
            break;
        case AST_SUB:
            printf("-\n");
            break;
        case AST_MULT:
            printf("*\n");
            break;
        case AST_DIV:
            printf("/\n");
            break;
        default:
            exit(1);
    }

    ast_print(node->left, space);
}
