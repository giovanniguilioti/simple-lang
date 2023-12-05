#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

struct symbol
{
    char* name;
    int value;
    struct symbol* next;
};

struct symbol_table
{
    struct symbol* head;
};

struct symbol_table* symtable_init();

int symtable_empty(struct symbol* head);

int symtable_find(struct symbol_table* symtable, char* name);

int symtable_push(struct symbol_table* symtable, char* name, int value);

int symtable_update(struct symbol_table* symtable, char* name, int value);

#endif