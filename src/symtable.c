#include <stdlib.h>
#include <string.h>
#include "symtable.h"

struct symbol_table* symtable_init()
{
    struct symbol_table* symtable = malloc(sizeof(struct symbol_table));
    symtable->head = NULL;
    return symtable;
}

int symtable_empty(struct symbol* head)
{
    if(head == NULL)
        return 1;

    return 0;
}

int symtable_find(struct symbol_table* symtable, char* name)
{
    if(symtable_empty(symtable->head))
        return 0;

    struct symbol* temp = symtable->head;
    while(temp != NULL)
    {
        if(strcmp(temp->name, name) == 0)
            return temp->value;

        temp = temp->next;
    }
    
    return 0;
}

int symtable_push(struct symbol_table* symtable, char* name, int value)
{
    struct symbol* new  = malloc(sizeof(struct symbol));
    new->name = name;
    new->value = value;

    if(symtable_empty(symtable->head))
    {
        symtable->head = new;
        return 1;
    }

    struct symbol* temp = symtable->head;
    while(temp->next != NULL)
        temp = temp->next;

    temp->next = new;
    return 1;
}

int symtable_update(struct symbol_table* symtable, char* name, int value)
{
    if(symtable_empty(symtable->head))
        return 0;

    struct symbol* temp = symtable->head;
    while(temp != NULL)
    {
        if(strcmp(temp->name, name) == 0)
        {
            temp->value = value;
            return 1;
        }

        temp = temp->next;
    }
    
    return 0;
}