#include "list.h"
#include <stdio.h>

struct list* list_init()
{
    struct list* list = malloc(sizeof(list));
    list->head = NULL;
    return list;
}

int list_empty(struct token_node* head)
{
    if(head == NULL)
        return 1;

    return 0;
}

int list_size(struct token_node* head)
{
    if(head == NULL)
        return 0;

    struct token_node* temp = head->next;

    int i = 1;
    while(temp != NULL)
    {   
        temp = temp->next;
        ++i;
    }

    return i;
}


struct list* list_push(struct list* list, struct token* token)
{
    struct token_node* new  = malloc(sizeof(struct token_node));
    new->token = *token;
    new->next = NULL;

    if(list_empty(list->head))
    {
        list->head = new;
        return list;
    }

    struct token_node* temp = list->head;
    while(temp->next != NULL)
        temp = temp->next;

    temp->next = new;
    return list;
}

struct token_node* list_at(struct list* list, int index)
{
    if(list_empty(list->head))
        return 0;

    if(index < 0)
        return 0;

    if(index >= list_size(list->head))
        return 0;

    struct token_node* temp = list->head;
    int i = 0;
    while(i < index)
    {
        temp = temp->next;
        ++i;
    }
    
    return temp;
}