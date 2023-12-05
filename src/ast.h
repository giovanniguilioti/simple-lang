#ifndef AST_H
#define AST_H

#include "symtable.h"

enum ast_type
{
    AST_EMPTY,
    AST_ID,
    AST_NUMBER,
    AST_ADD,
    AST_SUB,
    AST_MULT,
    AST_DIV,
    AST_ASSIGN
};

struct ast_node
{
    enum ast_type type;

    struct ast_node* right;
    struct ast_node* left;

    union
    {
        int value;
        char op;
        char* id;
    };
};

struct ast_node* ast_empty(enum ast_type type);

struct ast_node* ast_num(int v);

struct ast_node* ast_op(char c, struct ast_node* l, struct ast_node* r);

struct ast_node* ast_id(char* id);

void ast_evaluate(struct ast_node* node, struct symbol_table* symtable);

void ast_evaluate_add(struct ast_node* node, struct symbol_table* symtable);

void ast_evaluate_sub(struct ast_node* node, struct symbol_table* symtable);

void ast_evaluate_mult(struct ast_node* node, struct symbol_table* symtable);

void ast_evaluate_div(struct ast_node* node, struct symbol_table* symtable);

void ast_evaluate_assign(struct ast_node* node, struct symbol_table* symtable);

void ast_post_order(struct ast_node* n);

void ast_print(struct ast_node* node, int indent);

#endif