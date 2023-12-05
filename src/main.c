#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "token.h"
#include "lexer.h"
#include "token_list.h"
#include "parser.h"
#include "ast.h"
#include "symtable.h"

char* readFile(char* filename);

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char filename[100];
    strcpy(filename, ".//example//");
    strcat(filename, argv[1]);
    
    char* content = readFile(filename);

    struct lexer* lexer = lexer_init(content);
    struct token* token = (void*)0;

    struct token_list* list = list_init();

    while((token = lexer_get_next_token(lexer)) != (void*)0)
    {
        list_push(list, token);
        //printf("[%d, %s]\n", token->type, token->value);
    }

    struct symbol_table* symtable = symtable_init();
    struct parser* parser = parser_init(list);
    struct ast_node* ast = stmts(parser);
    ast_print(ast, 0);
    ast_evaluate(ast, symtable);
    struct symbol* node = symtable->head;
    while(node != NULL)
    {
        printf("%s: %d\n", node->name, node->value);
        node = node->next;
    }/*
    printf("\n%s: %d\n", symtable->head->name, symtable->head->value);*/
    //printf("%d", ast->type);
}

char* readFile(char* filename)
{
    FILE* example = fopen(filename, "r");
    if (example == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fseek(example, 0, SEEK_END);
    long file_size = ftell(example);
    fseek(example, 0, SEEK_SET);

    char* content = (char*)malloc(file_size + 1);
    if (content == NULL) {
        fclose(example);
        exit(EXIT_FAILURE);
    }

    size_t bytesRead = fread(content, 1, file_size, example);
    if (bytesRead != (size_t)file_size) {
        fclose(example);
        free(content);
        exit(EXIT_FAILURE);
    }

    content[file_size] = '\0';

    fclose(example);
    return content;
}