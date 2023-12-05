#include "ast.h"
#include "symtable.h"
#include <stdlib.h>
#include <stdio.h>

struct ast_node* ast_empty(enum ast_type type)
{
    struct ast_node* new = malloc(sizeof(struct ast_node));
    new->type = type;

    new->right = NULL;
    new->left = NULL;

    return new;
}

struct ast_node* ast_op(char c, struct ast_node* l, struct ast_node* r)
{
    struct ast_node* new = malloc(sizeof(struct ast_node));
    
    switch(c)
    {
        case '=': 
            new->type = AST_ASSIGN;
            break;
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

struct ast_node* ast_id(char* id)
{
    struct ast_node* new = malloc(sizeof(struct ast_node));
    new->type = AST_ID;
    new->id = id;

    new->right = NULL;
    new->left = NULL;

    return new;
}

void ast_evaluate(struct ast_node* node, struct symbol_table* symtable)
{
    if (node == NULL) {
        return;
    }

    ast_evaluate(node->left, symtable);
    ast_evaluate(node->right, symtable);

    switch (node->type)
    {
        case AST_ADD:
            ast_evaluate_add(node, symtable);
            break;
        case AST_SUB:
            ast_evaluate_sub(node, symtable);
            break;
        case AST_MULT:
            ast_evaluate_mult(node, symtable);
            break;
        case AST_DIV:
            ast_evaluate_div(node, symtable);
            break;
        case AST_ASSIGN:
            ast_evaluate_assign(node, symtable);
            break;
        case AST_NUMBER:
        default:
            return;
    }
}

void ast_evaluate_add(struct ast_node* node, struct symbol_table* symtable)
{
    if(node->left->type ==  AST_ID)
        node->value = symtable_find(symtable, node->left->id) + node->right->value;
    else
        node->value = node->left->value + node->right->value;

    node->type = AST_NUMBER;
}

void ast_evaluate_sub(struct ast_node* node, struct symbol_table* symtable)
{
    if(node->left->type ==  AST_ID)
        node->value = symtable_find(symtable, node->left->id) - node->right->value;
    else
        node->value = node->left->value - node->right->value;

    node->type = AST_NUMBER;
}

void ast_evaluate_mult(struct ast_node* node, struct symbol_table* symtable)
{
    if(node->left->type ==  AST_ID)
        node->value = symtable_find(symtable, node->left->id) * node->right->value;
    else
        node->value = node->left->value * node->right->value;

    node->type = AST_NUMBER;
}

void ast_evaluate_div(struct ast_node* node, struct symbol_table* symtable)
{
    if(node->left->type ==  AST_ID)
        node->value = symtable_find(symtable, node->left->id) / node->right->value;
    else
        node->value = node->left->value / node->right->value;

    node->type = AST_NUMBER;
}

void ast_evaluate_assign(struct ast_node* node, struct symbol_table* symtable)
{
    if(!symtable_find(symtable, node->left->id))
        symtable_push(symtable, node->left->id, node->right->value);
    else
        symtable_update(symtable, node->left->id, node->right->value);
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
            case AST_ID:
                printf("%s | ", n->id);
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
        case AST_ID:
            printf("%s\n", node->id);
            break;
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
        case AST_ASSIGN:
            printf("=\n");
            break;
        case AST_EMPTY:
            printf("empty\n");
            break;
        default:
            exit(1);
    }

    ast_print(node->left, space);
}
