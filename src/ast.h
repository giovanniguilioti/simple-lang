#ifndef AST_H
#define AST_H

enum ast_type
{
    AST_NUMBER,
    AST_ADD,
    AST_SUB,
    AST_MULT,
    AST_DIV
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
    };
};

struct ast_node* ast_op(char c, struct ast_node* l, struct ast_node* r);

struct ast_node* ast_num(int v);

void ast_post_order(struct ast_node* n);

void ast_print(struct ast_node* node, int indent);

#endif